
#include <iostream>

using namespace std;

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

int main(int argc, char** argv){
	
	
    
    return 0;
}

