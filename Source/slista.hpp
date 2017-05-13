
#ifndef SLISTA
#define SLISTA
#include <vector>
#include <string>
#include "graphics.hpp"
#include "widgets.hpp"

class Slista : public Widget
{
protected:

    std::vector<std::string> adatok; //adat string vektora
    int scroll; // görgetéshez a pozíció
public:
    Slista(int x, int y, int sx, int sy, int);
    virtual void draw() const ;
    virtual void handle(genv::event ev);
    bool is_selected(int mouse_x, int mouse_y);
    virtual void pushb(std::string);
    virtual void Remo();
};


#endif // Slista
