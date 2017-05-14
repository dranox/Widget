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

void game(std::vector<std::vector<Widget*> >& widgets,const int & rows, const int & cols, const bool & multiplayer, bool & quit)
{
    event ev;
    int focusi = -1;
    int focusj = -1;
    char turn = 'X';
    int k = 0;
    bool exit = false;


    gout <<move_to(20,950)<<color(200,0,0)<<text("Backspace: Vissza a menübe         Esc: Kilépés");
    while(gin >> ev && !quit)
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

        if (ev.keycode==key_escape)
        {
            quit = true;
            break;
        }

        if (ev.keycode==key_backspace)
        {
            exit = true;
            return;
        }
////////////////////////////////////////////////////
        int s;
        int l;
        for(l=4; l>1 && turn=='O'; l--)
            for(int i=0; i<cols && !multiplayer; i++)
            {
                for(int j=0; j<rows; j++)
                {
                    if(widgets[i][j]->getData()=="X")
                    {
                        if(turn=='O')
                        {
                            for(s=0; s<4 && i<rows-4 && i>0; s++)
                            {
                                if(widgets[i+s][j]->getData()!=widgets[i][j]->getData())
                                    break;

                            }
                            if(s==l)
                            {
                                if(widgets[i-1][j]->getData()==" ")
                                {
                                    widgets[i-1][j]->setData('O');
                                    turn = 'X';
                                }
                                else if(widgets[i+s][j]->getData()==" ")
                                {
                                    widgets[i+s][j]->setData('O');
                                    turn = 'X';
                                }

                            }
                        }
                        if(turn=='O')
                        {

                            for(s=0; s<4 && j<cols-4 && j>0; s++)
                            {
                                if(widgets[i][j+s]->getData()!=widgets[i][j]->getData())
                                    break;
                            }
                            if(s==l)
                            {
                                if(widgets[i][j-1]->getData()==" ")
                                {
                                    widgets[i][j-1]->setData('O');
                                    turn = 'X';
                                }
                                else if(widgets[i][j+s]->getData()==" ")
                                {
                                    widgets[i][j+s]->setData('O');
                                    turn = 'X';
                                }

                            }

                        }
                        if(turn=='O')
                        {
                            for(s=0; s<4 && i<rows-4 && j<cols-4 && j>0 && i>0; s++)
                            {
                                if(widgets[i+s][j+s]->getData()!=widgets[i][j]->getData())
                                    break;
                            }
                            if(s==l)
                            {
                                if(widgets[i-1][j-1]->getData()==" ")
                                {
                                    widgets[i-1][j-1]->setData('O');
                                    turn = 'X';
                                }
                                else if(widgets[i+s][j+s]->getData()==" ")
                                {
                                    widgets[i+s][j+s]->setData('O');
                                    turn = 'X';
                                }

                            }
                        }
                        if(turn=='O')
                        {
                            for(s=0; s<4 && i<rows-4 && j>s && i>0; s++)
                            {
                                if(widgets[i+s][j-s]->getData()!=widgets[i][j]->getData())
                                    break;
                            }
                            if(s==l)
                            {
                                if(widgets[i-1][j+1]->getData()==" ")
                                {
                                    widgets[i-1][j+1]->setData('O');
                                    turn = 'X';
                                }
                                else if(widgets[i+s][j-s]->getData()==" ")
                                {
                                    widgets[i+s][j-s]->setData('O');
                                    turn = 'X';
                                }

                            }
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
        int draw;
        for(int i=0; i<cols; i++)
        {
            for(int j=0; j<rows; j++)
            {
                if(widgets[i][j]->getData()==" ")break;
                draw ++;
            }
        }
        if(draw == cols+rows) break;
////////////////////////////////////////

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
                widgets[focusi][focusj]->handle(ev);
                if(turn=='X')turn='O';
                else turn='X';
            }


        }

        for(int i=0; i<cols; i++)
        {
            for(int j=0; j<rows; j++)
            {
                if(widgets[i][j]->getData()==" ")break;
                draw ++;
            }
        }
        if(draw == cols+rows) break;



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
    if(gin >> ev && !quit && !exit)
        gout<<color(0,0,0)<<move_to(10,10)<<box(50,20)<<color(255,0,0)<<move_to(10,25)<<text(turn)<<text(" wins")<<refresh;

    while(gin >> ev && !quit && !exit)
    {
        if (ev.keycode==key_escape)
        {
            quit = true;
            break;
        }

        if (ev.keycode==key_backspace)
        {
            break;
        }
    }
}

bool menu(int & rows, int & cols, bool & quit)
{
    event ev;
    int focus = -1;

    vector<Widget*> widgets;

    Szambe * a1 = new Szambe(50,50,100,20, 10, 30);
    Szambe * a2 = new Szambe(160, 50, 100,20, 10,30);
    Button * b1 = new Button(50,100,150,50,"Single Player");
    Button * b2 = new Button(50,160,150,50,"Multy Player");

    widgets.push_back(a1);
    widgets.push_back(a2);
    widgets.push_back(b1);
    widgets.push_back(b2);

    gout << move_to(0,0) << color(0,0,0) <<box(1000,1000);
    gout << move_to(50,45)<<color(255,255,255)<<text("Sorok száma")<<move_to(150,45)<<text("Oszlopok száma");
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
        if (ev.keycode==key_escape)
        {
            quit = true;
            break;
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
    bool quit = false;
    int rows = 10;
    int cols = 10;
    event ev;

    while(gin >> ev && !quit)
    {
        multiplayer = menu(rows, cols, quit);


        std::vector<std::vector<Widget*> > matrix;
        matrix.resize(cols, std::vector<Widget*>(rows));
        for(int i=0; i<cols; i++)
        {
            for(int j=0; j<rows; j++)
            {
                matrix[i][j] = new Amoba(5+i*30,5+j*30,30,30);
            }
        }

        game(matrix, rows, cols, multiplayer, quit);
    }
    return 0;
}
