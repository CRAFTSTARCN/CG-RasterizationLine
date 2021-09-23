#ifndef RENDERABLEOBJECT_H
#define RENDERABLEOBJECT_H

#include "glad/glad.h"
#include "glm/glm.hpp"

#include <functional>
#include <vector>

class RenderableObject {
    
protected:
    unsigned int VAO, VBO, EBO;
    GLenum drawType, rendType;
    int shaderProgram;

public:


    glm::vec3 translate;
    glm::vec3 rotate;
    glm::vec3 scale;

    RenderableObject(GLenum drawT, GLenum rendT, int shader);
    ~RenderableObject();

    std::vector<float> vertices;
    std::vector<int> indexes;

    virtual void init(const std::function<void(RenderableObject*)>& initFunc);
    virtual void init();

    void bindData();

    virtual void renderPipline(const glm::mat4& project);
};

#endif