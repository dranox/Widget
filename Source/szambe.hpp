
#ifndef SZAMBE
#define SZAMBE

#include "graphics.hpp"
#include "widgets.hpp"

class Szambe : public Widget
{
protected:
    int szam; //maga az adat amit tárolunk
    int min_,max_ ; //intervallum
    bool selected;
public:
    Szambe(int x, int y, int sx, int sy, int Min, int Max);
    virtual void draw() const ;
    virtual void handle(genv::event ev);
    virtual int select(int mouse_x, int mouse_y); //visszaadja hogy az egér a "+" vagy "-" -on van
};


#endif // SZAMBE
