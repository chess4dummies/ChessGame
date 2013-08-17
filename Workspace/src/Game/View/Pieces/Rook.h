#ifndef __ROOK__
#define __ROOK__

#include "Common.h"
#include "DrawElement.h"

namespace View {

class Rook : public View::DrawElement
{
public:
    Rook( const View::Position& pos );
    ~Rook();

    virtual void draw();
    virtual void createGeometry();

private:
};

}

#endif