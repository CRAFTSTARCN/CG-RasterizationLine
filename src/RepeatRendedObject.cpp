#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "RepeatRendedObject.h"
#include "InputHandler.h"
#include "Logger.h"

RepeatRendedObject::RepeatRendedObject(GLenum drawT, GLenum rendT, int shader,
                                      unsigned int srcsz, unsigned int pixSize)
                    : RenderableObject(drawT,rendT,shader), algo()
{
    CanvasSize = srcsz;
    pixelSize = pixSize;
    genFunc = &Algo::Breshenham;
}

void RepeatRendedObject::init() {
    vertices = {
        -450.0f,-450.0f,0.0f,
        -450.0f,-450.0f+pixelSize,0.0f,
        -450.0f+pixelSize,-450.0f+pixelSize,0.0f,
        -450.0f+pixelSize,-450.0f,0.0f
    };

    indexes = {
        0,1,2,
        0,2,3
    };
}
void RepeatRendedObject::renderPipline(const glm::mat4& project) {
    if(InputHandler::getMouseL()) {
        if(InputHandler::getMouseDownL()) {
            x0 = floor( (InputHandler::getMouseX() - translate.x) / ((float)pixelSize) * scale.x);
            y0 = floor(((float)CanvasSize - InputHandler::getMouseY() - translate.y) / ((float)pixelSize)* scale.x);
        } else {  
            int xn = floor(InputHandler::getMouseX() / (float)pixelSize);
            int yn = floor(((float)CanvasSize - InputHandler::getMouseY() - translate.y) / ((float)pixelSize)* scale.x);
            if(xn!=x1 || yn != y1) {
                x1 = xn; y1 = yn;
                (algo.*genFunc)(x0,y0,x1,y1);
            }
        }
    } else {
        if(InputHandler::getKeyDown(GLFW_KEY_C)) {
            genFunc = &Algo::GetRound;
        }
        if(InputHandler::getKeyDown(GLFW_KEY_B)) {
            genFunc = &Algo::Breshenham;
        }
        if(InputHandler::getKeyDown(GLFW_KEY_D)) {
            genFunc = &Algo::DDA;
        }
        if(InputHandler::getKeyDown(GLFW_KEY_E)) {
            algo.clear();
        }
        x0 = 0; y0 = 0;
        x1 = 0; y1 = 0;
        if(InputHandler::getMouseR()) {
            if(InputHandler::getMouseDownR()) {
                x0 = InputHandler::getMouseX();
                y0 = InputHandler::getMouseY();
            } else {
                x1 = InputHandler::getMouseX();
                y1 = InputHandler::getMouseY();
                translate.x += (x1 - x0);
                translate.y += (y0 - y1);
                x0 = x1;
                y0 = y1;
            }
        } else {
            float scr = InputHandler::getScrollOffsetY();
            if(scr != 0.0) {
                if(scr == 1.0f) {
                    scale *= 1.1;
                } else if(scr == -1.0f) {
                    scale *= 0.91f;
                }
                if(scale.x < 1.0) {
                    scale.x = 1.0; scale.y = 1.0; scale.z = 1.0;
                }

                if(scale.x > 40.0) {
                    scale.x = 40.0; scale.y = 40.0; scale.z = 40.0;
                }
            } else if(InputHandler::getKeyDown(GLFW_KEY_H)) {
                translate = glm::vec3(0.0f,0.0f,0.0f);
                scale = glm::vec3(1.0f,1.0f,1.0f);
            }
        }
    }

    float maxOffset = (scale.x - 1.0f) * 450;

    if(translate.x > maxOffset) translate.x =maxOffset;
    if(translate.x < -maxOffset) translate.x = -maxOffset;
    if(translate.y > maxOffset) translate.y = maxOffset;
    if(translate.y < -maxOffset) translate.y = -maxOffset;

    for(auto beg = algo.getResIter(); beg != algo.end(); ++beg) {
        glm::mat4 transfromMatrix(1.0f);
        glm::vec3 translate2  = translate;
        translate2.x += pixelSize * beg->first  * scale.x;
        translate2.y += pixelSize * beg->second * scale.y;

        transfromMatrix = glm::translate(transfromMatrix,translate2);
        transfromMatrix = glm::scale(transfromMatrix,scale);
        transfromMatrix = project * transfromMatrix;

        glUseProgram(shaderProgram);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"MATRIX_MVP"),1,GL_FALSE,glm::value_ptr(transfromMatrix));
        glBindVertexArray(VAO);
        glDrawElements(rendType,indexes.size(),GL_UNSIGNED_INT,0);
        glBindVertexArray(0);
    }
}
    