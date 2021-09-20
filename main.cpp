#include <iostream>
#include "Window.h"
#include "init.h"

int main(int argc, char** argv) {
    initGLFW(3,3);

    Window win(900,900,"Rasterization line, Press B Bresenham, D DDA, C Circle");
    win.initWindow();
    win.setUpRendProp();
    win.mainLoop();

    return 0;
}
