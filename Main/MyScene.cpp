//
//  MyScene.cpp
//  CG_project
//
//  Created by OYXY on 2020/12/13.
//  Copyright © 2020 OYXY. All rights reserved.
//

#include <stdio.h>
#include "MyScene.h"
#include "../Framework/Utility/Shader.h"
#include "../Framework/Utility/Model.h"
#include "../Objects/Town.h"
#include "../Objects/Bus.h"
#include "../Objects/Sun.h"
#include "../Objects/Boy.h"
#include "../Objects/Plane.h"
#include "../Objects/Car.h"
#include "../Objects/StopBus.h"
#include "../Objects/Statue.h"

//initialize the static variable
int MyScene::lightOn = 1;
int MyScene::onPlane = 0;
int MyScene::flashLight = 0;
int MyScene::isMove = 0;
int MyScene::isNight = 1;

glm::vec3 MyScene::orgPosition(1.0f);
glm::vec3 MyScene::planePosition(1.0f);

float MyScene::skyboxVertices[] = {
    // positions
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
};

glm::vec3 MyScene::pointLightPositions[] = {
    glm::vec3(-1.2f, 0.6f, -4.4f),
    glm::vec3(3.4f, 0.5f, -8.1f),
    glm::vec3(2.9f, 0.6f, 7.4f),
    glm::vec3(7.0f, 0.5f, -3.4f),
    glm::vec3(7.0f, 0.5f, 3.0f),
    glm::vec3(-5.2f, 0.6f, 7.4f),
    glm::vec3(-5.2f, 0.6f, 1.0f),
};

//constructor is used to configurate the shaders
MyScene::MyScene(const char *title, const int& windowWidth, const int& windowHeight)
    : Scene(title, windowWidth, windowHeight)
{
    // modelShader configuration
    modelShader.use();
    modelShader.setInt("texture_diffuse1", 0);
    modelShader.setInt("texture_specular1", 1);
    
    // skyboxShader configuration
    skyboxShader.use();
    skyboxShader.setInt("skybox", 0);
}

//draw the whole scene.
void MyScene::Run(){
    std::cout<<"start running..."<<std::endl;
    
    // creat the model objects
    Bus bus;
    StopBus stopBus;
    Town town;
    Sun sun;
    Plane plane;
    Car car;
    Statue statue;
    
    //skybox
    unsigned int skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    
    // load the skybox
    unsigned int cubemapTexture_day = loadCubemap(skyboxFaces_day);
    unsigned int cubemapTexture_night = loadCubemap(skyboxFaces_night);
    
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        processInput(window);

        // render
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // if lightOn equal to 1, turn on the streetlights, else turn off the streeetlights.
        if(lightOn == 1){
            lightsOn(modelShader, pointLightPositions);
        }else{
            lightsOff(modelShader, pointLightPositions);
        }
        
        // if flashLight equal to 1, open the flashlight, else close the flashlight.
        if(flashLight == 1){
            flashlightOn(modelShader);
        }else{
            flashlightOff(modelShader);
        }
        
        // if onPlane equal to 1, set the camera position to the airplane's position.
        if(onPlane == 1){
            camera.Position = glm::vec3(planePosition);
        }
        
        
        modelShader.use();
        
        //set the  projection, view matrix
        glm::mat4 projection = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        view = camera.GetViewMatrix();
        modelShader.setMat4("projection", projection);
        modelShader.setMat4("view", view);
        
        //draw the town
        glm::mat4 model = town.getModel(); //get the model matrix of the town
        modelShader.setMat4("model", model);
        town.Draw(modelShader);
        
        //draw the moving bus (move then stop at the bus parking area)
        model = bus.getModel(); //get the model matrix of the bus
        modelShader.setMat4("model", model);
        bus.Draw(modelShader);
        
        //draw another moving bus (move then sotp at the bus station)
        model = stopBus.getModel(); //get the model matrix of the bus
        modelShader.setMat4("model", model);
        stopBus.Draw(modelShader);
        
        //draw the moving sun
        model = sun.getModel(); //get the model matrix of the sun
        sun.setDirLight(modelShader);
        modelShader.setMat4("model", model);
        sun.Draw(modelShader);
        
        //draw the rotating statue
        model = statue.getModel(); //get the model matrix of the statue
        modelShader.setMat4("model", model);
        statue.Draw(modelShader);
        
        //draw the flying airplane
        glm::vec4 planeVec(0.0f, 0.0f, 0.0f, 1.0f);
        model = plane.getModel(); //get the model matrix of the airplane
        planeVec = model * planeVec;
        planePosition = glm::vec3(planeVec.x, planeVec.y+1.5f, planeVec.z); //get the airplane position and set it as the camera position
        modelShader.setMat4("model", model);
        plane.Draw(modelShader);
        
        //draw the moving car
        model = car.getModel(); //get the position of the car
        modelShader.setMat4("model", model);
        car.Draw(modelShader);
        
        if(onPlane == 0){
            orgPosition = camera.Position;
        }
        
        //draw skybox
        glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
        skyboxShader.use();
        view = glm::mat4(1.0f);
        view = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
        skyboxShader.setMat4("view", view);
        skyboxShader.setMat4("projection", projection);
        // skybox cube
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        if(isNight == 0){
             glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture_day);
        }else{
            glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture_night);
        }
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glDeleteVertexArrays(1, &skyboxVAO);
    glDeleteBuffers(1, &skyboxVBO);
    
    glfwTerminate();
}

//turn on the streetlights
void MyScene::lightsOn(Shader shader, glm::vec3* pointLightPositions){
    shader.use();
    
    // point light 1
    shader.setVec3("pointLights[0].position", pointLightPositions[0]);
    shader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
    shader.setVec3("pointLights[0].diffuse", 1.0f, 0.92f, 0.8f);
    shader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
    shader.setFloat("pointLights[0].constant", 1.0f);
    shader.setFloat("pointLights[0].linear", 0.14);
    shader.setFloat("pointLights[0].quadratic", 0.07);
    // point light 2
    shader.setVec3("pointLights[1].position", pointLightPositions[1]);
    shader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
    shader.setVec3("pointLights[1].diffuse", 1.0f, 0.92f, 0.8f);
    shader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
    shader.setFloat("pointLights[1].constant", 1.0f);
    shader.setFloat("pointLights[1].linear", 0.14);
    shader.setFloat("pointLights[1].quadratic", 0.07);
    // point light 3
    shader.setVec3("pointLights[2].position", pointLightPositions[2]);
    shader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
    shader.setVec3("pointLights[2].diffuse", 1.0f, 0.92f, 0.8f);
    shader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
    shader.setFloat("pointLights[2].constant", 1.0f);
    shader.setFloat("pointLights[2].linear", 0.14);
    shader.setFloat("pointLights[2].quadratic", 0.07);
    // point light 4
    shader.setVec3("pointLights[3].position", pointLightPositions[3]);
    shader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
    shader.setVec3("pointLights[3].diffuse", 1.0f, 0.92f, 0.8f);
    shader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
    shader.setFloat("pointLights[3].constant", 1.0f);
    shader.setFloat("pointLights[3].linear", 0.14);
    shader.setFloat("pointLights[3].quadratic", 0.07);
    //point light 5
    shader.setVec3("pointLights[4].position", pointLightPositions[4]);
    shader.setVec3("pointLights[4].ambient", 0.05f, 0.05f, 0.05f);
    shader.setVec3("pointLights[4].diffuse", 1.0f, 0.92f, 0.8f);
    shader.setVec3("pointLights[4].specular", 1.0f, 1.0f, 1.0f);
    shader.setFloat("pointLights[4].constant", 1.0f);
    shader.setFloat("pointLights[4].linear", 0.14);
    shader.setFloat("pointLights[4].quadratic", 0.07);
    //point light 6
    shader.setVec3("pointLights[5].position", pointLightPositions[5]);
    shader.setVec3("pointLights[5].ambient", 0.05f, 0.05f, 0.05f);
    shader.setVec3("pointLights[5].diffuse", 1.0f, 0.92f, 0.8f);
    shader.setVec3("pointLights[5].specular", 1.0f, 1.0f, 1.0f);
    shader.setFloat("pointLights[5].constant", 1.0f);
    shader.setFloat("pointLights[5].linear", 0.14);
    shader.setFloat("pointLights[5].quadratic", 0.07);
    //point light 7
    shader.setVec3("pointLights[6].position", pointLightPositions[6]);
    shader.setVec3("pointLights[6].ambient", 0.05f, 0.05f, 0.05f);
    shader.setVec3("pointLights[6].diffuse", 1.0f, 0.92f, 0.8f);
    shader.setVec3("pointLights[6].specular", 1.0f, 1.0f, 1.0f);
    shader.setFloat("pointLights[6].constant", 1.0f);
    shader.setFloat("pointLights[6].linear", 0.14);
    shader.setFloat("pointLights[6].quadratic", 0.07);
}

//turn off the streetlights
void MyScene::lightsOff(Shader shader, glm::vec3* pointLightPositions){
    shader.use();
    
    // point light 1
    shader.setVec3("pointLights[0].position", pointLightPositions[0]);
    shader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
    shader.setVec3("pointLights[0].diffuse", 0.0f, 0.0f, 0.0f);
    shader.setVec3("pointLights[0].specular", 0.0f, 0.0f, 0.0f);
    shader.setFloat("pointLights[0].constant", 1.0f);
    shader.setFloat("pointLights[0].linear", 0.09);
    shader.setFloat("pointLights[0].quadratic", 0.032);
    // point light 2
    shader.setVec3("pointLights[1].position", pointLightPositions[1]);
    shader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
    shader.setVec3("pointLights[1].diffuse", 0.0f, 0.0f, 0.0f);
    shader.setVec3("pointLights[1].specular", 0.0f, 0.0f, 0.0f);
    shader.setFloat("pointLights[1].constant", 1.0f);
    shader.setFloat("pointLights[1].linear", 0.09);
    shader.setFloat("pointLights[1].quadratic", 0.032);
    // point light 3
    shader.setVec3("pointLights[2].position", pointLightPositions[2]);
    shader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
    shader.setVec3("pointLights[2].diffuse", 0.0f, 0.0f, 0.0f);
    shader.setVec3("pointLights[2].specular", 0.0f, 0.0f, 0.0f);
    shader.setFloat("pointLights[2].constant", 1.0f);
    shader.setFloat("pointLights[2].linear", 0.09);
    shader.setFloat("pointLights[2].quadratic", 0.032);
    // point light 4
    shader.setVec3("pointLights[3].position", pointLightPositions[3]);
    shader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
    shader.setVec3("pointLights[3].diffuse", 0.0f, 0.0f, 0.0f);
    shader.setVec3("pointLights[3].specular", 0.0f, 0.0f, 0.0f);
    shader.setFloat("pointLights[3].constant", 1.0f);
    shader.setFloat("pointLights[3].linear", 0.09);
    shader.setFloat("pointLights[3].quadratic", 0.032);
    //point light 5
    shader.setVec3("pointLights[4].position", pointLightPositions[4]);
    shader.setVec3("pointLights[4].ambient", 0.05f, 0.05f, 0.05f);
    shader.setVec3("pointLights[4].diffuse", 0.0f, 0.0f, 0.0f);
    shader.setVec3("pointLights[4].specular", 0.0f, 0.0f, 0.0f);
    shader.setFloat("pointLights[4].constant", 1.0f);
    shader.setFloat("pointLights[4].linear", 0.09);
    shader.setFloat("pointLights[4].quadratic", 0.032);
    //point light 6
    shader.setVec3("pointLights[5].position", pointLightPositions[5]);
    shader.setVec3("pointLights[5].ambient", 0.05f, 0.05f, 0.05f);
    shader.setVec3("pointLights[5].diffuse", 0.0f, 0.0f, 0.0f);
    shader.setVec3("pointLights[5].specular", 0.0f, 0.0f, 0.0f);
    shader.setFloat("pointLights[5].constant", 1.0f);
    shader.setFloat("pointLights[5].linear", 0.09);
    shader.setFloat("pointLights[5].quadratic", 0.032);
    //point light 7
    shader.setVec3("pointLights[6].position", pointLightPositions[6]);
    shader.setVec3("pointLights[6].ambient", 0.05f, 0.05f, 0.05f);
    shader.setVec3("pointLights[6].diffuse", 0.0f, 0.0f, 0.0f);
    shader.setVec3("pointLights[6].specular", 0.0f, 0.0f, 0.0f);
    shader.setFloat("pointLights[6].constant", 1.0f);
    shader.setFloat("pointLights[6].linear", 0.09);
    shader.setFloat("pointLights[6].quadratic", 0.032);
    
    /*for(int i=0; i<7; i++){
        shader.setVec3("pointLights[i].position", pointLightPositions[i]);
        shader.setVec3("pointLights[i].ambient", 0.05f, 0.05f, 0.05f);
        shader.setVec3("pointLights[i].diffuse", 0.0f, 0.0f, 0.0f);
        shader.setVec3("pointLights[i].specular", 1.0f, 1.0f, 1.0f);
        shader.setFloat("pointLights[i].constant", 1.0f);
        shader.setFloat("pointLights[i].linear", 0.14);
        shader.setFloat("pointLights[i].quadratic", 0.07);
    }*/
}

//turn on the flashlight
void MyScene::flashlightOn(Shader shader){
    shader.use();
    
    shader.setVec3("spotLight.position", camera.Position);
    shader.setVec3("spotLight.direction", camera.Front);
    shader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
    shader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
    shader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
    shader.setFloat("spotLight.constant", 1.0f);
    shader.setFloat("spotLight.linear", 0.09);
    shader.setFloat("spotLight.quadratic", 0.032);
    shader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
    shader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
}

//turn off the flashlight
void MyScene::flashlightOff(Shader shader){
    shader.use();
    
    shader.setVec3("spotLight.position", camera.Position);
    shader.setVec3("spotLight.direction", camera.Front);
    shader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
    shader.setVec3("spotLight.diffuse", 0.0f, 0.0f, 0.0f);
    shader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
    shader.setFloat("spotLight.constant", 1.0f);
    shader.setFloat("spotLight.linear", 0.09);
    shader.setFloat("spotLight.quadratic", 0.032);
    shader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
    shader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
}

//load the skybox
unsigned int MyScene::loadCubemap(vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrComponents;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrComponents, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

//override
void MyScene::processInput(GLFWwindow *window)
{
    
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if(onPlane == 0){
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.ProcessKeyboard(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.ProcessKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.ProcessKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
        lightOn = 1;
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        lightOn = 0;
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS){
        onPlane = 1;
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){
        camera.Position = orgPosition;
        onPlane = 0;
    }
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
        flashLight = 1;
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
        flashLight = 0;
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
        isMove = 1;
}
