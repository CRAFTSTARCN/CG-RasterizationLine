#include "TransformObject.h"
#include "InputHandler.h"
#include "Logger.h"

TransfromObject::TransfromObject(GLenum drawT, GLenum rendT, int shader) : 
    RenderableObject(drawT,rendT,shader)
{
    x0=0; y0=0;
    x1=0; y1=0;
}

TransfromObject::~TransfromObject() {}

void TransfromObject::renderPipline(const glm::mat4& project) {
    if(InputHandler::getMouseL()) {

    } else if(InputHandler::getMouseR()) {
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

    if(InputHandler::getMouseUpR()) {
        x0 = 0; y0 = 0;
        x1 = 0; y1 = 0;
    }

    float maxOffset = (scale.x - 1.0f) * 450;

    if(translate.x > maxOffset) translate.x =maxOffset;
    if(translate.x < -maxOffset) translate.x = -maxOffset;
    if(translate.y > maxOffset) translate.y = maxOffset;
    if(translate.y < -maxOffset) translate.y = -maxOffset;


    RenderableObject::renderPipline(project);
}