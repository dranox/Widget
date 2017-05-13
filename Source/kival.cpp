#include "kival.hpp"
#include "graphics.hpp"
#include <string>
#include <iostream>
#include <sstream>
using namespace genv;
using namespace std;

Kiv::Kiv(int x, int y, int sx, int sy, int Syy)
    : Widget(x,y,sx,sy), syy(Syy), selected(false), scroll(1)
{
    adatok.push_back("");

}

void Kiv::draw() const
{
    gout << move_to(_x, _y-2) << color(255,255,255) << box(_size_x+3, _size_y+4);
    gout << move_to(_x+2, _y) << color(0,0,0) << box(_size_x-_size_y-4, _size_y);
    gout << move_to(_x+7,_y+_size_y/2+5) << color(255,255,255) << text(adatok[0]);
    gout << color(0,0,0) << move_to(_x+_size_x-_size_y,_y) << box(_size_y,_size_y)<<move_to(_x+_size_x-_size_y/2-4,_y+_size_y/2+5) << color(255,255,255) << text('V');
    gout << move_to(_x,_y+_size_y+2)<< color(0,0,0) << box(_size_x+1,syy-2); // magát a widgetet rajzolja idáig
    if(selected)
    {
        for(int i=0; i<syy/20 && i<adatok.size()-1; i++) // minden éppen látható elemet lerajzól a legördülõben
        {
            gout << move_to(_x,_y+_size_y+i*20) <<color(255,255,255)<< box(_size_x-5,20);
            gout << move_to(_x+1,_y+1+_size_y+i*20) <<color(0,0,0)<< box(_size_x-7,18);
            if(adatok[i+scroll]==adatok[0])//megnézi hogy az adott elem van-e kiválasztva
            {
                gout << move_to(_x+1,_y+1+_size_y+i*20) <<color(70,70,70)<< box(_size_x-7,18); //ha ez van kiválasztva akkor hátteret ad neki
            }
            gout << move_to(_x+5,_y+_size_y+15+i*20) <<color(255,255,255)<<text(adatok[i+scroll]) <<move_to(_x,_y+_size_y-1+(1+i)*20) <<color(255,255,255) << line(_size_x-5,0);
        }
        if((syy/20)<adatok.size()-1)// ha nem fér ki minden elem akkor csinál egy görgõt
        {
            gout <<move_to(_x+_size_x-5,_y+4+_size_y+(scroll-1)*adatok.size()) << color(70,70,70) <<box(6,(syy/20)*syy/(adatok.size()-1)); //görgõ
        }
    }
    else if(delet)
    {
        gout << move_to(_x,_y+_size_y+2)<< color(0,0,0) << box(_size_x+1,syy-2);//eltünteti a legördülõt

    }
}

void Kiv::handle(event ev)
{
    delet=false;
    if(ev.type==ev_mouse && ev.button==btn_left && is_selected(ev.pos_x, ev.pos_y) && ev.pos_x>_x+_size_x-_size_y )
    {
        selected = !selected;
        delet=true;
    }
    if(selected)
    {
        if(ev.button==btn_wheelup && scroll>1) scroll--;//lefele görget
        if(ev.button==btn_wheeldown && scroll<adatok.size()-syy/20) scroll++; //felfele görget
        for(int i = 0; ev.button==btn_left && ev.pos_x>_x &&ev.pos_y>_y+_size_y && ev.pos_x<_x+_size_x && i<syy/20+1 && i<adatok.size(); i++)
        {
            if(ev.pos_y<_y+_size_y+20*i && ev.pos_y>_y+_size_y+20*i-20)adatok[0]=adatok[i+scroll-1];//kiválaszt egy elemet amire kattintunk
            selected = false;//eltünteti a listát
        }
    }

    if(ev.keycode==key_enter) //ha "enter"-t nyomunk akkor kiírja egy file-ba az elemeket
    {
        stringstream ss;
        ss<< adatok[0] <<endl;
        throw ss.str();
    }
}


bool Kiv::is_selected(int mouse_x, int mouse_y)
{
    if(selected)
    {
        if(mouse_x>_x && mouse_x <_x +_size_x && mouse_y>_y && mouse_y<_y+_size_y+syy)
            {
                return true;//ha lenyílik a lista akkor a widget maradjon focus-ba, akkor is ha a listára kattintunk
            }
        else selected = false; //ha azon kivülre kattintunk akkor eltünik a lista

    }
    return mouse_x>_x && mouse_x<_x+_size_x && mouse_y>_y && mouse_y<_y+_size_y;
}
void Kiv::pushb(std::string szavak)
{
    adatok.push_back(szavak);

}
