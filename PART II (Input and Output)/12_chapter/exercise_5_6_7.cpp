/*
[5]
Define a Striped_rectangle where instead of fill, the rectangle is ‘‘filled’’ by drawing one-
pixel-wide horizontal lines across the inside of the rectangle (say, draw every second line like
that). You may have to play with the width of lines and the line spacing to get a pattern you
like.
[6]
Define a Striped_circle using the technique from Striped_rectangle.
[7]
Define a Striped_closed_polyline using the technique from Striped_rectangle (this requires
some algorithmic inventiveness).
*/

#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/Simple_window.h"
#include <numbers>

using namespace Graph_lib;

class Striped_closed_polyline :public Closed_polyline
{
public:
    using Closed_polyline::Closed_polyline;
    void draw_specifics(Painter& painter) const override;

};
void Striped_closed_polyline::draw_specifics(Painter& painter) const
{
    if (fill_color().visibility() && 2 < number_of_points()) //at least 3 points
    {
        Color c = color();
        painter.set_color(fill_color());
        Point left{ -2500,0 };
        Point right{ 2500,0 };
        while (right.y<1500)
        {
            vector<Point> intersections;

            Point p_intersect;
            for (int a = 1; a < number_of_points(); ++a)
            {
                bool is_intersect{ line_segment_intersect(left, right
                    ,point(a - 1), point(a),p_intersect) };
                if (is_intersect&& p_intersect!= point(a) && p_intersect != point(a-1))
                    intersections.push_back(p_intersect);
            }

            bool is_intersect{ line_segment_intersect(left, right
                    ,point(number_of_points() - 1), point(0),p_intersect) };// last line
            if (is_intersect && p_intersect != point(0) && p_intersect != point(number_of_points() - 1))
                intersections.push_back(p_intersect);

            for (int x = 1; x < intersections.size(); x+=2)
            {
                painter.draw_line(intersections[x-1], intersections[x]);
            }
            left.y += style().width() * 2;
            right.y += style().width() * 2;
        }
        painter.set_color(c);
    }
    if (color().visibility())
    {
        painter.set_fill_color(Color::invisible); //draw() will restore()
        Closed_polyline::draw_specifics(painter);
    }
}
//-----------------------------------------------
Point get_point(const Circle& e, double angle_degree)
{
    double angle_radians{ angle_degree * (std::numbers::pi / 180.0) };
    int x = e.center().x + e.radius() * cos(angle_radians);
    int y = e.center().y + e.radius() * sin(angle_radians);
    return { x,y };
}
class Striped_circle :public Circle
{
public:
    using Circle::Circle;
    void draw_specifics(Painter& painter) const override;

};
void Striped_circle::draw_specifics(Painter& painter) const
{
    if (fill_color().visibility())
    {
        Color c = color();
        painter.set_color(fill_color());
        Point p_left{ center().x,center().y-radius()};
        Point p_right{ p_left };
        int degree_left = 90;
        int degree_right = 90;
        while (degree_left < 270 )
        {
            painter.draw_line(p_left, p_right);
            degree_left += style().width() * 2;
            degree_right -= style().width() * 2;
            p_left = get_point(*this, degree_left);
            p_right = get_point(*this, degree_right);
        }
        painter.set_color(c);
    }
    if (color().visibility())
    {
        painter.set_fill_color(Color::invisible); //draw() will restore()
        Circle::draw_specifics(painter);
    }
}
//-----------------------------------------------
class Striped_rectangle :public Rectangle
{
public:
    using Rectangle::Rectangle;
    void draw_specifics(Painter& painter) const override;

};
void Striped_rectangle::draw_specifics(Painter& painter) const
{
    if (fill_color().visibility())
    {
        Point p_left{ point(0) };
        Point p_right{ p_left.x + width(),p_left.y };
        Color c = color();
        painter.set_color(fill_color()); 
        for (int max = p_left.y + height(); p_left.y < max;)
        {
            painter.draw_line(p_left, p_right);
            p_left.y += style().width() * 2;
            p_right.y += style().width() * 2;
        }
        painter.set_color(c);
    }
    if (color().visibility())
    {
        Point p0{ point(0) };
        Point p1{ p0.x + width(),p0.y };
        Point p2{ p0.x + width(),p0.y + height() };
        Point p3{ p0.x,p0.y + height() };
        painter.draw_line(p0, p1);
        painter.draw_line(p1, p2);
        painter.draw_line(p2, p3);
        painter.draw_line(p3, p0);
    }
}
//-----------------------------------------------
int main(int /*argc*/, char* /*argv*/[])
{
    Application app;
    Simple_window win{ {100,100},600,400,"chapter" };
    Striped_rectangle sr{ {100,100},200,100 };
    sr.set_style({ Line_style::dashdot,5 });
    sr.set_color(Color::blue);
    sr.set_fill_color(Color::magenta);

    Striped_circle sc{ {100,100},150 };
    sc.set_color(Color::blue);
    sc.set_fill_color(Color::dark_blue);


    Striped_closed_polyline star{ {100,100},{200,200},{50,150},{300,125},{100,200} };
    star.set_fill_color(Color::dark_blue);

    win.attach(star);
    //win.attach(sr);
   // win.attach(sc);
    win.wait_for_button();
}
