#ifndef _BOARD_
#define _BOARD_

#include "DrawElement.h"

namespace View {

class Board : public View::DrawElement {
public:
    // constructors
    Board();
    ~Board();

    virtual void draw();
    virtual void createGeometry();

private:
};

}

#endif