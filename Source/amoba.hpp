#ifndef AMOBA
#define AMOBA

#include "graphics.hpp"
#include "widgets.hpp"
#include <string>

class Amoba : public Widget
{
    protected:
        char dolog;
        char pturn;
    public:
        Amoba(int x, int y, int sx, int sy);
        virtual void draw() const ;
        virtual void handle(genv::event ev);
        virtual std::string getData();
        virtual void setTurn(const char &);
        void setData(const char & c);
};
#endif // WIDGETS_HPP_INCLUDED
