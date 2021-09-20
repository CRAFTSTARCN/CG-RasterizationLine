#ifndef REPEAT_RENDED_OBJECT_H
#define REPEAT_RENDED_OBJECT_H

#include "glm/glm.hpp"

#include "RenderableObject.h"
#include "Algo.h"


class RepeatRendedObject : public RenderableObject {

    private:
    unsigned int CanvasSize;
    unsigned int pixelSize;
    glm::mat4 translate;
    Algo algo;

    int x0, y0,x1,y1;

    typedef void (Algo::*AlgoFunc)(int,int,int,int);
 
    AlgoFunc genFunc;

    public:

    RepeatRendedObject(GLenum drawT, GLenum rendT, int shader,unsigned int srcsz, unsigned int pixSize);
    virtual void init();
    virtual void renderPipline();
};

#endif