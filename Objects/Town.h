//
//  Town.h
//  CG_project
//
//  Created by OYXY on 2020/12/14.
//  Copyright © 2020 OYXY. All rights reserved.
//

#ifndef Town_h
#define Town_h
#include "../Framework/Interface/Object.h"

string const townPath = "../Resources/town_environment/town_scene_22.obj";

/**
 class Town inherit class Object, and is used to load the town model and set the position (model matrix).
 */
class Town: public Object
{
public:
    Town();
    ~Town(){};
    
    glm::mat4 getModel();
};

Town::Town():Object(townPath){};
glm::mat4 Town::getModel()
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); //translate to make it at the center of the scene
    model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f)); //scale it down
    return model;
};

#endif /* Town_h */
