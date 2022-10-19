//
//  car.h
//  CG_project
//
//  Created by OYXY on 2020/12/16.
//  Copyright © 2020 OYXY. All rights reserved.
//

#ifndef Car_h
#define Car_h
#include "../Framework/Interface/Object.h"

string const carPath = "../Resources/Lancia Delta/Material/lacia_delta.obj";

/**
class Car inherit class Object, and is used to load the car model and set the dynamic position (model matrix).
*/
class Car: public Object
{
public:
    Car();
    ~Car(){};
    
    int carState = 1;
    
    float carVel = 1.2f;
    float carDist = 0.0f;
    
    float carRotate = 0.0f;
    float carRotateVel = 12.0f;
    
    float carDownVel = 0.2f;
    float carDownDist = 0.0f;
    
    glm::mat4 getModel();
    
};

Car::Car():Object(carPath){};

//the animation of the car
glm::mat4 Car::getModel()
{
    glm::mat4 model = glm::mat4(1.0f);
    
    //if isMove equals to 1, the car start moving
    if(MyScene::isMove == 1){
        switch(carState){
            case 1: //go straight
                carDist += carVel * MyScene::deltaTime;
                model = glm::translate(model, glm::vec3(-carDist, 0.0f, 0.0f));
                if(carDist > 6.0f){
                    carState = 2;
                    carDist = 0.0f;
                }
                break;
            
            case 2: //turn around
                carRotate += carRotateVel * MyScene::deltaTime;
                model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.8f));
                model = glm::rotate(model, glm::radians(carRotate), glm::vec3(0.0f, 1.0f, 0.0f));
                model = glm::translate(model, glm::vec3(-2.0f, 0.0f, -1.8f));
                model = glm::translate(model, glm::vec3(-6.0f, 0.0f, 0.0f));
                
                //if turned 90 degrees, change to state 3
                if(carRotate > 90.0f){
                    carState = 3;
                    carRotate = 0.0f;
                }
                break;
            
            case 3: //go straight
                carDist += carVel * MyScene::deltaTime;
                model = glm::translate(model, glm::vec3(0.0f, 0.0f, carDist));
            
                model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.8f));
                model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                model = glm::translate(model, glm::vec3(-2.0f, 0.0f, -1.8f));
                model = glm::translate(model, glm::vec3(-6.0f, 0.0f, 0.0f));
                if(carDist > 10.8f){
                    carState = 4;
                    carDist = 0.0f;
                }
                break;
            
            case 4: //go down and disappear under the ground
                carDownDist += carDownVel * MyScene::deltaTime;
                model = glm::translate(model, glm::vec3(0.0f, -carDownDist, 0.0f));
            
                model = glm::translate(model, glm::vec3(0.0f, 0.0f, 10.8f));
                model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.8f));
                model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                model = glm::translate(model, glm::vec3(-2.0f, 0.0f, -1.8f));
                model = glm::translate(model, glm::vec3(-6.0f, 0.0f, 0.0f));
            
                if(carDownDist > 0.5){
                    carState = 5;
                    carDownDist = 0.0f;
                }
                break;
            
            case 5: //go up and re-appear in the start position
                carDownDist += carDownVel * MyScene::deltaTime;
                model = glm::translate(model, glm::vec3(0.0f, carDownDist, 0.0f));
                model = glm::translate(model, glm::vec3(3.0, -0.5f, 0.0f));
                if(carDownDist > 0.5){
                    carState = 6;
                    carDownDist = 0.0f;
                }
                break;
            
            case 6: //go straight untill arrive the cornor, then change to state 2, turn around
                carDist += carVel * MyScene::deltaTime;
                model = glm::translate(model, glm::vec3(-carDist, 0.0f, 0.0f));
                if(carDist > 9.0f){
                    carState = 2;
                    carDist = 0.0f;
                }
                model = glm::translate(model, glm::vec3(3.0f, 0.0f, 0.0f));
                break;
            
            default:
                break;
        }
    }
    
    //set the original position of the car
    model = glm::translate(model, glm::vec3(8.0f, 0.1f, 0.2f));
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f)); //scale it down
    
    return model;
};

#endif /* Car_h */
