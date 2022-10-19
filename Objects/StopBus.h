//
//  StopBus.h
//  CG_project
//
//  Created by OYXY on 2020/12/17.
//  Copyright © 2020 OYXY. All rights reserved.
//

#ifndef StopBus_h
#define StopBus_h

#include "../Framework/Interface/Object.h"

/**
class StopBus inherit class Object, and is used to load another bus model and set the dynamic position (model matrix).
*/
class StopBus: public Object
{
public:
    StopBus();
    ~StopBus(){};
    
    int busState = 1;
    float busVel = 0.8f;
    float busDist = 0.0f;
    float busRotate = 0.0f;
    float rotateVel = 12.0f;
    
    glm::mat4 getModel();
    
};

StopBus::StopBus():Object(busPath){};

//the animation of the bus
glm::mat4 StopBus::getModel()
{
    glm::mat4 model = glm::mat4(1.0f);
    
    //if isMove equal to 1, the bus would start moving
    if(MyScene::isMove == 1){
        switch(busState){
            case 1: //go straight
                busDist += busVel * MyScene::deltaTime;
                model = glm::translate(model, glm::vec3(busDist, 0.0f, 0.0f));
                if(busDist > 4.6f){
                    busState = 2;
                    busDist = 0.0f;
                }
                break;
                
            case 2: //turn around
                busRotate += rotateVel * MyScene::deltaTime;
                model = glm::translate(model, glm::vec3(-1.7f, 0.0f, 10.2f));
                model = glm::rotate(model, glm::radians(busRotate), glm::vec3(0.0f, 1.0f, 0.0f));
                model = glm::translate(model, glm::vec3(1.7f, 0.0f, -10.2f));
                model = glm::translate(model, glm::vec3(4.6f, 0.0f, 0.0f));
            
                //when turn 90 degrees, change to state 3
                if(busRotate > 90.0f){
                    busState = 3;
                    busRotate = 0.0f;
                }
                break;
                
            case 3: //go straight
                busDist += busVel * MyScene::deltaTime;
                model = glm::translate(model, glm::vec3(0.0f, 0.0f, -busDist));
            
                model = glm::translate(model, glm::vec3(-1.7f, 0.0f, 10.2f));
                model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                model = glm::translate(model, glm::vec3(1.7f, 0.0f, -10.2f));
                model = glm::translate(model, glm::vec3(4.6f, 0.0f, 0.0f));
            
                if(busDist > 3.5f){
                    busState = 4;
                    busDist = 0.0f;
                }
                break;
                
            case 4: //turn around
                busRotate += rotateVel * MyScene::deltaTime;
                model = glm::translate(model, glm::vec3(-1.7f, 0.0f, 6.7f));
                model = glm::rotate(model, glm::radians(busRotate), glm::vec3(0.0f, 1.0f, 0.0f));
                model = glm::translate(model, glm::vec3(1.7f, 0.0f, -6.7f));
            
                model = glm::translate(model, glm::vec3(0.0, 0.0f, -3.5f));
                model = glm::translate(model, glm::vec3(-1.7f, 0.0f, 10.2f));
                model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                model = glm::translate(model, glm::vec3(1.7f, 0.0f, -10.2f));
                model = glm::translate(model, glm::vec3(4.6f, 0.0f, 0.0f));
            
                //when turn 90 degrees, change to state5
                if(busRotate > 90.0f){
                    busState = 5;
                    busRotate = 0.0f;
                }
                break;
            
            case 5: //go straight
                busDist += busVel * MyScene::deltaTime;
                model = glm::translate(model, glm::vec3(-busDist, 0.0f, 0.0f));
            
                model = glm::translate(model, glm::vec3(-1.7f, 0.0f, 6.7f));
                model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                model = glm::translate(model, glm::vec3(1.7f, 0.0f, -6.7f));
            
                model = glm::translate(model, glm::vec3(0.0, 0.0f, -3.5f));
                model = glm::translate(model, glm::vec3(-1.7f, 0.0f, 10.2f));
                model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                model = glm::translate(model, glm::vec3(1.7f, 0.0f, -10.2f));
                model = glm::translate(model, glm::vec3(4.6f, 0.0f, 0.0f));
            
                if(busDist > 1.5f){
                    busState = 6;
                }
            break;
            
            case 6: //stop at front of thee bus station
                model = glm::translate(model, glm::vec3(-1.5f, 0.0f, 0.0f));
            
                model = glm::translate(model, glm::vec3(-1.7f, 0.0f, 6.7f));
                model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                model = glm::translate(model, glm::vec3(1.7f, 0.0f, -6.7f));
            
                model = glm::translate(model, glm::vec3(0.0, 0.0f, -3.5f));
                model = glm::translate(model, glm::vec3(-1.7f, 0.0f, 10.2f));
                model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                model = glm::translate(model, glm::vec3(1.7f, 0.0f, -10.2f));
                model = glm::translate(model, glm::vec3(4.6f, 0.0f, 0.0f));
                break;
                
            default:
                break;
        }
    }
    
    model = glm::translate(model, glm::vec3(-6.3f, 0.0f, 11.0f));//set the original position of the bus
    model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f)); //scale it down
    
    return model;
};


#endif /* StopBus_h */
