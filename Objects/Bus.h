//
//  Bus.h
//  CG_project
//
//  Created by OYXY on 2020/12/14.
//  Copyright © 2020 OYXY. All rights reserved.
//

#ifndef Bus_h
#define Bus_h

#include "../Framework/Interface/Object.h"

string const busPath = "../Resources/bus/bus_2.obj";

/**
class Bus inherit class Object, and is used to load the bus model and set the dynamic position (model matrix).
*/
class Bus: public Object
{
public:
    Bus();
    ~Bus(){};
    
    int busState = 1;
    float busVel = 0.8f;
    float busDist = 0.0f;
    float busRotate = 0.0f;
    float rotateVel = 12.0f;
    
    glm::mat4 getModel();
};

Bus::Bus():Object(busPath){};

//the animation of the bus
glm::mat4 Bus::getModel()
{
    glm::mat4 model = glm::mat4(1.0f);
    
    //if isMove equal to 1, the bus start moving
    if(MyScene::isMove == 1){
        switch(busState){
            case 1: //go straight
                busDist += busVel * MyScene::deltaTime;
                model = glm::translate(model, glm::vec3(-busDist, 0.0f, 0.0f));
                if(busDist > 8.8f){
                    busState = 2;
                    busDist = 0.0f;
                }
                break;
            
            case 2: //turn around
                busRotate += rotateVel * MyScene::deltaTime;
                model = glm::translate(model, glm::vec3(-4.8f, 0.0f, 3.5f));
                model = glm::rotate(model, glm::radians(busRotate), glm::vec3(0.0f, 1.0f, 0.0f));
                model = glm::translate(model, glm::vec3(4.8f, 0.0f, -3.5f));
                model = glm::translate(model, glm::vec3(-8.8f, 0.0f, 0.0f));
                if(busRotate > 90.0f){
                    busState = 3;
                }
                break;
                
            case 3: //go straigh
                busDist += busVel * MyScene::deltaTime;
                model = glm::translate(model, glm::vec3(0.0f, 0.0f, busDist));
                model = glm::translate(model, glm::vec3(-4.8f, 0.0f, 3.5f));
                model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                model = glm::translate(model, glm::vec3(4.8f, 0.0f, -3.5f));
                model = glm::translate(model, glm::vec3(-8.8f, 0.0f, 0.0f));
                if(busDist > 6.0f){
                    busState = 4;
                }
                break;
            
            case 4: //stop at the bus parking area
                model = glm::translate(model, glm::vec3(0.0f, 0.0f, 6.0f));
                model = glm::translate(model, glm::vec3(-4.8f, 0.0f, 3.5f));
                model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                model = glm::translate(model, glm::vec3(4.8f, 0.0f, -3.5f));
                model = glm::translate(model, glm::vec3(-8.8f, 0.0f, 0.0f));
                break;
            
            default:
                break;
        }
    }
    
    //set the original position of the bus
    model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, -1.0f, 0.0f));
    model = glm::translate(model, glm::vec3(-4.0f, 0.0f, 0.5f));
    model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f)); //scale it down
    
    return model;
};

#endif /* Bus_h */
