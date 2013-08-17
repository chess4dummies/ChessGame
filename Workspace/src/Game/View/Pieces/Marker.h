#ifndef _Marker_
#define _Marker_

#include "Common.h"
#include "DrawElement.h"

namespace View {

class Marker : public View::DrawElement
{
public:
    Marker( const View::Position& pos );
    ~Marker();

    virtual void draw();
    virtual void createGeometry();

private:
};

}

#endif