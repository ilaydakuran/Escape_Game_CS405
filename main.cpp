#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GL/glut.h"
//#include "glu.h"
#include "glm/glm.hpp"
#include "glm/gtc/constants.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/common.hpp"
#include "glm/gtc/type_ptr.hpp"
//#include "Mesh.h"
//#include "Model.h"
#include <filesystem>
#include "Window.hpp"
#include "includes/GameObj3D.hpp"
#include "ShaderProgram.hpp"
#include "Camera.hpp"
#include "includes/parametric-3d/Parametric3DShape.hpp"
#include "CubeData.hpp"
#include "includes/Textures.hpp"
#include "collusion-helpers.hpp"
#include "Scene.hpp"
//#include "includes/particle_generator.cpp"
#include <iostream>
#include <vector>
using namespace std;

// Globals
int u_transform, u_pv, u_frame, u_light_pos, u_light_color;
int moveFront = 0, moveRight = 0, moveDash = 0;
float mouseX = 0, mouseY = 0;
float velocityY = 0;
int balls = 0;
int xpos = 0, ypos = 0;

void keyCallback(GLFWwindow *_, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_W && action == GLFW_PRESS)
    {
        moveFront = 1;
    }
    else if (key == GLFW_KEY_W && action == GLFW_RELEASE)
    {
        moveFront = 0;
    }
    if (key == GLFW_KEY_S && action == GLFW_PRESS)
    {
        moveFront = -1;
    }
    else if (key == GLFW_KEY_S && action == GLFW_RELEASE)
    {
        moveFront = 0;
    }
    if (key == GLFW_KEY_D && action == GLFW_PRESS)
    {
        moveRight = 1;
    }
    else if (key == GLFW_KEY_D && action == GLFW_RELEASE)
    {
        moveRight = 0;
    }
    if (key == GLFW_KEY_A && action == GLFW_PRESS)
    {
        moveRight = -1;
    }
    else if (key == GLFW_KEY_A && action == GLFW_RELEASE)
    {
        moveRight = 0;
    }
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    {
        for(int x = 1 ; x <5; x++){
            velocityY = x;
            
        }
    }
    if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS)
    {
        moveFront = 4;
    }
    else if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE)
    {
        moveFront = 0;
    }
}

static void cursorPositionCallback(GLFWwindow *_, double x, double y)
{
    mouseX = 2.0 * ((float)x / Window::width) - 1;
    mouseY = 2.0 * (1 - ((float)y / Window::height)) - 1;
}

int main()
{
    // init window
    Window::init(800, 800, "my window");

    glfwSetKeyCallback(Window::window, keyCallback);
    glfwSetCursorPosCallback(Window::window, cursorPositionCallback);
    float vertices[] =
       {
           300, 300, 0.0, // top right corner
           0, 300, 0.0, // top left corner
           0, 0, 0.0, // bottom left corner
           300, 0, 0.0 // bottom right corner
       };
       
       glViewport( 0.0f, 0.0f, 800, 800 ); // specifies the part of the window to which OpenGL will draw (in pixels), convert from normalised to pixels
       glMatrixMode( GL_PROJECTION ); // projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
       glLoadIdentity( ); // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
       glOrtho( 0, 800, 0, 800, 0, 1 ); // essentially set coordinate system
       glMatrixMode( GL_MODELVIEW ); // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world
       glLoadIdentity( ); // same as above comment
    // init objects
    Model3D sphereModel = Parametric3DShape::generate(ParametricLine::halfCircle, 50, 50);
    Model3D sphereModel2 = Parametric3DShape::generate(ParametricLine::halfCircle, 5, 5);
    
  
    Model3D cone = Parametric3DShape::generate(ParametricLine::spikes, 50, 50);
    Model3D cubeModel(CubeData::positions, CubeData::normals, CubeData::uvs, CubeData::indices);
    
  
   // Mesh hero2(getdate("objects/shark-boi/source/shark.obj"));
   // hero2.textures_loaded;
    //  Model ourModel("objects/backpack/backpack.obj");


    
    //benim hareket ettiğim şey
    GameObj3D hero(sphereModel);
    hero.translate(15, 1.0, -15.0);
    hero.scale(0.3, 0.3, 0.3);
    hero.textureId = 1;
    //hero.hasGravity = false; // çevreyi kontrol etmek için kullanılır
    scene.push_back(&hero);

    GameObj3D* firstwall = new GameObj3D(cubeModel);
    scene.push_back(firstwall);

    firstwall -> translate(2.6,30 ,0.8);
    firstwall -> scale(50,0.1,18); //düzlemin büyüklüğü değişiyor
    firstwall-> rotate(90, 0, 0);
    firstwall -> textureId = 2;
    firstwall -> isCollid = false;
    firstwall -> hasGravity = false;
    
    GameObj3D* secondhalfwall = new GameObj3D(cubeModel);
    scene.push_back(secondhalfwall);

    secondhalfwall -> translate(2.6,1 ,0.8);
    secondhalfwall -> scale(30,0.1,10); //düzlemin büyüklüğü değişiyor
    secondhalfwall-> rotate(90, 0, 0);
    secondhalfwall -> textureId = 2;
    secondhalfwall -> isCollid = false;
    secondhalfwall -> hasGravity = false;
    
    GameObj3D* mine0 = new GameObj3D(cubeModel);
    mine0 -> translate(0, 2, -2);
    mine0 -> scale(5,0.5,2); //düzlemin büyüklüğü değişiyor
    mine0 -> hasGravity = false;
    mine0 -> isCollid = false;
    scene.push_back(mine0);
    
    GameObj3D* mine = new GameObj3D(cubeModel);
    mine -> translate(0, 2, -2);
    mine -> scale(5,0.5,2); //düzlemin büyüklüğü değişiyor
    mine -> hasGravity = false;
    mine -> isCollid = false;
    scene.push_back(mine);
    
    
    GameObj3D* mine2 = new GameObj3D(cubeModel);
    mine2 -> translate(10, 3, -2);
    mine2 -> scale(5,0.5,2); //düzlemin büyüklüğü değişiyor
    mine2 -> hasGravity = false;
    mine2 -> isCollid = false;
    scene.push_back(mine2);
    
    GameObj3D* mine3 = new GameObj3D(cubeModel);
    mine3 -> translate(20, 4, -2);
    mine3 -> scale(5,0.5,2); //düzlemin büyüklüğü değişiyor
    mine3 -> hasGravity = false;
    mine3 -> isCollid = false;
    scene.push_back(mine3);
    
    GameObj3D* mine4 = new GameObj3D(cubeModel);
    mine4 -> translate(30, 5, -2);
    mine4 -> scale(5,0.5,2); //düzlemin büyüklüğü değişiyor
    mine4 -> hasGravity = false;
    mine4 -> isCollid = false;
    scene.push_back(mine4);
    
    GameObj3D* mine5 = new GameObj3D(cubeModel);
    mine5 -> translate(40, 6, -2);
    mine5 -> scale(5,0.5,2); //düzlemin büyüklüğü değişiyor
    mine5 -> hasGravity = false;
    mine5 -> isCollid = false;
    scene.push_back(mine5);
    
    GameObj3D* mine6 = new GameObj3D(cubeModel);
    mine6 -> translate(50, 7, -2);
    mine6 -> scale(5,0.5,2); //düzlemin büyüklüğü değişiyor
    mine6 -> hasGravity = false;
    mine6 -> textureId = 5;
    mine6 -> isCollid = false;
    scene.push_back(mine6);
    /*
    GameObj3D* particle1 = new GameObj3D(sphereModel);
    particle1 -> translate(50, 9, -2);
    particle1 -> scale(0.1,0.1,0.1); //düzlemin büyüklüğü değişiyor
    particle1 -> textureId = 1;
    particle1 -> hasGravity = false;
    scene.push_back(particle1);
     */
    ///particles
    int numpart = 250;
    for ( unsigned int i = 0; i < numpart  ; i ++){
        GameObj3D* particle1 = new GameObj3D(sphereModel2);
        float b = (rand() % 400) / float(100) + float(7);
        float c = (rand() % 300) / float(100);
        float e = (rand() % 600) / float(100) + float(49);
        c = -1 * c;
        particle1 -> translate(e, b , c );
        particle1 -> scale(0.035 ,0.035,0.035);
        particle1 -> textureId = 3;
        particle1 -> isCollid = false;
        particle1 -> hasGravity = false;
        scene.push_back(particle1);
    }
    for ( unsigned int i = 0; i < numpart /2 ; i ++){
        GameObj3D* particle2 = new GameObj3D(sphereModel2);
        float b = (rand() % 400) / float(100) + float(7.9);
        float c = (rand() % 300) / float(100);
        float e = (rand() % 600) / float(100) + float(49);
        c = -1 * c;
        particle2 -> translate(e, b , c );
        particle2 -> scale(0.035 ,0.035,0.035);
        particle2 -> textureId = 3;
        particle2 -> isCollid = false;
        particle2 -> hasGravity = false;
        scene.push_back(particle2);
    }
    for ( unsigned int i = 0; i < numpart / 2 ; i ++){
        GameObj3D* particle3 = new GameObj3D(sphereModel2);
        float b = (rand() % 200) / float(100) + float(7);
        float c = (rand() % 150) / float(100);
        float e = (rand() % 300) / float(100) + float(51);
        c = -1 * c - 1;
        particle3 -> translate(e, b , c );
        particle3 -> scale(0.035 ,0.035,0.035);
        particle3 -> textureId = 4;
        particle3 -> isCollid = false;
        particle3 -> hasGravity = false;
        scene.push_back(particle3);
    }
    GameObj3D* floor = new GameObj3D(cubeModel);
    scene.push_back(floor);

    floor -> translate(0, -1, 0);
    floor -> scale(50,0.5,50); //düzlemin büyüklüğü değişiyor
    floor -> textureId = 2;
    floor -> hasGravity = false; //böyle olunca asılı
    /*
    //walls
    GameObj3D* floor3 = new GameObj3D(cubeModel);
    scene.push_back(floor3);

    floor3 -> translate(1,0 , 0);
    floor3 -> scale(50,0.5,18); //düzlemin büyüklüğü değişiyor
    floor3-> rotate(90, 270, 0);
    floor3 -> textureId = 2;
    floor3 -> isCollid = false;
    floor3 -> hasGravity = false;
    
    GameObj3D* floor32 = new GameObj3D(cubeModel);
    scene.push_back(floor32);

    floor32 -> translate(1,30 , 30);
    floor32 -> scale(50,0.4,9); //düzlemin büyüklüğü değişiyor
    floor32-> rotate(90, 270, 0);
    floor32 -> textureId = 2;
    floor32 -> isCollid = false;
    floor32 -> hasGravity = false;
    
    GameObj3D* floor4 = new GameObj3D(cubeModel);
    scene.push_back(floor4);

    floor4 -> translate(50,0, 0);
    floor4 -> scale(50,0.5,50); //düzlemin büyüklüğü değişiyor
    floor4-> rotate(90, 270, 0);
    floor4 -> textureId = 2;
    floor4 -> isCollid = false;
    floor4 -> hasGravity = false;
     */
    /*
    GameObj3D* floor21 = new GameObj3D(cubeModel);
    scene.push_back(floor21);
    floor21 -> translate(1.5,0.5 , 0.5);
    floor21 -> scale(20,0.5,50); //düzlemin büyüklüğü değişiyor
    floor21-> rotate(90, 0, 0);
    floor21 -> textureId = 2;
    floor21 -> isCollid = false;
    floor21 -> hasGravity = false;
     */
   /*
    GameObj3D* floor22 = new GameObj3D(cubeModel);
    scene.push_back(floor22);

    floor22 -> translate(,0 , 0);
    floor22 -> scale(50,0.4,8); //düzlemin büyüklüğü değişiyor
    floor22-> rotate(90, 0, 0);
    floor22 -> textureId = 2;
    floor22 -> isCollid = false;
    floor22 -> hasGravity = false;
    
    GameObj3D* floor23 = new GameObj3D(cubeModel);
    scene.push_back(floor23);

    floor23 -> translate(10,0, 50);
    floor23 -> scale(100,0.2,50); //düzlemin büyüklüğü değişiyor
    floor23-> rotate(90, 0, 0);
    floor23 -> textureId = 2;
    floor23 -> isCollid = false;
    floor23 -> hasGravity = false;
   */



    GameObj3D* tavan = new GameObj3D(cubeModel);
    scene.push_back(tavan);

    tavan -> translate(0, 50, 0);
    tavan -> scale(80,0.5,80); //düzlemin büyüklüğü değişiyor
    tavan -> textureId = 2;
    tavan -> hasGravity = false; //böyle olunca asılı kalıyor
    
    GameObj3D* step = new GameObj3D(cubeModel);
    step -> translate(4, 2, 10);
    step -> scale(3,0.5,2); //düzlemin büyüklüğü değişiyor
    step -> hasGravity = false;
    scene.push_back(step);
    

    GameObj3D step2(cubeModel);
    step2.translate(4, 4, 20);
    step2.scale(3,0.5,2); //düzlemin büyüklüğü değişiyor
    step2.hasGravity = false;
    scene.push_back(&step2);
    
    GameObj3D step3(cubeModel);
    step3.translate(4, 8, 20);  /// x y height
    step3.scale(3,0.5,2); //düzlemin büyüklüğü değişiyor
    step3.hasGravity = false;
    scene.push_back(&step3);
    
    GameObj3D* step4 = new GameObj3D(cubeModel);
    step4 -> translate(4, 6, 10);
    step4 -> scale(3,0.5,2); //düzlemin büyüklüğü değişiyor
    step4 -> hasGravity = false;
    scene.push_back(step4);
    
    GameObj3D* step5 = new GameObj3D(cubeModel);
    step5 -> translate(4, 10, 10);
    step5 -> scale(3,0.5,2); //düzlemin büyüklüğü değişiyor
    step5 -> hasGravity = false;
    scene.push_back(step5);
    
    GameObj3D step6(cubeModel);
    step6.translate(4, 12, 20);  /// x y height
    step6.scale(3,0.5,2); //düzlemin büyüklüğü değişiyor
    step6.hasGravity = false;
    scene.push_back(&step6);
    
    GameObj3D* step7 = new GameObj3D(cubeModel);
    step7 -> translate(4, 14, 10);
    step7 -> scale(3,0.5,2); //düzlemin büyüklüğü değişiyor
    step7 -> hasGravity = false;
    scene.push_back(step7);
    
    GameObj3D step8(cubeModel);
    step8.translate(4, 16, 20);  /// x y height
    step8.scale(3,0.5,2); //düzlemin büyüklüğü değişiyor
    step8.hasGravity = false;
    scene.push_back(&step8);
    
    //***************
    
    GameObj3D* basamak = new GameObj3D(cubeModel);
    basamak -> translate(-20, 3, -30);
    basamak -> scale(2,0.5,4); //düzlemin büyüklüğü değişiyor
    basamak -> hasGravity = false;
    scene.push_back(basamak);
    

    GameObj3D basamak2(cubeModel);
    basamak2.translate(-20, 4, -35);
    basamak2.scale(2,0.5,4); //düzlemin büyüklüğü değişiyor
    basamak2.hasGravity = false;
    scene.push_back(&basamak2);
    
    GameObj3D basamak3(cubeModel);
    basamak3.translate(-20, 5, -40);  /// x y height
    basamak3.scale(2,0.5,4); //düzlemin büyüklüğü değişiyor
    basamak3.hasGravity = false;
    scene.push_back(&basamak3);
    
    GameObj3D basamak4(cubeModel);
    basamak4.translate(-20, 6, -45);  /// x y height
    basamak4.scale(2,0.5,4); //düzlemin büyüklüğü değişiyor
    basamak4.hasGravity = false;
    scene.push_back(&basamak4);
    
    GameObj3D basamak5(cubeModel);
    basamak5.translate(4, 7, 45);  /// x y height
    basamak5.scale(2,0.5,4); //düzlemin büyüklüğü değişiyor
    basamak5.rotate(0, 90, 0);
    basamak5.hasGravity = false;
    scene.push_back(&basamak5);
    
    GameObj3D basamak6(cubeModel);
    basamak6.translate(5,9, 45);  /// x y height
    basamak6.scale(2,0.5,15); //düzlemin büyüklüğü değişiyor
   basamak6.rotate(0, 90, 0);
    basamak6.hasGravity = false;
    scene.push_back(&basamak6);
    
    GameObj3D basamak7(cubeModel);
    basamak7.translate(15,7, 40);  /// x y height
    basamak7.scale(3,0.5,2); //düzlemin büyüklüğü değişiyor
    basamak7.rotate(0, 90, 0);
    basamak7.hasGravity = false;
    scene.push_back(&basamak7);
    
    GameObj3D basamak8(cubeModel);
    basamak8.translate(15,6, 35);  /// x y height
    basamak8.scale(3,0.5,2); //düzlemin büyüklüğü değişiyor
    basamak8.rotate(0, 90, 0);
    basamak8.hasGravity = false;
    scene.push_back(&basamak8);
    
    GameObj3D basamak9(cubeModel);
    basamak9.translate(15,5, 30);  /// x y height
    basamak9.scale(3,0.5,2); //düzlemin büyüklüğü değişiyor
    basamak9.rotate(0, 90, 0);
    basamak9.hasGravity = false;
    scene.push_back(&basamak9);
    
    GameObj3D basamak10(cubeModel);
    basamak10.translate(15,4, 25);  /// x y height
    basamak10.scale(3,0.5,2); //düzlemin büyüklüğü değişiyor
    basamak10.rotate(0, 90, 0);
    basamak10.hasGravity = false;
    scene.push_back(&basamak10);
    
    GameObj3D basamak11(cubeModel);
    basamak11.translate(15,3, 20);  /// x y height
    basamak11.scale(3,0.5,2); //düzlemin büyüklüğü değişiyor
    basamak11.rotate(0, 90, 0);
    basamak11.hasGravity = false;
    scene.push_back(&basamak11);
    
     //*******
    GameObj3D basamak71(cubeModel);
    basamak71.translate(-5,7, 40);  /// x y height
    basamak71.scale(3,0.5,2); //düzlemin büyüklüğü değişiyor
    basamak71.rotate(0, 90, 0);
    basamak71.hasGravity = false;
    scene.push_back(&basamak71);
    
    GameObj3D basamak81(cubeModel);
    basamak81.translate(-5,6, 35);  /// x y height
    basamak81.scale(3,0.5,2); //düzlemin büyüklüğü değişiyor
    basamak81.rotate(0, 90, 0);
    basamak81.hasGravity = false;
    scene.push_back(&basamak81);
    
    GameObj3D basamak91(cubeModel);
    basamak91.translate(-5,5, 30);  /// x y height
    basamak91.scale(3,0.5,2); //düzlemin büyüklüğü değişiyor
    basamak91.rotate(0, 90, 0);
    basamak91.hasGravity = false;
    scene.push_back(&basamak91);
    
    GameObj3D basamak101(cubeModel);
    basamak101.translate(-5,4, 25);  /// x y height
    basamak101.scale(3,0.5,2); //düzlemin büyüklüğü değişiyor
    basamak101.rotate(0, 90, 0);
    basamak101.hasGravity = false;
    scene.push_back(&basamak101);
    
    GameObj3D basamak111(cubeModel);
    basamak111.translate(-5,3, 20);  /// x y height
    basamak111.scale(3,0.5,2); //düzlemin büyüklüğü değişiyor
    basamak111.rotate(0, 90, 0);
    basamak111.hasGravity = false;
    scene.push_back(&basamak111);
    
    GameObj3D basamak112(cubeModel); //belki çıkartmak gerekir
    basamak112.translate(-5,2, 20);  /// x y height
    basamak112.scale(3,0.5,2); //düzlemin büyüklüğü değişiyor
    basamak112.rotate(0, 90, 0);
    basamak112.hasGravity = false;
    scene.push_back(&basamak112);
    
    for ( int i =0; i < 10; i++){
        int x = rand() % 50;
        int y = rand() % 50;
        int x1 = rand() % 50;
        int y1 = rand() % 50;

        
        GameObj3D* toy =  new GameObj3D(sphereModel2);
        toy -> translate(x , 0 , y);
        toy -> scale(0.5, 0.5, 0.5);
        toy -> textureId = 6;
        toy -> hasGravity = false;
        scene.push_back(toy);
        
        GameObj3D* toy2 =  new GameObj3D(sphereModel);
        toy2 -> translate(x , 0 , y);
        toy2 -> scale(0.5, 0.5, 0.5);
        toy2 -> textureId = 6;
        toy2 -> hasGravity = false;
        
        
        GameObj3D* toycube = new GameObj3D(cubeModel);
        toycube -> translate(x1, 0 , y1);
        toycube -> scale(0.5,0.5,0.5); //düzlemin büyüklüğü değişiyor
        toycube -> hasGravity = false;
        toycube -> textureId = 8;
        scene.push_back(toycube);
    }
    // light
    glm::vec3 lightPos = glm::vec3(0.0, 0.0, 1.0);
    glm::vec3 lightColor= glm::vec3(1.0, 1.0, 1.0);
    
    glm::vec3 lightPos2 = glm::vec3(52.5, 9.0, -2.0);
    glm::vec3 lightColor2 = glm::vec3(1.0, 1.0, 1.0);
// Model ourModele"objects/shark-boi/source/shark.obj");
   
    const vector<string> texture_files{"/Users/ilaydakuran/Desktop/project3d02/project3d02/textures/gold.jpg", "/Users/ilaydakuran/Desktop/project3d02/project3d02/textures/sphere.jpg","/Users/ilaydakuran/Desktop/project3d02/project3d02/textures/wood3.jpeg",
        "/Users/ilaydakuran/Desktop/project3d02/project3d02/textures/fire.jpg", "/Users/ilaydakuran/Desktop/project3d02/project3d02/textures/yellowone.jpg", "/Users/ilaydakuran/Desktop/project3d02/project3d02/textures/lava.jpg", "/Users/ilaydakuran/Desktop/project3d02/project3d02/textures/images.jpeg", "/Users/ilaydakuran/Desktop/project3d02/project3d02/textures/toy2.jpeg", "/Users/ilaydakuran/Desktop/project3d02/project3d02/textures/trexlow.jpeg", "/Users/ilaydakuran/Desktop/project3d02/project3d02/textures/trexhigh.jpeg"
    };
    // load textures
    vector<unsigned int> textures = Textures::loadTextures(texture_files);
    
    
    // create shader
    ShaderProgram sp("/Users/ilaydakuran/Desktop/project3d02/project3d02/shader/vertex.vert", "/Users/ilaydakuran/Desktop/project3d02/project3d02/shader/frag.frag");
    u_transform = glGetUniformLocation(sp.id, "u_transform");
    u_pv = glGetUniformLocation(sp.id, "u_pv");
    u_frame = glGetUniformLocation(sp.id, "u_frame");
    u_light_pos = glGetUniformLocation(sp.id, "u_light_pos");
    u_light_color = glGetUniformLocation(sp.id, "u_light_color");
    auto u_texture = glGetUniformLocation(sp.id, "u_texture");
    glUniform1i(u_texture, 0);    // 0th unit
    glActiveTexture(GL_TEXTURE0); // active 0th unit

    sp.use();

    //unsigned a = 0;
    // game loop
    while (!Window::isClosed())
    {
        // update player and camera
        hero.moveFront(moveFront * 0.1);
        hero.rotate(hero.rotation().x, hero.rotation().y - moveRight *2.0f, hero.rotation().z);
        
        if(velocityY > 0) {
            hero.moveUp(velocityY);
            if(CollidesWithSth(hero)) {
                hero.moveUp(-velocityY);
            }
        }
        Camera::position = hero.position() - hero.front() * 4.0f + hero.up() * 2.0f;
        Camera::front = hero.front() + glm::vec3(0, mouseY, 0);
        Camera::up = glm::cross(Camera::front, hero.right());
        Camera::front = glm::rotateY(Camera::front, -mouseX);

        // update uniforms
        glUniformMatrix4fv(u_pv, 1, GL_FALSE, glm::value_ptr(Camera::getProjMatrix() * Camera::getViewMatrix()));
        glUniform1i(u_frame, 1);
        glUniform3fv(u_light_pos, 1, glm::value_ptr(lightPos));
        glUniform3fv(u_light_color, 1, glm::value_ptr(lightColor));
        
        // water earth fire air gecmiste 4 ulus baris ve uyum icinde yasardi
        glUniform3fv(u_light_pos, 1, glm::value_ptr(lightPos2));
        glUniform3fv(u_light_color, 1, glm::value_ptr(lightColor2));
                
            
        
        
        
        // scene draw
        for (std::vector<GameObj3D*>::iterator t = scene.begin(); t != scene.end(); ++t) {

            // get the object
            const int i = t - scene.begin();

            // gravity logic
            GameObj3D* object = scene[i];
            if ( (object -> textureId == 1) && (object -> hasGravity) ) {
                object -> moveUp(-0.2);
                if(CollidesWithSth(*object)) {
                    object -> moveUp(0.2);
                }
            }
            if(object -> textureId == 3 || object -> textureId == 4){
                object -> moveUp(0.005);
                if(object -> position().y > 8 && object->textureId == 4){
                    float b = (rand() % 200) / float(100) + float(7);
                    float c = (rand() % 150) / float(100);
                    float e = (rand() % 300) / float(100) + float(49);
                    c = c * -1 -1 ;
                    object -> translate(e, b, c);
                }
                if(object ->position().y > 10 ){
                    float b = (rand() % 400) / float(100) + float(7);
                    float c = (rand() % 300) / float(100);
                    float e = (rand() % 600) / float(100) + float(49);
                    c = c * -1;
                    object -> translate(e, b, c);
                }
                if(object -> position().y > 5 && (object -> position().z < -1 || object->position().z < -2) && (object ->position().x > 53  || object ->position().x < 51)){
                    float b = (rand() % 400) / float(100) + float(7);
                    float c = (rand() % 300) / float(100);
                    float e = (rand() % 600) / float(100) + float(49);
                    c = c * -1;
                    object -> translate(e, b, c);
                }
            }
            //level of detail
            if(object->textureId == 1){
                xpos = object -> position().x;
                ypos = object -> position().y;
            }
            if(object-> textureId == 6 && ((xpos - (object -> position().x) <= 5) &&  ypos - (object -> position().y) <= 5)){
                GameObj3D* toy2 =  new GameObj3D(sphereModel);
                toy2 -> translate(object -> position().x , 0 , object-> position().y);
                toy2 -> scale(0.5, 0.5, 0.5);
                toy2 -> textureId = 6;
                toy2 -> hasGravity = false;
                object = toy2;
                
            }
            if(object-> textureId == 8 && ((xpos - (object -> position().x) <= 5) &&  ypos - (object -> position().y) <= 5)){
                object-> textureId = 9;
            }
            else if(object-> textureId == 9 && ((xpos - (object -> position().x) >= 5) &&  ypos - (object -> position().y) >= 5)){
                object-> textureId = 8;
            }
            // for jump logic
            velocityY -= 0.2;

            // draw the object
            glUniformMatrix4fv(u_transform, 1, GL_FALSE, glm::value_ptr(object -> getTransform()));
            glBindTexture(GL_TEXTURE_2D, textures[object -> textureId]);
            object -> draw();
            
            glEnableClientState( GL_VERTEX_ARRAY ); // tell OpenGL that you're using a vertex array for fixed-function attribute
            glVertexPointer( 3, GL_FLOAT, 0, vertices ); // point to the vertices to be used
            glDrawArrays( GL_QUADS, 0, 4 ); // draw the vertixes
            glDisableClientState( GL_VERTEX_ARRAY ); // tell OpenGL that you're finished using the vertex arrayattribute
        
            // Poll for and process events
            glfwPollEvents( );
            
        }

        // update the scene
        Window::refresh();
    }

    Window::terminate();

    return 0;
}
