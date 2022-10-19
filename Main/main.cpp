
#include "MyScene.h"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    MyScene *myScene = NULL;
    myScene = new MyScene("CG_project", SCR_WIDTH, SCR_HEIGHT);
    myScene -> Run();
}
