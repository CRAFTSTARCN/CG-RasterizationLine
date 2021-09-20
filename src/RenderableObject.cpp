#include "RenderableObject.h"

RenderableObject::RenderableObject(GLenum drawT, GLenum rendT, int shader) {
    drawType = drawT;
    rendType = rendT;
    shaderProgram = shader;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);    
}

RenderableObject::~RenderableObject() {
    glDeleteBuffers(1,&VAO);
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&EBO);
}

/*
WARNNING:
Asynchronous function
You cant run this function in to thread simultaneously
*/
void RenderableObject::bindData() {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,vertices.size()*sizeof(float),vertices.data(),drawType);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,indexes.size()*sizeof(int),indexes.data(),drawType);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

/*
WARNNING:
Asynchronous function
You cant run this function in to thread simultaneously
*/
void RenderableObject::renderPipline() {
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(rendType,indexes.size(),GL_UNSIGNED_INT,0);
    glBindVertexArray(0);
}

void RenderableObject::init(const std::function<void(RenderableObject*)>& initFunc) {
    initFunc(this);
}

void RenderableObject::init() {

}