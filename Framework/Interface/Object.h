//
//  Object.h
//  CG_project
//
//  Created by OYXY on 2020/12/14.
//  Copyright © 2020 OYXY. All rights reserved.
//

#ifndef Object_h
#define Object_h
#include "../Utility/Model.h"

/**
 class Object inherite class model, all the objects(Town.h, Bus.h ...) should inherite this class.
*/
class Object : public Model
{
public:
    
    Object(string const &path):Model(path){}; //load the object from the file
    ~Object(){};
    
    virtual glm::mat4 getModel() = 0; //get the model matrix of the object
};

#endif /* Object_h */
