#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "RepeatRendedObject.h"
#include "InputHandler.h"
#include "Logger.h"

RepeatRendedObject::RepeatRendedObject(GLenum drawT, GLenum rendT, int shader,
                                      unsigned int srcsz, unsigned int pixSize)
                    : RenderableObject(drawT,rendT,shader), translate(1.0f), algo()
{
    CanvasSize = srcsz;
    pixelSize = pixSize;
    genFunc = &Algo::Breshenham;
}

void RepeatRendedObject::init() {
    pix = 2.0f * (float)pixelSize/(float)CanvasSize;
    vertices = {
        -1.0f,-1.0f,0.0f,
        -1.0f,-1.0f+pix,0.0f,
        -1.0f+pix,-1.0f+pix,0.0f,
        -1.0f+pix,-1.0f,0.0f
    };

    indexes = {
        0,1,2,
        0,2,3
    };
}
void RepeatRendedObject::renderPipline() {
    glm::mat4 aft;
    if(InputHandler::getMouseL()) {
        if(InputHandler::getMouseDownL()) {
            x0 = floor(InputHandler::getMouseX() / (float)pixelSize);
            y0 = floor(((float)CanvasSize - InputHandler::getMouseY()) / (float)pixelSize);
        } else {  
            int xn = floor(InputHandler::getMouseX() / (float)pixelSize);
            int yn = floor(((float)CanvasSize - InputHandler::getMouseY()) / (float)pixelSize);
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
    }

    for(auto beg = algo.getResIter(); beg != algo.end(); ++beg) {
        glUseProgram(shaderProgram);
        aft = glm::translate(translate,glm::vec3(beg->first*pix,beg->second*pix,0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"translate"),1,GL_FALSE,glm::value_ptr(aft));
        glBindVertexArray(VAO);
        glDrawElements(rendType,indexes.size(),GL_UNSIGNED_INT,0);
        glBindVertexArray(0);
    }
}
    