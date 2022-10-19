//
//  plane.h
//  CG_project
//
//  Created by OYXY on 2020/12/15.
//  Copyright © 2020 OYXY. All rights reserved.
//

#ifndef Plane_h
#define Plane_h

#include "../Framework/Interface/Object.h"

string const planePath = "../Resources/plane/bixler.obj";

/**
class Plane inherit class Object, and is used to load the airplane model and set the dynamic position (model matrix).
*/
class Plane: public Object
{
public:
    Plane();
    ~Plane(){};
    
    float turnVel = 9.0f;
    float turnRadium = 2.0f;
    float rotateAngle = 0.0f;
    float rotateVel = 8.0f;
    
    glm::mat4 getModel();
};

Plane::Plane():Object(planePath){};

//the animation of the airplane
glm::mat4 Plane::getModel()
{
    glm::mat4 model = glm::mat4(1.0f);
    rotateAngle += rotateVel * MyScene::deltaTime;
    
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotateVel*(float)glfwGetTime()), glm::vec3(0.0f, -1.0f, 0.0f));
    model = glm::translate(model, glm::vec3(-5.0f, 7.0f, 0.0f));
    
    model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.02f)); //scale it down

    return model;
};

#endif /* Plane_h */
