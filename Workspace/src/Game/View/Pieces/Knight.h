#ifndef __KNIGHT__
#define __KNIGHT__

#include "Common.h"
#include "DrawElement.h"

namespace View {

class Knight : public View::DrawElement
{
public:
    Knight( const View::Position& pos );
    ~Knight();

    virtual void draw();
    virtual void createGeometry();

private:
};

}

#endif