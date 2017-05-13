#ifndef KIVI
#define KIVI
#include <vector>
#include <string>
#include "graphics.hpp"
#include "widgets.hpp"

class Kiv : public Widget
{
protected:

    std::vector<std::string> adatok; //adat string vektora
    int syy; //lista magass�ga
    bool selected; //lista ki van-e nyitva
    bool delet; //leg�rd�l� lista t�rl�s�hez
    int scroll; // g�rget�shez a poz�ci�
public:
    Kiv(int x, int y, int sx, int sy, int syy);
    virtual void draw() const ;
    virtual void handle(genv::event ev);
    bool is_selected(int mouse_x, int mouse_y);
    virtual void pushb(std::string);
};


#endif // KIVI
