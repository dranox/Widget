
#ifndef BUTTON
#define BUTTON
#include "widgets.hpp"
#include "graphics.hpp"

class Button : public Widget
{
protected:
    std::string Label;
public:
    Button(int x, int y, int sx, int sy,std::string label);
    virtual void draw() const;
    virtual void handle(genv::event ev);
};


#endif // WIDGETS_HPP_INCLUDED
