#ifndef _SCENE_
#define _SCENE_

#include "DrawElement.h"
#include "src/glm/glm.hpp"

namespace View {

class Scene {
public:
    Scene();
   ~Scene();
    Scene( const Scene& other );

    void addDrawElement( const DrawElement::ePieceType piece, const View::Position& pos);
    void removeDrawElement( const glm::vec2& pos );
    void drawScene(); // set up matrices, call draw on all elements.

    void rotateScene( const float rad, const glm::vec3& axis );
    void drawElements( DrawElement* d) const;

private:
    void operator = ( const Scene& other ); // non-copyable
    
    std::vector< DrawElement* > _drawElementList;
    glm::mat4x4                 _viewMatrix;      // world  -> camera
    glm::mat4x4                 _projectionMatrix;// camera -> clip
};

}
#endif