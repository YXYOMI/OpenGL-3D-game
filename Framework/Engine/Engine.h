//
//  Engine.h
//  CG_project
//
//  Created by OYXY on 2020/12/13.
//  Copyright © 2020 OYXY. All rights reserved.
//

#ifndef Engine_h
#define Engine_h
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

/**
 class Engine is used to load the basic libraries to support the later programe and initialize the basic window.
 */
class Engine
{
public:
    Engine(const char *title, const int& windowWidth, const int& windowHeight);
    virtual ~Engine(){};
    
    static const char* SCR_TITLE;
    static int SCR_WIDTH;
    static int SCR_HEIGHT;
    static GLFWwindow* window;
    
};

#endif /* Engine_h */
