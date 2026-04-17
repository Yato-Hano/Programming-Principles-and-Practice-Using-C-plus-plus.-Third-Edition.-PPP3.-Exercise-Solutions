/*
[4]
Define a class Immobile_Circle, which is just like Circle but can’t be moved.
*/

#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

using namespace Graph_lib;
class Immobile_Circle :public Circle
{
public:
    using Circle::Circle;
private:
    void move(int dx, int dy) override {}
};


void f_move(Shape& c)
{
    c.move(120, 120);
}
int main(int /*argc*/, char* /*argv*/[])
{
    Application app;
    Simple_window win{ {100,100},600,400,"chapter" };
    Circle c{ {100,100} ,50};
    win.attach(c);
    Immobile_Circle ic{ {200,100} ,50 };
    ic.set_color(Color::red);
    win.attach(ic);
    win.wait_for_button();
    f_move(ic);
    f_move(c);
    // ic.move(-100, -100);

    win.wait_for_button();
}
