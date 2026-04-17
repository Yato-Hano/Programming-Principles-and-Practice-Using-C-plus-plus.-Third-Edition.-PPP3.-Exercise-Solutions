/*
[18] 
The exceptions defined in the C++ standard library, such as exception, runtime_error, and
out_of_rang e (§4.6.3), are organized into a class hierarchy (with a virtual function what()
returning a string supposedly explaining what went wrong). Search your information sources
for the C++ standard exception class hierarchy and draw a class hierarchy diagram of it.
*/

#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

using namespace Graph_lib;


class Box :public Rectangle
{
public:
    Box(Point, string);
    void draw_specifics(Painter& painter) const override;
private:
    Text lable;
};

void Box::draw_specifics(Painter& painter) const
{
    Rectangle::draw_specifics(painter);
    lable.draw_specifics(painter);
}
Box::Box(Point p, string s)
    : Rectangle(p, 15 * s.length(), 25)
    , lable{ {p.x + 5,p.y + 5},s }
{
    set_fill_color(Color::cyan);
}


class Arrow :public Line {
public:
    Arrow(Point start, Point arrow_here);
    void draw_specifics(Painter& painter) const override;
};

Arrow::Arrow(Point p1, Point p2)
    :Line{ p1,p2 }
{
    const double dx = p2.x - p1.x;
    const double dy = p2.y - p1.y;
    const double angle = std::atan2(dy, dx);

    constexpr double arrow_length{ 15 };
    constexpr double arrow_angle{ 0.5 };

    const int x3 = p2.x - arrow_length * std::cos(angle + arrow_angle);
    const int y3 = p2.y - arrow_length * std::sin(angle + arrow_angle);

    const int x4 = p2.x - arrow_length * std::cos(angle - arrow_angle);
    const int y4 = p2.y - arrow_length * std::sin(angle - arrow_angle);

    Shape::add({ x3,y3 });
    Shape::add({ x4,y4 });
    set_fill_color(Color::black);
}

void Arrow::draw_specifics(Painter& painter) const
{
    painter.draw_line(point(0), point(1));
    painter.draw_polygon(Polygon{ point(1), point(2), point(3) }); // for fill color
}
Point n(const Rectangle& r)
// top center 
{
    return { r.point(0).x + (r.width() / 2),r.point(0).y };
}
Point s(const Rectangle& r)
// bottom center 
{
    return { r.point(0).x + (r.width() / 2),r.point(0).y + r.height() };
}

int main(int /*argc*/, char* /*argv*/[])
{
    Application app;
    Simple_window win{ {100,100},1000,600,"chapter" };
    Box box0{ {200,200},"exception" };
    Box box1{ {10,50},"logic_error(out_of_range)" };
    Box box2{ {50,300},"bad_alloc" };
    Box box3{ {200,350},"bad_cast" };
    Box box4{ {350,350},"bad_function_call" };
    Box box5{ {400,50},"runtime_error(range)" };

    Arrow a0{ n(box1),n(box0) };
    Arrow a1{ n(box2),s(box0) };
    Arrow a2{ n(box3),s(box0) };
    Arrow a3{ n(box4),s(box0) };
    Arrow a4{ n(box5),n(box0) };

    win.attach(a0);
    win.attach(a1);
    win.attach(a2);
    win.attach(a3);
    win.attach(a4);

    win.attach(box0);
    win.attach(box1);
    win.attach(box2);
    win.attach(box3);
    win.attach(box4);
    win.attach(box5);


    win.wait_for_button();
}
