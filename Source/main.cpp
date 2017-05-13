#include "graphics.hpp"
#include "widgets.hpp"
#include "kival.hpp"
#include "szambe.hpp"
#include "button.hpp"
#include "textbox.hpp"
#include "slista.hpp"
#include "amoba.hpp"
#include <fstream>
#include <vector>

using namespace std;
using namespace genv;

void event_loop(std::vector<std::vector<Widget*> >& widgets,const int & rows, const int & cols)
{
    event ev;
    int focusi = -1;
    int focusj = -1;
    char turn = 'X';

    fstream f;
    f.open("Test", fstream::out );
    while(gin >> ev )
    {

        if (ev.type == ev_mouse && ev.button==btn_left)
        {
            for(int i=0; i<cols; i++)
            {
                for(int j=0; j<rows; j++)
                {
                    if (widgets[i][j]->is_selected(ev.pos_x, ev.pos_y))
                    {
                        focusi = i;
                        focusj = j;
                    }
                }
            }
        }
        if (focusi!=-1)
        {
            if(widgets[focusi][focusj]->getData()==" ")
            {
             widgets[focusi][focusj]->setTurn(turn);
             if(turn=='X')turn='O';
             else turn='X';
            }
            widgets[focusi][focusj]->handle(ev);

        }
        for(int i=0; i<cols; i++)
        {
            for(int j=0; j<rows; j++)
            {
                widgets[i][j]->draw();
            }
        }
        gout << refresh;
    }
}


int main()
{
    gout.open(1000,1000);
    vector<Widget*> w;


    int rows = 10;
    int cols = 5;
    std::vector<std::vector<Widget*> > matrix;
    matrix.resize(cols, std::vector<Widget*>(rows));
    for(int i=0; i<cols; i++)
    {
        for(int j=0; j<rows; j++)
        {
            matrix[i][j] = new Amoba(5+i*30,5+j*30,30,30);
        }
    }

    event_loop(matrix, rows, cols);
    return 0;
}
