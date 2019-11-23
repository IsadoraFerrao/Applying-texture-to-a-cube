
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>


// gcc texture.c -o texture -lGL -lGLU -lglut -lm


GLuint texture[4]; //the array for our texture

float theta;

int i;

GLuint LoadTexture( const char * filename, int width, int height )
{
    GLuint texture;
    unsigned char * data;
    FILE * file;

    file = fopen( filename, "rb" );
    if ( file == NULL ) return 0;
    data = (unsigned char *)malloc( width * height * 3 );
    fread( data, width * height * 3, 1, file );
    fclose( file );

    glGenTextures( 1, &texture ); //gera a textura
    glBindTexture( GL_TEXTURE_2D, texture ); // faz o binding da texture com o array
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE ); //parametros de ambiente da textura

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

   
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    free( data ); 
    return texture; 
}



void FreeTexture( GLuint texture )
{
  glDeleteTextures( 1, &texture );
}

static void idle(void){
  GLfloat seconds = glutGet(GLUT_ELAPSED_TIME)/1000.0;

  glutPostRedisplay();
}

void timer(int value){
theta+=1;
if (theta >= 360) theta=0.0;
    glutPostRedisplay();      
    glutTimerFunc(10, timer, 0);
}


void display(void)
{
    GLfloat rot_x=0.0, rot_y=0.0;
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(0.0, 0.0, 0.0);
    glEnable( GL_TEXTURE_2D );
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    gluLookAt (0.0, 0.0, 25.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glScalef (1.0, 1.0, 1.0);      
    glTranslated(0,0,0);
    glRotatef(theta, 0.0f, 1.0f, 0.0f);

    glBindTexture(GL_TEXTURE_2D, texture [0]);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0,0.0);
    glVertex3f(5.0, 5.0, 10.0); //tamanho da figura na tela
    glTexCoord2f(0.0, 1.0);
    glVertex3f(1.0,1.0,1.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(1.0,-1.0,-1.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(1.0,-1.0,-1.0);
    glPopMatrix();
    glEnd();
   
    glFlush();
    glutSwapBuffers();
    glDisable(GL_TEXTURE_2D);

}


void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity();

/*    
    if (w <= h)

        glOrtho(-10.0, 10.0, -10.0 * (GLfloat) h / (GLfloat) w,
            10.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-10.0 * (GLfloat) w / (GLfloat) h,
            10.0 * (GLfloat) w / (GLfloat) h, -10.0, 10.0, -10.0, 10.0);
*/

    glFrustum(-10,10,-10,10,-10,10);
    gluPerspective(45,1,-10,10);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
}

void init()
{
     
        glShadeModel(GL_SMOOTH);
        glEnable(GL_LIGHTING);

        glDepthFunc(GL_LEQUAL);
        glEnable(GL_DEPTH_TEST);

        glClearColor(0.0, 0.0, 0.0, 1.0);
        glColor3f(0.0, 0.0, 0.0);

}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Code Textura Isadora");
    
    init();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
	//glutIdleFunc(idle);
	

  
texture[3]=LoadTexture("chess.bmp",256,256);
texture[2]=LoadTexture("chess.bmp",256,256);
texture[1]=LoadTexture("chess.bmp",256,256);
texture[0]=LoadTexture("chess.bmp",256,256);
  
    glutTimerFunc(10, timer, 0);
    glutMainLoop();
    return 0;
}
