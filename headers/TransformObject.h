#ifndef TRANSFROMOBJECT_H
#define TRANSFROMOBJECT_H

#include "RenderableObject.h"

class TransfromObject : public RenderableObject {
    int x0,y0;
    int x1,y1;

    public:
    TransfromObject(GLenum drawT, GLenum rendT, int shader);
    ~TransfromObject();

    virtual void renderPipline(const glm::mat4& project);
};

#endif