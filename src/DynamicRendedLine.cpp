#include "DynamicRendedLine.h"
#include "InputHandler.h"

DynamicRendedLine::DynamicRendedLine(GLenum drawT, GLenum rendT, int shader, unsigned int srcsize) :
    RenderableObject(drawT,rendT,shader)
{
    srcSize = srcsize;
}

DynamicRendedLine::~DynamicRendedLine() {}

void DynamicRendedLine::renderPipline() {
    if(InputHandler::getMouseL()) {
        if(InputHandler::getMouseDownL()) {
            x0 = InputHandler::getMouseX() / (float)srcSize;
            y0 = ((float)srcSize - InputHandler::getMouseY()) / (float)srcSize;
            x0 = x0 * 2 - 1;
            y0 = y0 * 2 - 1;
        } else {
            x1 = InputHandler::getMouseX() / (float)srcSize;
            y1 = ((float)srcSize - InputHandler::getMouseY()) / (float)srcSize;
            x1 = x1 * 2 - 1;
            y1 = y1 * 2 - 1;
            vertices.clear();
            vertices.push_back(x0);vertices.push_back(y0);vertices.push_back(0.0f);
            vertices.push_back(x1);vertices.push_back(y1);vertices.push_back(0.0f);
            this->bindData();
            glLineWidth(2);
            RenderableObject::renderPipline();
        }
    }
}