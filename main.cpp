#include "graphics.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <sstream>

int main()
{

    int goutmaxx=700;
    int goutmaxy=800;
    gout.open(goutmaxx,goutmaxy);
    int pixwidth,pixheight;
    ifs>>pixwidth;
    ifs>>pixheight;
    canvas c(pixwidth,pixheight);
    int i,j;
    int r,g,b;
    for(j=0; j<pixheight; j++)
    {
        for(i=0; i<pixwidth; i++)
        {
            ifs>>r>>g>>b;
            c<<color(r,g,b)<<move_to(i,j)<<dot;
        }
    }
    gout<<stamp(c,0,0)<<refresh;
    event ev;
    while(gin >> ev)
    {
        if(ev.type==ev_mouse)
        {
            gout <<move_to(0,0) <<color(0,0,0) <<box_to(goutmaxx-1,goutmaxy-1);
            gout<<stamp(c,ev.pos_x,ev.pos_y)<< refresh;
        }
    };
    return 0;
}
