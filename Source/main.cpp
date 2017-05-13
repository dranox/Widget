#include "graphics.hpp"
#include "widgets.hpp"
#include "kival.hpp"
#include "szambe.hpp"
#include "button.hpp"
#include "textbox.hpp"
#include "slista.hpp"
#include "amoba.hpp"
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace genv;

void game(std::vector<std::vector<Widget*> >& widgets,const int & rows, const int & cols, const bool & multiplayer)
{
    event ev;
    int focusi = -1;
    int focusj = -1;
    char turn = 'X';
    int k = 0;

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

        while(turn=='O' && !multiplayer)
        {

            int x = std::rand() % cols;
            std::srand(std::time(0));
            int y = std::rand() % rows;
            if(widgets[x][y]->getData()==" ")
            {
                widgets[x][y]->setData('O');
                turn = 'X';
            }

        }

        for(int i=0; i<cols && !multiplayer; i++)
        {
            for(int j=0; j<rows; j++)
            {
                if(widgets[i][j]->getData()!=" ")
                {
                    if(k<5)
                        for(k=0; k<5 && i<rows-4; k++)
                        {
                            if(widgets[i+k][j]->getData()!=widgets[i][j]->getData())
                                break;
                        }
                    if(k<5)
                        for(k=0; k<5 && j<cols-4; k++)
                        {
                            if(widgets[i][j+k]->getData()!=widgets[i][j]->getData())
                                break;
                        }
                    if(k<5)
                        for(k=0; k<5 && i<rows-4 && j<cols-4; k++)
                        {
                            if(widgets[i+k][j+k]->getData()!=widgets[i][j]->getData())
                                break;
                        }
                    if(k<5)
                        for(k=0; k<5 && i<rows-4 && j>4; k++)
                        {
                            if(widgets[i+k][j-k]->getData()!=widgets[i][j]->getData())
                                break;
                        }
                }
            }
        }

        if(k>=4)break;

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



        for(int i=0; i<cols; i++)
        {
            for(int j=0; j<rows; j++)
            {
                if(widgets[i][j]->getData()!=" ")
                {
                    if(k<5)
                        for(k=0; k<5 && i<rows-4; k++)
                        {
                            if(widgets[i+k][j]->getData()!=widgets[i][j]->getData())
                                break;
                        }
                    if(k<5)
                        for(k=0; k<5 && j<cols-4; k++)
                        {
                            if(widgets[i][j+k]->getData()!=widgets[i][j]->getData())
                                break;
                        }
                    if(k<5)
                        for(k=0; k<5 && i<rows-4 && j<cols-4; k++)
                        {
                            if(widgets[i+k][j+k]->getData()!=widgets[i][j]->getData())
                                break;
                        }
                    if(k<5)
                        for(k=0; k<5 && i<rows-4 && j>4; k++)
                        {
                            if(widgets[i+k][j-k]->getData()!=widgets[i][j]->getData())
                                break;
                        }
                }
            }
        }

        if(k>=4)break;

        gout << refresh;
    }
    if(turn=='X')turn='O';
    else turn='X';
    gout<<color(0,0,0)<<move_to(10,10)<<box(50,20)<<color(255,0,0)<<move_to(10,25)<<text(turn)<<text(" wins")<<refresh;

    while(gin >> ev )
    {

    }
}

bool menu(int & rows, int & cols)
{
    event ev;
    int focus = -1;
    gout << move_to(50,45)<<color(255,255,255)<<text("Sorok száma")<<move_to(150,45)<<text("Oszlopok száma");
    vector<Widget*> widgets;

    Szambe * a1 = new Szambe(50,50,100,20, 10, 30);
    Szambe * a2 = new Szambe(160, 50, 100,20, 10,30);
    Button * b1 = new Button(50,100,150,50,"Single Player");
    Button * b2 = new Button(50,160,150,50,"Multy Player");

    widgets.push_back(a1);
    widgets.push_back(a2);
    widgets.push_back(b1);
    widgets.push_back(b2);

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
                if(e == "Single Player")
                {
                    return false;
                }
                if(e == "Multy Player")
                {
                    return true;
                }
                if(focus == 0)
                {
                    std::stringstream ss;
                    ss << e;
                    ss >> rows;
                }
                if(focus == 1)
                {
                    std::stringstream ss;
                    ss << e;
                    ss >> cols;
                }
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
    gout.open(1000,1000);
    bool multiplayer;

    int rows = 10;
    int cols = 10;

    multiplayer = menu(rows, cols);


    std::vector<std::vector<Widget*> > matrix;
    matrix.resize(cols, std::vector<Widget*>(rows));
    for(int i=0; i<cols; i++)
    {
        for(int j=0; j<rows; j++)
        {
            matrix[i][j] = new Amoba(5+i*30,5+j*30,30,30);
        }
    }

    game(matrix, rows, cols, multiplayer);
    return 0;
}
