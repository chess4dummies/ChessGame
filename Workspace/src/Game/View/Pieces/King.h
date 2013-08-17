#ifndef __KING__
#define __KING__

#include "Common.h"
#include "DrawElement.h"

namespace View {

class King : public View::DrawElement
{
public:
    King( const View::Position& pos );
    ~King();

    virtual void draw();
    virtual void createGeometry();

private:
};

}

#endif