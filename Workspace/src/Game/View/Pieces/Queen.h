#ifndef __QUEEN__
#define __QUEEN__

#include "Common.h"
#include "DrawElement.h"

namespace View {

class Queen : public View::DrawElement
{
public:
    Queen( const View::Position& pos );
    ~Queen();

    virtual void draw();
    virtual void createGeometry();

private:
};

}

#endif