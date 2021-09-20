#ifndef DYNAMICRENDEDLINE_H
#define DYNAMICRENDEDLINE_H

#include "RenderableObject.h"

class DynamicRendedLine : public RenderableObject {
    private:
    unsigned int srcSize;

    float x0, y0;
    float x1, y1;

    public:
    DynamicRendedLine(GLenum drawT, GLenum rendT, int shader, unsigned int srcsize);
    ~DynamicRendedLine();

    virtual void renderPipline();
};




#endif