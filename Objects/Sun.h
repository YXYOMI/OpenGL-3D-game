//
//  Sun.h
//  CG_project
//
//  Created by OYXY on 2020/12/14.
//  Copyright © 2020 OYXY. All rights reserved.
//

#ifndef Sun_h
#define Sun_h
#include "../Framework/Interface/Object.h"

string const sunPath = "../Resources/sun/sun.obj";

/**
class Sun inherit class Object, and is used to load the sun model and set the dynamic position (model matrix).
*/
class Sun: public Object
{
public:
    Sun();
    ~Sun(){};
    
    float sunVel = 0.5f;
    float sunRotate = 0.0f;
    float sunVelocity = 0.08;
    float radium = 9.5f;
    static glm::vec3 sunDirection;
    
    void setDirLight(Shader shader);
    glm::mat4 getModel();
    glm::vec3 setDirection();

};

glm::vec3 Sun::sunDirection(0.0f, 0.0f, 0.0f);

Sun::Sun():Object(sunPath){};

//the aninmation of the sun
glm::mat4 Sun::getModel()
{
    glm::vec3 sunDirection = setDirection();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, sunDirection);

    model = glm::scale(model, glm::vec3(0.1f)); //scale it down
    return model;
};

glm::vec3 Sun::setDirection(){
    float x = radium * cos(glfwGetTime() * sunVelocity);
    float y = radium * sin(glfwGetTime() * sunVelocity);
    
    // if the sun move below the horizon line, set isNight to 0, else set to 1
    if(y>0){
        MyScene::isNight = 0;
    }else{
        MyScene::isNight = 1;
    }
    
    glm::vec3 sunDirection(radium * cos(glfwGetTime() * sunVelocity), radium * sin(glfwGetTime() * sunVelocity), 0.0f);
    
    return sunDirection;
}

//set the sunlight
void Sun::setDirLight(Shader shader){
    shader.use();
    glm::vec3 sunDirection = setDirection();
    shader.setVec3("dirLight.direction", -sunDirection);
    shader.setVec3("dirLight.ambient", 0.1f, 0.1f, 0.1f);
    shader.setVec3("dirLight.diffuse", 0.8f, 0.8f, 0.8f);
    shader.setVec3("dirLight.specular", 1.0f, 1.0f, 1.0f);
}

#endif /* Sun_h */
