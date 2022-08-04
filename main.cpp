#include <bits/stdc++.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <iostream>
#include <math.h>

#include <windows.h>

using namespace std;

//<<<<<<< HEAD

void display(){
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-70, 70, -70, 70, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(0,1,0);
	glutSwapBuffers();

}
//=======
void drawGrid(){
	int i;
	glColor3f(1,0,0);
	glBegin(GL_LINES);
	{
		for(i=-60;i<=60;i=i+40){
			glVertex2f(-60,i);
			glVertex2f(60,i);
			
			glVertex2f(i,-60);
			glVertex2f(i,60);
		}
	}
	glEnd();
}
//>>>>>>> Ebert
int main(int argc, char** argv){
		//cout<<" PROYECTO "<<endl;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(" PROYECTO !");
	glutDisplayFunc(display);
	glutMainLoop();
	
    
    return 0;
}

