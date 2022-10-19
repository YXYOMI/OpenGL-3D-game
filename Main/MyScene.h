//
//  MyScene.h
//  CG_project
//
//  Created by OYXY on 2020/12/13.
//  Copyright © 2020 OYXY. All rights reserved.
//

#ifndef MyScene_h
#define MyScene_h
#include "../Framework/Engine/Scene.h"
#include "../Framework/Utility/Shader.h"
#include <vector>


/**
 class MyScene inherits from class Scene and is used to draw the whole scene by function run().
 */
class MyScene: public Scene
{
public:
    MyScene(const char *title, const int& windowWidth, const int& windowHeight);
    ~MyScene(){};
    
    void Run();

    void lightsOn(Shader shader, glm::vec3* pointLightPositions);
    void lightsOff(Shader shader, glm::vec3* pointLightPositions);
    void flashlightOn(Shader shader);
    void flashlightOff(Shader shader);
    unsigned int loadCubemap(std::vector<std::string> faces); //load the skybox
    
    //override
    void processInput(GLFWwindow *window);
    
    //load the shaders that should be used to loading model and load the skybox
    Shader modelShader = Shader("../Resources/Shaders/model_loading.vs", "../Resources/Shaders/model_loading.fs");
    Shader skyboxShader = Shader("../Resources/Shaders/skybox.vs", "../Resources/Shaders/skybox.fs");
    
    std::vector<std::string> skyboxFaces_day //day skybox resources
    {
        "../Resources/skybox/Day/px.png", //right
        "../Resources/skybox/Day/nx.png", //left
        "../Resources/skybox/Day/py.png", //up
        "../Resources/skybox/Day/ny.png", //down
        "../Resources/skybox/Day/pz.png", //front
        "../Resources/skybox/Day/nz.png", //back
    };
    
    std::vector<std::string> skyboxFaces_night //night skybox resources
    {
        "../Resources/skybox/night/Sky_Night Moon Low CrepuscularStyle_Cam_2_Left+X.png",
        "../Resources/skybox/night/Sky_Night Moon Low CrepuscularStyle_Cam_3_Right-X.png",
        "../Resources/skybox/night/Sky_Night Moon Low CrepuscularStyle_Cam_4_Up+Y.png",
        "../Resources/skybox/night/Sky_Night Moon Low CrepuscularStyle_Cam_5_Down-Y.png",
        "../Resources/skybox/night/Sky_Night Moon Low CrepuscularStyle_Cam_0_Front+Z.png",
        "../Resources/skybox/night/Sky_Night Moon Low CrepuscularStyle_Cam_1_Back-Z.png",
    };
    
    static glm::vec3 pointLightPositions[];
    static float skyboxVertices[];
    static int lightOn;     //check whether the light should turn on
    static int onPlane;     //check whether the user is on the airplane
    static int flashLight;  //check whether the flashlight should turn on
    static int isMove;      //check whether the animation should begin
    static int isNight;     //check whether it is at night
    
    static glm::vec3 planePosition; //get the airplane position
    static glm::vec3 orgPosition;   //store the position before get on the airplane
};

#endif /* MyScene_h */
