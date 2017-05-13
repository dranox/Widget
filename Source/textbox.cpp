#include "textbox.hpp"
#include "graphics.hpp"
#include <string>
#include <iostream>
#include <sstream>
using namespace genv;
using namespace std;

Textbox::Textbox(int x, int y, int sx, int sy)
    : Widget(x,y,sx,sy), betu(""),  selected(false)
{}

void Textbox::draw() const
{
    stringstream ss; // stringstream-en keresztül konventárja stringé a számot
    ss<< betu <<endl;

    gout << move_to(_x, _y-2) << color(255,255,255) << box(_size_x+3, _size_y+4); //ezek rajzolják meg a widgetet
    if(selected){gout << move_to(_x, _y-2) << color(30,255,0) << box(_size_x+3, _size_y+4); //ezek rajzolják meg a widgetet
    }
    gout << move_to(_x+2, _y) << color(0,0,0) << box(_size_x-1, _size_y);
    gout << move_to(_x+2,_y+_size_y/2+4) << color(255,255,255) << text(ss.str());
    if(selected && betu.length()<(_size_x/8)){gout <<move_to(_x+2+betu.size()*8,_y+_size_y/2+4) << text("|");}
}

void Textbox::handle(event ev)
{
    string asd;

    if (ev.type == ev_mouse) selected = is_selected(ev.pos_x, ev.pos_y);
        if(betu.length()<(_size_x/8)){
   if (ev.type == ev_key && ev.keycode !=key_backspace && ev.keycode>0 && ev.keycode<255)asd=ev.keycode;betu.append(asd);
    }
   if (ev.keycode ==key_backspace && selected) betu=betu.substr (0,betu.length()-1);



}
int Textbox::select(int mouse_x, int mouse_y)
{
    if(mouse_x>=_x+_size_x-7 && mouse_x<=_x+_size_x && mouse_y>=_y && mouse_y<=_y+_size_y/2) return 1; //"+"-on van az egér
    if(mouse_x>=_x+_size_x-7 && mouse_x<=_x+_size_x && mouse_y>=_y+_size_y/2 && mouse_y<=_y+_size_y) return 2;//"-"-on van az egér
    return -1; // egyiken sincs
}

std::string Textbox::getData(){
return betu;
}
