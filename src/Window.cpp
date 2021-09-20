#include "Window.h"
#include "Logger.h"
#include "InputHandler.h"
#include "SimpleShaderCompiler.h"
#include "RepeatRendedObject.h"
#include "iostream"

Window::Window(unsigned int wd, unsigned int ht, const std::string& name) {
    windowWidth = wd;
    windowHeight = ht;
    window = glfwCreateWindow(wd, ht, name.c_str(), NULL, NULL);

    if(window == nullptr) {
        Logger::ERROR.log("Fail to create window");
        exit(-1);
    }

    initGLAD(window);
}

Window::~Window() {
    for(auto* obj : objects) {
        delete obj;
    }

    glfwTerminate();
}

void Window::initWindow() {
    InputHandler::init(window);

    auto defaultSizeCallback = [](GLFWwindow* window, int width, int height){
        glViewport(0, 0, width, height);
    };

    glfwSetFramebufferSizeCallback(window, defaultSizeCallback);
}

void Window::setUpRendProp() {
    int vert, frag, shaderProgram,vertTrans,shaderProgram2;
    try {
        vert = SimpleShaderCompiler::compile("./shaders/vert.vert",GL_VERTEX_SHADER);
        frag = SimpleShaderCompiler::compile("./shaders/frag.frag",GL_FRAGMENT_SHADER);
        vertTrans = SimpleShaderCompiler::compile("./shaders/reposVert.vert",GL_VERTEX_SHADER);
        shaderProgram = SimpleShaderCompiler::link(vert,frag);
        shaderProgram2 = SimpleShaderCompiler::link(vertTrans,frag);

        glDeleteShader(vert);
        glDeleteShader(vertTrans);
        glDeleteShader(frag);
    }
    catch(Throwable& e) {
        Logger::ERROR.log(e.type());
        Logger::ERROR.log(e.what());
        throw e;
    }

    RenderableObject* obj = new RenderableObject(GL_STATIC_DRAW, GL_LINES, shaderProgram);
    
    obj->init([](RenderableObject* obj){
        int pix_num = 60;

        float step = 2.0 / (float)pix_num;


        float cury = -1;
        int idx=0;

        for(int i = 1; i<pix_num; ++i) {
            cury += step;
            obj->vertices.push_back(1);
            obj->vertices.push_back(cury);
            obj->vertices.push_back(0);
            obj->indexes.push_back(idx++);

            obj->vertices.push_back(-1);
            obj->vertices.push_back(cury);
            obj->vertices.push_back(0);
            obj->indexes.push_back(idx++);

            obj->vertices.push_back(cury);
            obj->vertices.push_back(1);
            obj->vertices.push_back(0);
            obj->indexes.push_back(idx++);

            obj->vertices.push_back(cury);
            obj->vertices.push_back(-1);
            obj->vertices.push_back(0);
            obj->indexes.push_back(idx++);
        }
    });
    
    obj->bindData();

    RenderableObject* obj2 = new RenderableObject(GL_STATIC_DRAW, GL_LINE_LOOP, shaderProgram);

    obj2->vertices = {
        1,1,0,
        1,-1,0,
        -1,-1,0,
        -1,1,0
    };

    obj2->indexes = {
        0,1,2,3
    };

    obj2->bindData();

    RenderableObject* obj3 = new RepeatRendedObject(GL_STATIC_DRAW,GL_TRIANGLE_FAN,shaderProgram2,900,15);
    obj3->init();
    obj3->bindData();

    objects.push_back(obj);
    objects.push_back(obj2);
    objects.push_back(obj3);
}

void Window::renderProcess() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLineWidth(1);
    for(int i=0; i<objects.size(); ++i) {
        objects[i]->renderPipline();
    }
    glfwSwapBuffers(window);
}

void Window::mainLoop() {
    while(!glfwWindowShouldClose(window)) {
        renderProcess();
        if(InputHandler::getKeyDown(GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(window,true);
        }
        InputHandler::clearStatus();
        glfwPollEvents();
    }
}