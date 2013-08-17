#ifndef __BISHOP__
#define __BISHOP__

#include "Common.h"
#include "DrawElement.h"

namespace View {

class Bishop : public View::DrawElement
{
public:
    Bishop( const View::Position& pos );
    ~Bishop();

    virtual void draw();
    virtual void createGeometry();

private:
};

}

#endif