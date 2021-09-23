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
    float hp = (float)pixelSize / 2.0;
    vertices = {
        -hp,-hp,0.0f,
        -hp,hp,0.0f,
        hp,hp,0.0f,
        hp,-hp,0.0f
    };

    indexes = {
        0,1,2,
        0,2,3
    };
}
void RepeatRendedObject::renderPipline(const glm::mat4& project) {
    float hp = (float)pixelSize / 2.0;
    float hc = (float)CanvasSize / 2.0;
    if(InputHandler::getMouseL()) {
        float xTrans = InputHandler::getMouseX() + hc * scale.x - hc - translate.x;
        float yTrans = (float)CanvasSize - InputHandler::getMouseY() + hc * scale.y - hc - translate.y;
        if(InputHandler::getMouseDownL()) {
            x0 = floor(xTrans / ((float)pixelSize * scale.x));
            y0 = floor(yTrans / ((float)pixelSize * scale.y));

        } else {  
            int xn = floor(xTrans / ((float)pixelSize * scale.x));
            int yn = floor(yTrans / ((float)pixelSize * scale.y));
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
                inputx0 = InputHandler::getMouseX();
                inputy0 = InputHandler::getMouseY();
            } else {
                inputx1 = InputHandler::getMouseX();
                inputy1 = InputHandler::getMouseY();
                translate.x += (inputx1 - inputx0);
                translate.y += (inputy0 - inputy1);
                inputx0 = inputx1;
                inputy0 = inputy1;
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

    if(InputHandler::getMouseUpR()) {
        inputx0 = 0; inputx1 = 0;
        inputy0 = 0; inputy1 = 0;
    }

    float maxOffset = (scale.x - 1.0f) * 450;

    if(translate.x > maxOffset) translate.x =maxOffset;
    if(translate.x < -maxOffset) translate.x = -maxOffset;
    if(translate.y > maxOffset) translate.y = maxOffset;
    if(translate.y < -maxOffset) translate.y = -maxOffset;

    for(auto beg = algo.getResIter(); beg != algo.end(); ++beg) {
        glm::mat4 transfromMatrix(1.0f);
        glm::vec3 translate2  = translate;//glm::vec3(0,0,0);
        translate2.x += pixelSize * beg->first  * scale.x - (450.0f - hp) * scale.x;
        translate2.y += pixelSize * beg->second * scale.y - (450.0f - hp) * scale.y;

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
    