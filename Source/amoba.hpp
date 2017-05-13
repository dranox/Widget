#ifndef AMOBA
#define AMOBA

#include "graphics.hpp"
#include "widgets.hpp"


class Amoba : public Widget
{
    protected:
        char dolog;
        char pturn;
    public:
        Amoba(int x, int y, int sx, int sy);
        virtual void draw() const ;
        virtual void handle(genv::event ev);
        virtual char getData();
        virtual void setTurn(const char &);
};
#endif // WIDGETS_HPP_INCLUDED
