#include <bits/stdc++.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <iostream>
#include <math.h>

#include <windows.h>

using namespace std;

void draw_stuff(int index, double tx, double ty){
	char string[8][256];
	
	unsigned int count;
	void* stroke_fonts[2]={
		GLUT_STROKE_ROMAN,
		GLUT_STROKE_ROMAN
	};
	for(int i=0;i<8;i++){
		count=0;
		string[i][count]=49+i;
		string[i][++count]='\0';
	}
	glColor3f(0.0,0.0,0.0);
	int stroke_scale=10;
	glPushMatrix();
	{
		glTranslatef(tx,ty,0);
		glScalef(0.2,0.2,0.2);
		print_stroke_string(GLUT_STROKE_ROMAN,string[index]);
	}
	glPopMatrix();
}

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

void display(){
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-70, 70, -70, 70, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(0,1,0);
    drawGrid();
	glutSwapBuffers();
    

}

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

