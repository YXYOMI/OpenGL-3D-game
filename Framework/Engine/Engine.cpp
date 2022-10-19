//
//  Engine.cpp
//  CG_project
//
//  Created by OYXY on 2020/12/13.
//  Copyright © 2020 OYXY. All rights reserved.
//

#include <stdio.h>
#include "Engine.h"

const char* Engine::SCR_TITLE = "";
int Engine::SCR_WIDTH = 0;
int Engine::SCR_HEIGHT = 0;
GLFWwindow* Engine::window = NULL;

//initilize the window
Engine::Engine(const char *title, const int& windowWidth, const int& windowHeight)
{
    Engine::SCR_WIDTH = windowWidth;
    Engine::SCR_HEIGHT = windowHeight;
    Engine::SCR_TITLE = title;
    
    glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    
}


