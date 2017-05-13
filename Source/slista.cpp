#include "Slista.hpp"
#include "graphics.hpp"
#include <string>
#include <iostream>
#include <sstream>
using namespace genv;
using namespace std;

Slista::Slista(int x, int y, int sx, int sy,int)
    : Widget(x,y,sx,sy), scroll(1)
{
    adatok.push_back("");

}

void Slista::draw() const
{

        gout << move_to(_x-1,_y+1)<< color(255,255,255) << box(_size_x+3,_size_y);//eltünteti a legördülõt
        gout << move_to(_x,_y+2)<< color(0,0,0) << box(_size_x+1,_size_y-2);
        gout << move_to(_x-6+_size_x,_y) << color(255,255,255) << line(0,_size_y);

        for(int i=0; i<_size_y/20 && i<adatok.size()-1; i++) // minden éppen látható elemet lerajzól a legördülõben
        {
            gout << move_to(_x,_y+i*20) <<color(255,255,255)<< box(_size_x-5,20);
            gout << move_to(_x+1,_y+1+i*20) <<color(0,0,0)<< box(_size_x-7,18);
            if(adatok[i+scroll]==adatok[0])//megnézi hogy az adott elem van-e kiválasztva
            {
                gout << move_to(_x+1,_y+1+i*20) <<color(70,70,70)<< box(_size_x-7,18); //ha ez van kiválasztva akkor hátteret ad neki
            }
            gout << move_to(_x+5,_y+15+i*20) <<color(255,255,255)<<text(adatok[i+scroll]) <<move_to(_x,_y-1+(1+i)*20) <<color(255,255,255) << line(_size_x-5,0);
        }
        if((_size_y/20)<adatok.size()-1)// ha nem fér ki minden elem akkor csinál egy görgõt
        {
            gout <<move_to(_x+_size_x-5,_y+(scroll-1)*adatok.size()) << color(70,70,70) <<box(6,(_size_y/20)*_size_y/(adatok.size()-1)); //görgõ
        }
}

void Slista::handle(event ev)
{



        if(ev.button==btn_wheelup && scroll>1) scroll--;//lefele görget
        if(ev.button==btn_wheeldown && scroll<adatok.size()-_size_y/20) scroll++; //felfele görget
        for(int i = 0; ev.button==btn_left && ev.pos_x>_x &&ev.pos_y>_y && ev.pos_x<_x+_size_x && i<_size_y/20+1 && i<adatok.size(); i++)
        {
            if(ev.pos_y<_y+20*i && ev.pos_y>_y+20*i-20)adatok[0]=adatok[i+scroll-1];//kiválaszt egy elemet amire kattintunk

        }


    if(ev.keycode==key_enter) //ha "enter"-t nyomunk akkor kiírja egy file-ba az elemeket
    {
        stringstream ss;
        ss<< adatok[0] <<endl;
        throw ss.str();
    }
}


bool Slista::is_selected(int mouse_x, int mouse_y)
{

        if(mouse_x>_x && mouse_x <_x +_size_x && mouse_y>_y && mouse_y<_y)
            {
                return true;
            }


}
void Slista::pushb(std::string szavak)
{
    adatok.push_back(szavak);

}

void Slista::Remo()
{
    for(int i=1;i<adatok.size();i++)
    {
        if(adatok[i]==adatok[0])
        {
            adatok[0]="";
            adatok.erase(adatok.begin()+i);
            break;
        }
    }
}

