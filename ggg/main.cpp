#include <windows.h>
#include <GL/glut.h>


#include <stdlib.h>

static int slices = 80;
static int stacks = 80;
static int rain = 50;
static float A[]={1.5 , 1.8 , 1.75};
static float M=0.7;

/* GLUT callback Handlers */

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

static void display(void)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;
    const int s=40-t*10;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


/// sun light ^_^
for (float j=0.1;j<0.92;j=j+0.04)
{
    glPushMatrix();
        glColor3d(.9,.8,0.1);
        glTranslated(-1.7-j*.5,2.4-j,-4);
        glRotated(60+90*j,0.2,0.5,-0.1);
        glutWireCone(.02,A[0],slices,stacks);
    glPopMatrix();
}
for (float j=1.2;j<2;j=j+0.03)
{
    glPushMatrix();
        glColor3d(.9,0.9,0.4);
        glTranslated(-1.8-j*.5,3.1-j,-4);
        glRotated(100*j,0.2,0.5,-.2);
        glutWireCone(.02,A[1],slices,stacks);
    glPopMatrix();

}
for (float j=0.1;j<1.5;j=j+0.05)

{
    glPushMatrix();
        glColor3d(.6,.5,0);
        glTranslated(-2.65-j*.8,1.4+j*.5,-4);
        glRotated(60,1,0,0);

        glRotated(22,-0.2,0.5,0.1);
        glutWireCone(.01,A[2],slices,stacks);
    glPopMatrix();
}

/// sun :P

glPushMatrix();
        glColor3d(0.8,0.75,0.15);
        glTranslated(-2.4,1.9,-4);
        glRotated(60,0,0,0);
        glutSolidSphere(1.9,slices,stacks);
    glPopMatrix();

for(float i=0.35 ;i<0.75; i=i+0.001)
{
    glPushMatrix();
        glColor3d(1,i,0.2);
        glTranslated(-2.4,1.8+i*.1,-4);
        glRotated(60,1,1,1);
        glutWireSphere(1,slices,stacks);
    glPopMatrix();
}


/// the sea :D
for (float i=4.0;i>0;i-=0.5)
    for (int k=-7 ;k<7;k+=1)
{


    glPushMatrix();
    if((k%2==0&&i==0.5)||(k%2!=0&&i==1))
        glColor3d(0.2,0.7,0.9);
    else if ((k%2!=0&&i==0.5)||(k%2==0&&i==1))
        glColor3d(0.2,0.7,0.8);
    else if((k%2==0&&i==1.5)||(k%2!=0&&i==2))
        glColor3d(0.2,0.6,0.9);
    else if((k%2==0&&i==2)||(k%2!=0&&i==1.5))
        glColor3d(0.2,0.6,0.8);
    else if((k%2==0&&i==2.5)||(k%2!=0&&i==3))
        glColor3d(0.2,0.4,0.9);
    else if((k%2==0&&i==3)||(k%2!=0&&i==2.5))
        glColor3d(0.2,0.4,0.8);
    else if((k%2==0&&i==3.5)||(k%2!=0&&i==4))
        glColor3d(0.1,0.3,1);
    else if((k%2==0&&i==4)||(k%2!=0&&i==3.5))
        glColor3d(0.1,0.3,0.9);

        glTranslated(k,1-i,-6);
        glRotated(60,0,0,0);
        glRotated(a,0,0,1);
        glutSolidCube(2.1);
    glPopMatrix();


}

for (int g=1 ; g<=rain ; g++)
for (int f=0 ; f<10; f++)
{

 glPushMatrix();
        glColor3d(.7,1,1);
        glTranslated(50-f*15,s+g*8,-100);
        glRotated(a,1,1,1);
        glutSolidDodecahedron();
    glPopMatrix();
}




    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;

        case '+':
            rain=100;
            if (A[0]>1.04)
                {
                A[0]-=0.15;
                A[1]-=0.15;
                A[2]-=0.10;

                }
            break;

        case '-':

            if (A[0]<1.9)
                {
                    rain -=15;
                A[0]+=0.15;
                A[1]+=0.15;
                A[2]+=0.10;

                }
            break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(170,100);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(0.8,0.85,0.9,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glutMainLoop();

    return EXIT_SUCCESS;
}
