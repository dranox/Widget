#include "button.hpp"
#include "widgets.hpp"
#include "graphics.hpp"

using namespace genv;


Button::Button(int x, int y, int sx, int sy,std::string label)
    : Widget(x,y,sx,sy),Label(label)
{}


void Button::draw() const
{

    gout << move_to(_x, _y-2) << color(255,255,255) << box(_size_x+3, _size_y+4); //ezek rajzolják meg a widgetet
    gout << move_to(_x+2, _y) << color(0,0,0) << box(_size_x-1, _size_y);
    gout << move_to(_x+11,_y+_size_y/2+4) << color(255,255,255) << text(Label);

}

void Button::handle(event ev)
{
   if (ev.type == ev_mouse && is_selected(ev.pos_x, ev.pos_y) && ev.button==btn_left)
    {
        throw Label;
    }
}



