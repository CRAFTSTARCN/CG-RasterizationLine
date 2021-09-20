#ifndef RENDERABLEOBJECT_H
#define RENDERABLEOBJECT_H

#include "glad/glad.h"

#include <functional>
#include <vector>

class RenderableObject {
    
protected:
    unsigned int VAO, VBO, EBO;
    GLenum drawType, rendType;
    int shaderProgram;
    float pix;
public:

    RenderableObject(GLenum drawT, GLenum rendT, int shader);
    ~RenderableObject();

    std::vector<float> vertices;
    std::vector<int> indexes;

    virtual void init(const std::function<void(RenderableObject*)>& initFunc);
    virtual void init();

    void bindData();

    virtual void renderPipline();
};

#endif