//
//  Scene.h
//  CG_project
//
//  Created by OYXY on 2020/12/13.
//  Copyright © 2020 OYXY. All rights reserved.
//

#ifndef Scene_h
#define Scene_h
#include "Engine.h"
#include "../Utility/Camera.h"

/**
 class Scene inherit class Engine. it is used to draw the window and initilize the camera
 */
class Scene : public Engine{
public:
    Scene(const char *title, const int& windowWidth, const int& windowHeight);
    virtual ~Scene(){};
    
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static void processInput(GLFWwindow *window);
    static float deltaTime;
    static float lastFrame;
    static Camera camera;
    
    //should be overrided by MyScene
    virtual void Run() = 0;
    
};



#endif /* Scene_h */
