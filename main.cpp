#include <bits/stdc++.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <iostream>
#include <math.h>

#include <windows.h>

using namespace std;


int totStep=0;

typedef enum{
	MODE_BITMAP,
		MODE_STROKE
}mode_type;

static mode_type mode;
static int font_index;

void print_stroke_string(void* font, char* s){
	if(s && strlen(s)){
		
		while(*s){
			glutStrokeCharacter(font,*s);
			s++;
		}
	}
}
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
struct st{
    double x;
    double y;
    double rgb[3];
    int number;
};
int flg = 1, index = 6, action = -1, stopIndex=-1;

int grid[3][3]={
    {4,3,2},
    {7,5,8},
    {1,6,0}
};
int order[9]={1,2,3,4,5,6,7,8,0};
double color[9][3]={
    {0,0,0},{1,0,1},{1,1,0},
    {1,0,0},{0,0,1},{0,1,0},
    {1,1,1},{0,1,1},{0.5,0.3,0.5}
};
double primaryPosition[9][2]={
	{20,-60},{-60,-60},{20,20},
	{-20,20},{-60,20},{-20,-20},
	{-20,-60},{-60,-20},{20,-20}
};

double counter=40;
typedef struct st blok;
blok bloks[9];

void findZero(int *x,int *y){
    int flag=0,i=0,j=0;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            if(grid[i][j]==0){
                flag=1;
                break;
            }
        }
        if(flag==1){
            break;
        }
    }
    *x=i;
    *y=j;
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

    for(int i=1;i<10;i++){
		if(flg==1){
			bloks[i-1].number=grid[(i-1)/3][(i-1)%3];
			bloks[i-1].x=primaryPosition[i-1][0];
			bloks[i-1].y=primaryPosition[i-1][1];
			cout<<bloks[i-1].number;
		}
		for(int j=0;j<3;j++){
			bloks[i-1].rgb[j]=color[i-1][j];
		}
		if(i-1 != stopIndex){
			double inc=0.05;
			drawSquare(bloks[i-1].x,bloks[i-1].y,bloks[i-1].rgb);
			for(int k=0;k<10;k++){
				if(i==9){
					draw_stuff(7,bloks[i-1].x+10+inc,bloks[i-1].y+10);
				}
				else{
					draw_stuff(i-2,bloks[i-1].x+10+inc,bloks[i-1].y+10);
				}
				inc=inc+0.1;
			}
			
		}
	}
	flg=0;

	glutSwapBuffers();
    

}

void specialKeyListener(int key,int x, int y){

	//cout<<action<<" - "<<index<<endl;
	if(key==GLUT_KEY_UP && action==-1){//abajo
		int x,y;
		findZero(&x,&y);
		/*cout<<"pressed up key"<<endl;
		cout<<x<<y<<endl;*/
		if(x<2){
		
			int aux;
			aux=grid[x][y];
			grid[x][y]=grid[x+1][y];
			grid[x+1][y]=aux;
			
			action=1;
			counter=40;
			index=grid[x][y];
			totStep++;
		}
	}
    else if(key==GLUT_KEY_DOWN && action==-1){
		int x,y;
		findZero(&x,&y);
		/*cout<<"pressed down key"<<endl;
		cout<<x<<y<<endl;*/
		if(x>0){
			//swap(grid[x][y],grid[x-1,y]);
			int aux;
			aux=grid[x][y];
			grid[x][y]=grid[x-1][y];
			grid[x-1][y]=aux;
			
			action=2;
			counter=-40;
			index=grid[x][y];
			totStep++;
		}
	}
	else if(key==GLUT_KEY_RIGHT && action==-1){
		int x,y;
		findZero(&x,&y);
		/*cout<<"pressed right key"<<endl;
		cout<<x<<y<<endl;*/
		if(y>0){
			//swap(grid[x][y],grid[x,y-1]);
			int aux;
			aux=grid[x][y];
			grid[x][y]=grid[x][y-1];
			grid[x][y-1]=aux;
			
			action=3;
			counter=40;
			index=grid[x][y];
			totStep++;
		}
	}
	else if(key==GLUT_KEY_LEFT && action==-1){
		int x,y;
		findZero(&x,&y);
		
		if(y<2){
			
			
			int aux;
			aux=grid[x][y];
			grid[x][y]=grid[x][y+1];
			grid[x][y+1]=aux;
			
			action=4;
			counter=-40;
			index=grid[x][y];
			totStep++;
		}
	}
	

	
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

