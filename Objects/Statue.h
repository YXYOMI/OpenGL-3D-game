//
//  Statue.h
//  CG_project
//
//  Created by OYXY on 2020/12/17.
//  Copyright © 2020 OYXY. All rights reserved.
//

#ifndef Statue_h
#define Statue_h

#include "../Framework/Interface/Object.h"

string const statuePath = "../Resources/statue/statue.obj";

/**
class Statue inherit class Object, and is used to load the statue model and set the dynamic position (model matrix).
*/
class Statue: public Object
{
public:
    Statue();
    ~Statue(){};
    
    float statueVel = 16.0f;
    
    glm::mat4 getModel();
    
};

Statue::Statue():Object(statuePath){};

//the animation of the statue
glm::mat4 Statue::getModel()
{
    glm::mat4 model = glm::mat4(1.0f);
    
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -7.0f));
    
    if(MyScene::isMove == 1){
        model = glm::rotate(model, glm::radians(statueVel*(float)glfwGetTime()), glm::vec3(0.0f, 1.0f, 0.0f));
    }
    
    //set the original position of the statue
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.001f,0.001f, 0.001f)); //scale it down
    
    return model;
};


#endif /* Statue_h */
