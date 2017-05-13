#include "szambe.hpp"
#include "graphics.hpp"
#include <string>
#include <iostream>
#include <sstream>
using namespace genv;
using namespace std;

Szambe::Szambe(int x, int y, int sx, int sy, int Min, int Max)
    : Widget(x,y,sx,sy), szam(Min), min_(Min), max_(Max), selected(false)
{}

void Szambe::draw() const
{
    stringstream ss; // stringstream-en keresztül konventárja stringé a számot
    ss<< szam <<endl;
    gout << move_to(_x, _y-2) << color(255,255,255) << box(_size_x+3, _size_y+4); //ezek rajzolják meg a widgetet
    gout << move_to(_x+2, _y) << color(0,0,0) << box(_size_x-11, _size_y);
    gout << move_to(_x+7,_y+_size_y/2+4) << color(255,255,255) << text(ss.str());
    gout << color(0,0,0) << move_to(_x+_size_x-7,_y) << box(8,_size_y/2)<<move_to(_x+_size_x-6,_y+_size_y/4+4) << color(255,255,255) << text('+');
    gout << color(0,0,0) <<move_to(_x+_size_x-7,_y+_size_y/2+1)<< box(8,_size_y/2-1)<<move_to(_x+_size_x-6,_y+_size_y/4+4+_size_y/2)<< color(255,255,255)<< text('--');
}

void Szambe::handle(event ev)
{

    if (ev.type == ev_mouse) selected = is_selected(ev.pos_x, ev.pos_y);


    if (szam < max_)
    {
        if (ev.type == ev_mouse && ev.button==btn_left && this->select(ev.pos_x, ev.pos_y)==1)szam++; //egér nyomásra +1
        if (ev.keycode == key_up && selected) szam++;//felfele nyílja +1
        if (ev.keycode == key_pgup && selected) //page up-ra +10
        {
            szam+=10;
            if(szam>max_)szam=max_;  //ha túllépne 10-en akkor a maxra állítja
        }



    }
    if (szam > min_)
    {
        if (ev.type == ev_mouse && ev.button==btn_left && this->select(ev.pos_x, ev.pos_y)==2)szam--;
        if (ev.keycode == key_down && selected) szam--;
        if (ev.keycode == key_pgdn && selected)
        {
            szam-=10;
            if(szam<min_)szam=min_;
        }
    }

        stringstream ss;
        ss<< szam <<endl;
        throw ss.str(); //itt dobja a kivételt

}
int Szambe::select(int mouse_x, int mouse_y)
{
    if(mouse_x>=_x+_size_x-7 && mouse_x<=_x+_size_x && mouse_y>=_y && mouse_y<=_y+_size_y/2) return 1; //"+"-on van az egér
    if(mouse_x>=_x+_size_x-7 && mouse_x<=_x+_size_x && mouse_y>=_y+_size_y/2 && mouse_y<=_y+_size_y) return 2;//"-"-on van az egér
    return -1; // egyiken sincs
}

