#include "TransformObject.h"
#include "InputHandler.h"
#include "Logger.h"

TransfromObject::TransfromObject(GLenum drawT, GLenum rendT, int shader, unsigned int srcsize) : 
    RenderableObject(drawT,rendT,shader)
{
    srcSize = srcsize;
    inputx0=0; inputy0=0;
    inputx1=0; inputy1=0;
}

TransfromObject::~TransfromObject() {}

void TransfromObject::getTransfromInfo() {
    if(InputHandler::getMouseL()) {

    } else if(InputHandler::getMouseR()) {
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

    if(InputHandler::getMouseUpR()) {
        inputx0 = 0; inputy0 = 0;
        inputx1 = 0; inputy1 = 0;
    }

    float maxOffset = (scale.x - 1.0f) * (float)srcSize / 2.0;

    if(translate.x > maxOffset) translate.x =maxOffset;
    if(translate.x < -maxOffset) translate.x = -maxOffset;
    if(translate.y > maxOffset) translate.y = maxOffset;
    if(translate.y < -maxOffset) translate.y = -maxOffset;
}

void TransfromObject::renderPipline(const glm::mat4& project) {
    
    getTransfromInfo();

    RenderableObject::renderPipline(project);
}