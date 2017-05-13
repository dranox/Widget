#include "graphics.hpp"
#include "widgets.hpp"
#include "kival.hpp"
#include "szambe.hpp"
#include "button.hpp"
#include "textbox.hpp"
#include "slista.hpp"
#include <fstream>
#include <vector>

using namespace std;
using namespace genv;

void event_loop(vector<Widget*>& widgets)
{
    event ev;
    int focus = -1;

    fstream f;
    f.open("Test", fstream::out );
    while(gin >> ev )
    {

        if (ev.type == ev_mouse && ev.button==btn_left)
        {
            for (size_t i=0; i<widgets.size(); i++)
            {
                if (widgets[i]->is_selected(ev.pos_x, ev.pos_y))
                {
                    focus = i;
                }
            }
        }
        if (focus!=-1)
        {
            try
            {
                widgets[focus]->handle(ev);
            }
            catch(string e) //elkapja a kivételeket, az Enter gomb lenyomásakor pedig egy file-ba írja ki
            {
                if(e == "Torles")
                {
                    widgets[2]->Remo();
                }
                if(e == "Hozzáadásssssssss")
                {
                    widgets[2]->pushb(widgets[3]->getData());
                }
                f << e;
            }
        }
        for (size_t i=0; i<widgets.size(); i++)
        {
            widgets[i]->draw();
        }
        gout << refresh;
    }
}


int main()
{
    gout.open(400,400);
    vector<Widget*> w;
    Szambe * a1 = new Szambe(50,50,300,40, 0, 30);//létrehoz egy számbeállító widgetet aminek koordinátái 50,50,szélessége 300, magassága 40,a [0:30] intervallumon
    Szambe * a2 = new Szambe(50, 100, 100,20, 53,86);

    Button * b1 = new Button(5,5,50,50,"Torles");
    Button * b2 = new Button(100,5,50,50,"Hozzáadásssssssss");

    Slista * k3= new Slista(100,76,200,200,1);
    Textbox * t1 = new Textbox(200,50,100,30);


//    w.push_back(a1);
//    w.push_back(a2);
//    w.push_back(k1);
//    w.push_back(k2);
    w.push_back(b1);
    w.push_back(b2);
    w.push_back(k3);
    w.push_back(t1);


    event_loop(w);
    return 0;
}
