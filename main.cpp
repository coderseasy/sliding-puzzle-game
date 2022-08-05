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
    {0,0,0},{0.5,0.1,0.9},{0.8,1,0.9},
    {0.9,0.6,0.2},{1,1,0},{1,0.4,0.8},
    {1,1,1},{0.7,0.5,1},{0.7,0.9,0.5}
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
void drawSquare(double x, double y, double color_rgb[]){
	glColor3f(color_rgb[0],color_rgb[1],color_rgb[2]);
	
	glBegin(GL_QUADS);
	{
		glVertex2f(x+1,y+1);
		glVertex2f(x+39,y+1);
		glVertex2f(x+39,y+39);
		glVertex2f(x+1,y+39);
	}
	glEnd();
	
}
bool check(){
	int cnt=0;
	
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(grid[i][j]!=order[cnt]){
				return false;
			}
			cnt++;
		}
	}
	return true;
}

void display(){

    if(check()){
		cout<<"Felicidades, lo ha Resuelto con exito !!\n";
		cout<<"Numero total de movimientos  "<<totStep<<endl;
		exit(0);
	}
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
				inc=inc+0.05;
			}
			
		}
	}
	flg=0;

	glutSwapBuffers();
    

}

double h=40;
void animate(){
    glutPostRedisplay();
	if(flg==0 && action != -1){
		if(action==1){
			int limit=bloks[index].y+counter;
			if(limit<=60 && counter>0){
				int x,y;
				findZero(&x,&y);
				stopIndex=grid[x][y];
				bloks[index].y=bloks[index].y+h;
				counter=counter-h;
			}
			if(counter<0){
				action=-1;
				stopIndex=-1;
				int x,y;
				findZero(&x,&y);
				int t=grid[x][y];
				bloks[t].y=bloks[t].y-40;
			}
		}
				else if(action==2){
			int limit=bloks[index].y+counter;
			if(limit>=-60 && counter<0){
				int x,y;
				findZero(&x,&y);
				stopIndex=grid[x][y];
				bloks[index].y=bloks[index].y-h;
				counter=counter+h;
			}
			if(counter>0){
				action=-1;
				stopIndex=-1;
				int x,y;
				findZero(&x,&y);
				int t=grid[x][y];
				bloks[t].y=bloks[t].y+40;
			}
		}
		else if(action==3){
			int limit=bloks[index].x+counter;
			if(limit<=60 && counter>0){
				int x,y;
				findZero(&x,&y);
				stopIndex=grid[x][y];
				bloks[index].x=bloks[index].x+h;
				counter=counter-h;
			}
			if(counter<0){
				action=-1;
				stopIndex=-1;
				int x,y;
				findZero(&x,&y);
				int t=grid[x][y];
				bloks[t].x=bloks[t].x-40;
			}
		}
		else if(action==4){
			int limit=bloks[index].x+counter;
			if(limit>=-60 && counter<0){
				int x,y;
				findZero(&x,&y);
				stopIndex=grid[x][y];
				bloks[index].x=bloks[index].x-h;
				counter=counter+h;
			}
			if(counter>0){
				action=-1;
				stopIndex=-1;
				int x,y;
				findZero(&x,&y);
				int t=grid[x][y];
				bloks[t].x=bloks[t].x+40;
			}
		}

    }

    action=-1;
}
void specialKeyListener(int key,int x, int y){

	
	if(key==GLUT_KEY_UP && action==-1){//abajo
		int x,y;
		findZero(&x,&y);

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
	
		if(x>0){
		
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
	
		if(y>0){
			
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
	
	animate();
	
}

int main(int argc, char** argv){
	

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(" PROYECTO !");
	glutDisplayFunc(display);
	glutSpecialFunc(specialKeyListener);
	glutMainLoop();
	
    
    return 0;
}

