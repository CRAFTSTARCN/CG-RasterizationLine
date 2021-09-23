#ifndef TRANSFROMOBJECT_H
#define TRANSFROMOBJECT_H

#include "RenderableObject.h"

class TransfromObject : public RenderableObject {

    protected:
    int inputx0,inputy0;
    int inputx1,inputy1;
    int srcSize;

    void getTransfromInfo();


    public:
    TransfromObject(GLenum drawT, GLenum rendT, int shader, unsigned int srcsize);
    ~TransfromObject();

    
    virtual void renderPipline(const glm::mat4& project);
};

#endif