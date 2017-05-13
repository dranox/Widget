
#ifndef TEXTBOX
#define TEXTBOX

#include "graphics.hpp"
#include "widgets.hpp"
#include "string"
#include "vector"

class  Textbox: public Widget
{
protected:
    std::string betu; //maga az adat amit tárolunk
    bool selected;

public:
    Textbox(int x, int y, int sx, int sy);
    virtual void draw() const ;
    virtual void handle(genv::event ev);
    virtual int select(int mouse_x, int mouse_y); //visszaadja hogy az egér a "+" vagy "-" -on van
    virtual std::string getData();
};


#endif // SZAMBE

