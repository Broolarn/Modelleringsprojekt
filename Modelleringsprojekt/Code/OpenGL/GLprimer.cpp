// File and console I/O for logging and error reporting
#include <iostream>
#include <math.h>
// In MacOS X, tell GLFW to include the modern OpenGL headers.
// Windows does not want this, so we make this Mac-only.
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#endif

// GLFW 3.x, to handle the OpenGL window
#include <GLFW/glfw3.h>
#include "Utilities.hpp"
#include "Shader.hpp"
#include "TriangleSoup.hpp"
#include "Texture.hpp"
#include "Rotator.hpp"

const int m1 = 0.024;
const int b1 = 0.25;

// Multiply 4x4 matrices M1 and M2 and put the result in Mout
void mat4mult ( float M1 [] , float M2 [] , float Mout []) {
float Mtemp [16];

        Mtemp [0] = M1[0]* M2[0] + M1[4]* M2[1] + M1[8] * M2[2] + M1[12] * M2[3];
        Mtemp [1] = M1[1]* M2[0] + M1[5]* M2[1] + M1[9] * M2[2] + M1[13] * M2[3];
        Mtemp [2] = M1[2]* M2[0] + M1[6]* M2[1] + M1[10] * M2[2] + M1[14] * M2[3];
        Mtemp [3] = M1[3]* M2[0] + M1[7]* M2[1] + M1[11] * M2[2] + M1[15] * M2[3];

        Mtemp [4] = M1[0]* M2[4] + M1[4]* M2[5] + M1[8] * M2[6] + M1[12] * M2[7];
        Mtemp [5] = M1[1]* M2[4] + M1[5]* M2[5] + M1[9] * M2[6] + M1[13] * M2[7];
        Mtemp [6] = M1[2]* M2[4] + M1[6]* M2[5] + M1[10] * M2[6] + M1[14] * M2[7];
        Mtemp [7] = M1[3]* M2[4] + M1[7]* M2[5] + M1[11] * M2[6] + M1[15] * M2[7];

        Mtemp [8] = M1[0]* M2[8] + M1[4]* M2[9] + M1[8] * M2[10] + M1[12] * M2[11];
        Mtemp [9] = M1[1]* M2[8] + M1[5]* M2[9] + M1[9] * M2[10] + M1[13] * M2[11];
        Mtemp [10] = M1[2]* M2[8] + M1[6]* M2[9] + M1[10] * M2[10] + M1[14] * M2[11];
        Mtemp [11] = M1[3]* M2[8] + M1[7]* M2[9] + M1[11] * M2[10] + M1[15] * M2[11];

        Mtemp [12] = M1[0]* M2[12] + M1[4]* M2[13] + M1[8] * M2[14] + M1[12] * M2[15];
        Mtemp [13] = M1[1]* M2[12] + M1[5]* M2[13] + M1[9] * M2[14] + M1[13] * M2[15];
        Mtemp [14] = M1[2]* M2[12] + M1[6]* M2[13] + M1[10] * M2[14] + M1[14] * M2[15];
        Mtemp [15] = M1[3]* M2[12] + M1[7]* M2[13] + M1[11] * M2[14] + M1[15] * M2[15];

        for ( int i =0; i < 16; i ++) {
        Mout[i] = Mtemp[i];
        }
}
void mat4print ( float M []) {
printf ("Matrix :\n");
printf ("%6.2f %6.2f %6.2f %6.2f\n", M[0] , M[4] , M[8] , M[12]);
printf ("%6.2f %6.2f %6.2f %6.2f\n", M[1] , M[5] , M[9] , M[13]);
printf ("%6.2f %6.2f %6.2f %6.2f\n", M[2] , M[6] , M[10] , M[14]);
printf ("%6.2f %6.2f %6.2f %6.2f\n", M[3] , M[7] , M[11] , M[15]);
printf ("\n") ;
};
void mat4rotx(float M[] ,float angle){
        M [0] = 1.0f;
        M [1] = 0.0f;
        M [2] = 0.0f;
        M [3] = 0.0f;
        M [4] = 0.0f;
        M [5] = cos(angle);
        M [6] = sin(angle);
        M [7] = 0.0f;
        M [8] = 0.0f;
        M [9] = -sin(angle);
        M [10] = cos(angle);
        M [11] = 0.0f;
        M [12] = 0.0f;
        M [13] = 0.0f;
        M [14] = 0.0f;
        M [15] = 1.0f;
}
void mat4roty ( float M [] , float angle ){
        M [0] = cos(angle);
        M [1] = 0.0f;
        M [2] = -sin(angle);
        M [3] = 0.0f;
        M [4] = 0.0f;
        M [5] = 1.0f;
        M [6] = 0.0f;
        M [7] = 0.0f;
        M [8] = sin(angle);
        M [9] = 0.0f;
        M [10] = cos(angle);
        M [11] = 0.0f;
        M [12] = 0.0f;
        M [13] = 0.0f;
        M [14] = 0.0f;
        M [15] = 1.0f;
}
void mat4rotz ( float M [] , float angle ){
        M [0] = cos(angle);
        M [1] = -sin(angle);
        M [2] = 0.0f;
        M [3] = 0.0f;
        M [4] = sin(angle);
        M [5] = cos(angle);
        M [6] = 0.0f;
        M [7] = 0.0f;
        M [8] = 0.0f;
        M [9] = 0.0f;
        M [10] = 1.0f;
        M [11] = 0.0f;
        M [12] = 0.0f;
        M [13] = 0.0f;
        M [14] = 0.0f;
        M [15] = 1.0f;
}
void mat4scale ( float M [] , float scale ) {
        M [0] = scale;
        M [1] = 0.0f;
        M [2] = 0.0f;
        M [3] = 0.0f;
        M [4] = 0.0f;
        M [5] = scale;
        M [6] = 0.0f;
        M [7] = 0.0f;
        M [8] = 0.0f;
        M [9] = 0.0f;
        M [10] = scale;
        M [11] = 0.0f;
        M [12] = 0.0f;
        M [13] = 0.0f;
        M [14] = 0.0f;
        M [15] = 1.0;
}
void mat4translate ( float M [] , float x , float y , float z) {
        M [0] = 1.0f;
        M [1] = 0.0f;
        M [2] = 0.0f;
        M [3] = 0.0f;

        M [4] = 0.0f;
        M [5] = 1.0f;
        M [6] = 0.0f;
        M [7] = 0.0f;

        M [8] = 0.0f;
        M [9] = 0.0f;
        M [10] = 1.0f;
        M [11] = 0.0f;

        M [12] = x;
        M [13] = y;
        M [14] = z;
        M [15] = 1.0f;
}
void mat4perspective ( float M [] , float vfov , float aspect , float znear , float zfar ) {
// M is the matrix we want to create (an output argument )
// vfov is the vertical field of view (in the y direction )
// aspect is the aspect ratio of the viewport ( width / height )
// znear is the distance to the near clip plane ( znear > 0)
// zfar is the distance to the far clip plane ( zfar > znear )

        M [0] = (cos(vfov/2)/sin(vfov/2))/aspect;
        M [1] = 0.0f;
        M [2] = 0.0f;
        M [3] = 0.0f;
        M [4] = 0.0f;
        M [5] = (cos(vfov/2)/sin(vfov/2));
        M [6] = 0.0f;
        M [7] = 0.0f;
        M [8] = 0.0f;
        M [9] = 0.0f;
        M [10] = -(zfar+znear)/(zfar-znear);
        M [11] = -1.0f;
        M [12] = 0.0f;
        M [13] = 0.0f;
        M [14] = -(2*zfar*znear)/(zfar-znear);
        M [15] = 0.0f;

}
void mat4identity(float M[]){
    M[0] = 1.0f;
    M[1] = 0.0f;
    M[2] = 0.0f;
    M[3] = 0.0f;
    M[4] = 0.0f;
    M[5] = 1.0f;
    M[6] = 0.0f;
    M[7] = 0.0f;
    M[8] = 0.0f;
    M[9] = 0.0f;
    M[10] = 1.0f;
    M[11] = 0.0f;
    M[12] = 0.0f;
    M[13] = 0.0f;
    M[14] = 0.0f;
    M[15] = 1.0f;
}

/*
 * main(argc, argv) - the standard C++ entry point for the program
 */

int main(int argc, char *argv[]) {

    using namespace std;

    GLfloat R [16];
    GLfloat R1 [16];
    GLfloat R2 [16];
    GLfloat R3 [16];
    GLfloat T [16];
    GLfloat T1[16];
    GLfloat T2[16];
    GLfloat T3[16];
    GLfloat RX [16];
    GLfloat RZ [16];
    GLfloat BigR[16];
    GLfloat transformation[16];
    GLfloat transformation2 [16];
    GLfloat transformation3 [16];
    GLfloat perspective [16];
    GLfloat mousegrej [16];
    GLfloat keygrej [16];
    GLfloat P [16];



    TriangleSoup myObj;
    TriangleSoup Bana;

    mat4identity(T1);
    mat4identity(R);

    mat4translate(T,0.0f,0.0f,-2.0f);
    mat4translate(T2, 0.0f, 0.2f, 0.0f);
    mat4translate(T3, 0.3f, 0.0f, 0.0f);
    mat4perspective(P,(M_PI/4),1.0f,1.0f,100.0f);
    mat4rotx(R1, M_PI/4);

    //slår i vid pi/15
    mat4rotz(R2, M_PI/15);


    Shader myShader;
    GLuint colorBufferID ; // Vertex colors
	int width, height;
	float time ;
    GLint location_time;

    //Texture myTexture2 ;
   // GLint location_tex2 ;
    KeyRotator myKeyRotator ;
    MouseRotator myMouseRotator ;

    const GLFWvidmode *vidmode;  // GLFW struct to hold information about the display
	GLFWwindow *window;    // GLFW struct to hold information about the window

    // Initialise GLFW
    glfwInit();

    // Determine the desktop size
    vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	// Make sure we are getting a GL context of at least version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Exclude old legacy cruft from the context. We don't need it, and we don't want it.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Open a square window (aspect 1:1) to fill half the screen height
    window = glfwCreateWindow(vidmode->height/1.2, vidmode->height/1.2, "GLprimer", NULL, NULL);
    if (!window)
    {
        cout << "Unable to open window. Terminating." << endl;
        glfwTerminate(); // No window was opened, so we can't continue in any useful way
        return -1;
    }

    // Make the newly created window the "current context" for OpenGL
    // (This step is strictly requirevoid Texture :: createTexture ( const char * filename ) {

    glfwMakeContextCurrent(window);
//finalcolor = texture(tex,st); // Use the texture to set the surface color

    // LoadGLint location_transformation3 ; extensions ( only needed in Microsoft Windows )
    Utilities :: loadExtensions () ;

    // Create the vertex buffer objects for attribute locations 0 and 1
    // ( the list of vertex coordinates and the list of vertex colors ).

    // Deactivate the vertex array object again to be nice
    glBindVertexArray(0) ;


    // Show some useful information on the GL context
    cout << "GL vendor:       " << glGetString(GL_VENDOR) << endl;
    cout << "GL renderer:     " << glGetString(GL_RENDERER) << endl;
    cout << "GL version:      " << glGetString(GL_VERSION) << endl;
    cout << "Desktop size:    " << vidmode->width << "x" << vidmode->height << " pixels" << endl;

    glfwSwapInterval(0); // Do not wait for screen refresh between frames


    //gör en shader av vertex och fragment
    myShader.createShader("vertex.glsl","fragment.glsl");

    myObj.readOBJ("meshes/Tyson.obj");
    Bana.readOBJ("meshes/Bana.obj");

    //ninjaskynke
    glEnable(GL_CULL_FACE);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);

    GLint location_P ;
    location_P = glGetUniformLocation(myShader.programID, "P");
    glUseProgram(myShader.programID); // Activate the shader to set its variables
    glUniformMatrix4fv(location_P, 1, GL_FALSE, P);
    glUseProgram(myShader.programID);

    myKeyRotator.init(window);
    myMouseRotator.init(window);

    // Variabler för rotationsvinkeln
    double radie=0.015;
    double b=0.0002;
    double m1 = 0.024;
    double hojd = 0.05;
    double airmy = 1.846;

    double Mluft=2*M_PI*airmy*radie*hojd/3;

    double lambda=(3/10)*m1*pow(radie,2) -(b/m1)-Mluft;
    double h = 1/60.0;
    int i = 0;

    double oldOmega = 271;
    double oldOmegaP = 0;
    double currAngle = 0;
    double currAngleP = 0;

    double translambda = -(0.2/m1);

    double oldV = 100;
    double oldS = 0.0;

    GLfloat I[16];
    I[0] =(1/10.0)*m1*pow(h,2) + (3/20.0)*m1*pow(radie,2);
    I[1] = 0.0f;
    I[2] = 0.0f;
    I[3] = 0.0f;
    I[4] = 0.0f;
    I[5] = (1/10.0)*m1*pow(h,2) + (3/20.0)*m1*pow(radie,2);
    I[6] = 0.0f;
    I[7] = 0.0f;
    I[8] = 0.0f;
    I[9] = 0.0f;
    I[10] = (3/10.0)*m1*pow(radie,2);
    I[11] = 0.0f;
    I[12] = 0.0f;
    I[13] = 0.0f;
    I[14] = 0.0f;
    I[15] = 1.0f;

    // Main loop
    while(!glfwWindowShouldClose(window))
    {

        Utilities :: displayFPS ( window );
        // Set the clear color and depth, and clear the buffers for drawing
        glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
        // Get window size. It may start out different from the requested
        // size, and will change if the user resizes the window.
        glfwGetWindowSize( window, &width, &height );
        // Set viewport. This is the pixel rectangle we want to draw into.
        glViewport( 0, 0, width, height ); // The entire window

        //MOTION BLUR

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glAccum(GL_RETURN, 0.95f);

        glClear(GL_ACCUM_BUFFER_BIT);

        /* ---- Rendering code should go here ---- */
        time = (float)glfwGetTime(); // Number of seconds since the program was started
        myKeyRotator.poll(window);
        // Create a rotation matrix that depends on myKeyRotator .phi and myKeyRotator . theta
        mat4rotx(RX,myKeyRotator.theta);
        mat4rotz(RZ,myKeyRotator.phi);
        //mat4mult(RX,RZ,keygrej);
        mat4mult(RZ,RX,keygrej);
        myMouseRotator.poll(window);
        // Create rotation matrix that depends on myMouseRotator . phi and myMouseRotator . theta
        mat4rotx(RX,myMouseRotator.theta);
        mat4rotz(RZ,myMouseRotator.phi);

        mat4mult(RX,RZ,mousegrej);

        glUseProgram(myShader.programID ); // Activate the shader to set its variables
        glUniform1f(location_time,time ); // Copy the value to the shader program

        GLint location_keygrej;

        location_keygrej = glGetUniformLocation(myShader.programID, "keygrej");
        glUseProgram(myShader.programID); // Activate the shader to set its variables
        glUniformMatrix4fv(location_keygrej, 1, GL_FALSE, keygrej); // Copy the value
        glUseProgram(myShader.programID);

        //Beräkningar för rotationsvinkeln

        if(i%2==0)
        {
            double newOmega = oldOmega + h*lambda*oldOmega;
            double oldAngle = currAngle;
            currAngle = oldOmega*h+oldAngle;

            mat4roty(R, currAngle);

            double tao = (3/10.0)*m1*pow(radie,2)*((newOmega-oldOmega)/h);
            double teta = asin(tao/(m1*0.02*9.82));

            mat4rotz(R2, teta);

            double omegaP = m1*9.82*0.02* 1/(I[10]*newOmega);
            double oldAngleP = currAngleP;
            currAngleP = omegaP*h+oldAngleP;


            mat4roty(R3, currAngleP);

            oldOmega = newOmega;



            /*double newS = oldS + h*oldV;
            double newV = oldV + h*translambda*oldV;

            mat4translate(T1,0.0f, 0.0f, h*oldV);

            oldS = newS;
            oldV = newV;*/

                    }

        ++i;

       /* mat4roty(BigR, time);
        mat4mult(R1, BigR, transformation3);
        mat4mult(T, transformation3, transformation3);



        location_transformation3 = glGetUniformLocation(myShader.programID, "transformation3");
        glUseProgram(myShader.programID); // Activate the shader to set its variables
        glUniformMatrix4fv(location_transformation3, 1, GL_FALSE, transformation3); // Copy the value
        glUseProgram(myShader.programID);*/

        //Bana.render();

        mat4identity(transformation3);

        mat4mult(R3, R2, transformation2);
        mat4mult(R1, transformation2, transformation2);
        mat4mult(transformation2, R, transformation2);
        mat4mult(T, transformation2, transformation2);
        //mat4mult(T2, transformation2,transformation3);
        //mat4mult(BigR, transformation3,transformation3);
        //mat4mult(T3, transformation3, transformation3);
        mat4mult(transformation2,mousegrej,transformation3);

        GLint location_transformation3;
        location_transformation3 = glGetUniformLocation(myShader.programID, "transformation3");
        glUseProgram(myShader.programID); // Activate the shader to set its variables
        glUniformMatrix4fv(location_transformation3, 1, GL_FALSE, transformation3); // Copy the value
        glUseProgram(myShader.programID);


        myObj.render();

        glUseProgram (0);

		// Swap buffers, i.e. display the image and prepare for next frame.
        glfwSwapBuffers(window);
        glAccum(GL_ACCUM, 0.9f);

		// Poll events (read keyboard and mouse input)
		glfwPollEvents();

        // Exit if the ESC key is pressed (and also if the window is closed).
        if(glfwGetKey(window, GLFW_KEY_ESCAPE)) {
          glfwSetWindowShouldClose(window, GL_TRUE);
        }

    }

    // Close the OpenGL window and terminate GLFW.
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
