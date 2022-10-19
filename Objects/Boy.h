//
//  Boy.h
//  CG_project
//
//  Created by OYXY on 2020/12/15.
//  Copyright © 2020 OYXY. All rights reserved.
//

#ifndef Boy_h
#define Boy_h

#include "../Framework/Interface/Object.h"

string const boyPath = "../Resources/little_boy/Lt_boy.obj";

class Boy: public Object
{
public:
    Boy();
    ~Boy(){};
    
    static float jumpVel;// = 0.01f;
    float height = 0.05f;
    static float jumpHeight;// = 0.0f;
    glm::mat4 getModel();
};

float Boy::jumpVel = 0.03f;
float Boy::jumpHeight = 0.0f;

Boy::Boy():Object(boyPath){};
glm::mat4 Boy::getModel()
{
    //glm::vec3 sunDirection(radium * cos(glfwGetTime() * sunVelocity), radium * sin(glfwGetTime() * sunVelocity), 0.0f);
    //getDirection(sunDirection);
    
    float currentFrame = glfwGetTime();
    MyScene::deltaTime = currentFrame - MyScene::lastFrame;
    MyScene::lastFrame = currentFrame;
    
    if(jumpHeight > height){
        jumpVel = -jumpVel;
        jumpHeight = height;
    }else if(jumpHeight < 0){
        jumpVel = -jumpVel;
        jumpHeight = 0.0f;
    }
    jumpHeight += jumpVel* MyScene::deltaTime;
    //std::cout<<jumpHeight<<std::endl;
    //std::cout<<jumpVel<<std::endl;
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3((-4.0f), jumpHeight, 1.0f));
    model = glm::scale(model, glm::vec3(0.05f));
    return model;
};

#endif /* Boy_h */
