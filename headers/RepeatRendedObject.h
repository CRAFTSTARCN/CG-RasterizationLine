#ifndef REPEAT_RENDED_OBJECT_H
#define REPEAT_RENDED_OBJECT_H

#include "glm/glm.hpp"

#include "RenderableObject.h"
#include "Algo.h"


class RepeatRendedObject : public RenderableObject {

    private:
    unsigned int CanvasSize;
    unsigned int pixelSize;
    Algo algo;

    int x0, y0,x1,y1;

    int inputx0, inputx1, inputy0, inputy1;

    typedef void (Algo::*AlgoFunc)(int,int,int,int);
 
    AlgoFunc genFunc;

    public:

    RepeatRendedObject(GLenum drawT, GLenum rendT, int shader,unsigned int srcsz, unsigned int pixSize);
    virtual void init();
    virtual void renderPipline(const glm::mat4& project);
};

#endif