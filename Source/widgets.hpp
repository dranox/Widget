#ifndef WIDGETS_HPP_INCLUDED
#define WIDGETS_HPP_INCLUDED

#include "graphics.hpp"

class Widget
{
protected:
    int _x, _y, _size_x, _size_y;
public:
    Widget(int x, int y, int sx, int sy);
    virtual bool is_selected(int mouse_x, int mouse_y) const;
    virtual void draw() const;
    virtual void handle(genv::event ev);
    virtual void pushb(std::string);
    virtual void Remo();
    virtual std::string getData();
    virtual void setData(const char &);
    virtual void setTurn(const char &);
};


#endif // WIDGETS_HPP_INCLUDED
