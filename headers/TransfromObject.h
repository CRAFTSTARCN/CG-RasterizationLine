#ifndef TRANSFROMOBJECT_H
#define TRANSFROMOBJECT_H

#include "RenderableObject.h"

class TransfromObject : public RenderableObject {

    public:
    TransfromObject(GLenum drawT, GLenum rendT, int shader);
    ~TransfromObject();

    virtual void renderPipline(const glm::mat4& project);
};

#endif