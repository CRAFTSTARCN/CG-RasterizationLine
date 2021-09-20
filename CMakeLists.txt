cmake_minimum_required(VERSION 3.0.0)
project(BresenhamLineSim VERSION 0.1.0)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

include_directories(include)
include_directories(headers)
link_directories(lib)

FILE(GLOB ALL_INCLUDES "./headers/*.h" "./headers/*.hpp")
FILE(GLOB ALL_SOURCES "./src/*.cpp")

set(SOURCE_FILES main.cpp glad.c 
                 headers/Exception.hpp
                 headers/init.h
                 headers/Logger.h
                 headers/RenderableObject.h
                 headers/SimpleShaderCompiler.h
                 headers/Algo.h
                 headers/inputHandler.h
                 headers/window.h
                 headers/RepeatRendedObject.h
                 
                 src/Logger.cpp
                 src/RenderableObject.cpp
                 src/SimpleShaderCompiler.cpp
                 src/inputHandler.cpp
                 src/Window.cpp
                 src/Algo.cpp
                 src/RepeatRendedObject.cpp)

add_executable(BresenhamLineSim ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} glfw3)