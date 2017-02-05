/*******************************
* Draws spinning triangle      *
*                              *
*******************************/

#include <GL/glut.h>
#include <GL/gl.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
using namespace std;

	float angle = 0.0;

	FILE *fin;
	FILE *fout;
	char t[11], preword1[20] = "#", preword2[20] = "vertices", preword3[20] = "faces", preword4[20] = "Vertex", preword5[20] = "Face", colour[20], partColour[10000][20], black[20] = "Black", green[20] = "Green", red[20] = "Red", blue[20] = "Blue", yellow[20] = "Yellow", white[20] = "White", grey[20] = "Grey";
	int num, Vnum, Fnum, p1[200000], p2[200000], p3[200000];
	float x[200000], y[200000], z[200000];

	//Lights settings
	GLfloat light_ambient[]= { 0.9f, 0.9f, 0.9f, 1.0f };
	GLfloat light_diffuse[]= { 0.9f, 0.9f, 0.9f, 1.0f };
	GLfloat light_specular[]= { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat light_position[]= { 0.0f, 50.0f, -200.0f, 1.0f };

	//Materials settings
	GLfloat mat_ambientBlack[]= { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat mat_ambientRed[]= { 0.2f, 0.0f, 0.0f, 1.0f };
	GLfloat mat_ambientWhite[]= { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat mat_ambientYellow[]= { 0.2f, 0.2f, 0.0f, 1.0f };
	GLfloat mat_ambientGreen[]= { 0.0f, 0.2f, 0.0f, 1.0f };
	GLfloat mat_ambientBlue[]= { 0.0f, 0.0f, 0.2f, 1.0f };
	GLfloat mat_ambientGrey[]= { 0.5f, 0.5f, 0.5f, 1.0f };

	GLfloat mat_diffuse[]= { 1.0f, 0.0f, 0.0f, 1.0f };
	GLfloat mat_specular[]= { 1.0f, 0.0f, 0.0f, 1.0f };
	GLfloat mat_shininess[]= { 1.0f };

	// Absolute rotation values (0-359 degrees) and rotation increments for each frame
	//double rotation_pitch = 0.0, rotation_x_increment=0.1;
	//double rotation_yaw = 0.0, rotation_y_increment=0.05;
	//double rotation_roll =0.0, rotation_z_increment=0.03;

	typedef struct{
		float x,y,z;
	}vector;

	vector normal[100000];
	vector tempNormal;
	vector eyePosition = {-30.0, 1.0, -20.0};
	vector centerPosition = {0.0, 1.0, 0.0};
	vector Fwd = {0.0, 0.0, 1.0};
	vector Up = {0.0, 1.0, 0.0};
	vector Right = {1.0, 0.0, 0.0};
	vector curFwd = {0.0, 0.0, 1.0};
	vector curUp = {0.0, 1.0, 0.0};
	vector curRight = {1.0, 0.0, 0.0};



	void orientation(){
//		vector fwd, up, right;
	}




void normalCalc(int n){
	
	float ax,ay,az,bx,by,bz,cx,cy,cz;

	bx = x[p1[n]] - x[p2[n]];
	by = y[p1[n]] - y[p2[n]];
	bz = z[p1[n]] - z[p2[n]];
	cx = x[p2[n]] - x[p3[n]];
	cy = y[p2[n]] - y[p3[n]];
	cz = z[p2[n]] - z[p3[n]];
	
	ax = by * cz - cy * bz; 
	ay = bz * cx - cz * bx; 
	az = bx * cy - cx * by;

	tempNormal.x = ax;
	tempNormal.y = ay;
	tempNormal.z = az;	
}

void normalAverage(int m){
	int num = 0, face[100000];
	float tempx = 0.0, tempy = 0.0, tempz = 0.0;

	for(int l = 0; l < Fnum + 1; l++){
		if(p1[l] == m){
			face[num] = l;
			num++;
		}
		if(p2[l] == m){
			face[num] = l;
			num++;
		}
		if(p3[l] == m){
			face[num] = l;
			num++;
		}
	}

//	printf("%d", num);
	for(int o = 0; o < num; o++){
		normalCalc(face[o]);
		tempx += tempNormal.x;
		tempy += tempNormal.y;
		tempz += tempNormal.z;
	}
	
	float numDivOne = 1.0f/num;
	tempx = tempx * numDivOne;
	tempy = tempy * numDivOne;
	tempz = tempz * numDivOne;
//	printf("%f", numDivOne);
	
	float length = sqrt(tempx * tempx + tempy * tempy + tempz * tempz);

//	printf("%f,", length);
	normal[m].x = tempx / length;
	normal[m].y = tempy / length;
	normal[m].z = tempz / length;
	length = sqrt(normal[m].x * normal[m].x + normal[m].y * normal[m].y + normal[m].z * normal[m].z);
//	printf("%f,", length);
//	printf("\n%f, %f, %f", normal[m].x, normal[m].y, normal[m].z);
}


void keyboard(unsigned char p_key, int p_x, int p_y)
{  
    switch (p_key)
    {
        case 's':
			Fwd.x = curFwd.x * cos(3.142/180) + curUp.x * sin(3.142/180);
			Fwd.y = curFwd.y * cos(3.142/180) + curUp.y * sin(3.142/180);
			Fwd.z = curFwd.z * cos(3.142/180) + curUp.z * sin(3.142/180);
			Up.x = - curFwd.x * sin(3.142/180) + curUp.x * cos(3.142/180);
			Up.y = - curFwd.y * sin(3.142/180) + curUp.y * cos(3.142/180);
			Up.z = - curFwd.z * sin(3.142/180) + curUp.z * cos(3.142/180);
        break;
		case 'w':
			Fwd.x = curFwd.x * cos(-3.142/180) + curUp.x * sin(-3.142/180);
			Fwd.y = curFwd.y * cos(-3.142/180) + curUp.y * sin(-3.142/180);
			Fwd.z = curFwd.z * cos(-3.142/180) + curUp.z * sin(-3.142/180);
			Up.x = - curFwd.x * sin(-3.142/180) + curUp.x * cos(-3.142/180);
			Up.y = - curFwd.y * sin(-3.142/180) + curUp.y * cos(-3.142/180);
			Up.z = - curFwd.z * sin(-3.142/180) + curUp.z * cos(-3.142/180);
        break;
		case 'd':
			Fwd.x = curFwd.x * cos(3.142/180) - curRight.x * sin(3.142/180);
			Fwd.y = curFwd.y * cos(3.142/180) - curRight.y * sin(3.142/180);
			Fwd.z = curFwd.z * cos(3.142/180) - curRight.z * sin(3.142/180);
			Right.x = curFwd.x * sin(3.142/180) + curRight.x * cos(3.142/180);
			Right.y = curFwd.y * sin(3.142/180) + curRight.y * cos(3.142/180);
			Right.z = curFwd.z * sin(3.142/180) + curRight.z * cos(3.142/180);
		break;
		case 'a':
			Fwd.x = curFwd.x * cos(-3.142/180) - curRight.x * sin(-3.142/180);
			Fwd.y = curFwd.y * cos(-3.142/180) - curRight.y * sin(-3.142/180);
			Fwd.z = curFwd.z * cos(-3.142/180) - curRight.z * sin(-3.142/180);
			Right.x = curFwd.x * sin(-3.142/180) + curRight.x * cos(-3.142/180);
			Right.y = curFwd.y * sin(-3.142/180) + curRight.y * cos(-3.142/180);
			Right.z = curFwd.z * sin(-3.142/180) + curRight.z * cos(-3.142/180);
		break;
		case 'e':
			Up.x = curUp.x * cos(3.142/180) - curRight.x * sin(3.142/180);
			Up.y = curUp.y * cos(3.142/180) - curRight.y * sin(3.142/180);
			Up.z = curUp.z * cos(3.142/180) - curRight.z * sin(3.142/180);
			Right.x = curUp.x * sin(3.142/180) + curRight.x * cos(3.142/180);
			Right.y = curUp.y * sin(3.142/180) + curRight.y * cos(3.142/180);
			Right.z = curUp.z * sin(3.142/180) + curRight.z * cos(3.142/180);
		break;
		case 'q':
			Up.x = curUp.x * cos(-3.142/180) - curRight.x * sin(-3.142/180);
			Up.y = curUp.y * cos(-3.142/180) - curRight.y * sin(-3.142/180);
			Up.z = curUp.z * cos(-3.142/180) - curRight.z * sin(-3.142/180);
			Right.x = curUp.x * sin(-3.142/180) + curRight.x * cos(-3.142/180);
			Right.y = curUp.y * sin(-3.142/180) + curRight.y * cos(-3.142/180);
			Right.z = curUp.z * sin(-3.142/180) + curRight.z * cos(-3.142/180);
		break;
		case 'l':
            eyePosition.x = eyePosition.x - 0.1 * Up.x;
			eyePosition.y = eyePosition.y - 0.1 * Up.y;
			eyePosition.z = eyePosition.z - 0.1 * Up.z;
		break;
		case 'h':
            eyePosition.x = eyePosition.x + 0.1 * Up.x;
			eyePosition.y = eyePosition.y + 0.1 * Up.y;
			eyePosition.z = eyePosition.z + 0.1 * Up.z;
		break;
		case 27:
			exit(0);
		break;

    }
}


void keyboard_s (int p_key, int p_x, int p_y)
{
    switch (p_key)
    {
        case GLUT_KEY_UP:
            eyePosition.x = eyePosition.x + 0.1 * Fwd.x;
			eyePosition.y = eyePosition.y + 0.1 * Fwd.y;
			eyePosition.z = eyePosition.z + 0.1 * Fwd.z;
			//printf("haha1 %f", eyePosition_z_increment);
        break;
        case GLUT_KEY_DOWN:
            eyePosition.x = eyePosition.x - 0.1 * Fwd.x;
			eyePosition.y = eyePosition.y - 0.1 * Fwd.y;
			eyePosition.z = eyePosition.z - 0.1 * Fwd.z;
			//printf("haha2 %f", eyePosition_z_increment);
        break;
        case GLUT_KEY_LEFT:
            eyePosition.x = eyePosition.x + 0.1 * Right.x;
			eyePosition.y = eyePosition.y + 0.1 * Right.y;
			eyePosition.z = eyePosition.z + 0.1 * Right.z;
			//printf("haha3 %f", eyePosition_x_increment);
        break;
        case GLUT_KEY_RIGHT:
			eyePosition.x = eyePosition.x - 0.1 * Right.x;
			eyePosition.y = eyePosition.y - 0.1 * Right.y;
			eyePosition.z = eyePosition.z - 0.1 * Right.z;            
			//printf("haha4 %f", eyePosition_x_increment);
        break;
    }
}


void renderScene()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();
  //glutSolidTorus(5.0, 7.0, 20, 20);
  //glRotatef(angle, 0.0, 1.0, 0.0);
/*
  float diff[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
  float amb[4] = { 0.9f, 0.9f, 0.9f, 1.0f };
	glMaterialfv (GL_FRONT, GL_AMBIENT, amb);
    glMaterialfv (GL_FRONT, GL_DIFFUSE, diff);
	*/
    //glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_specular);
    //glMaterialfv (GL_FRONT, GL_POSITION, mat_shininess);    



  for(int i = 0; i < Fnum + 1; i++){
		glBegin(GL_TRIANGLES);

		if(strcmp(partColour[i], black)==0){glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_ambientBlack);}
		if(strcmp(partColour[i], red)==0){glMaterialfv (GL_FRONT, GL_AMBIENT, mat_ambientRed);}
		if(strcmp(partColour[i], green)==0){glMaterialfv (GL_FRONT, GL_AMBIENT, mat_ambientGreen);}
		if(strcmp(partColour[i], yellow)==0){glMaterialfv (GL_FRONT, GL_AMBIENT, mat_ambientYellow);}
		if(strcmp(partColour[i], grey)==0){glMaterialfv (GL_FRONT, GL_AMBIENT, mat_ambientGrey);}
		if(strcmp(partColour[i], blue)==0){glMaterialfv (GL_FRONT, GL_AMBIENT, mat_ambientBlue);}
		if(strcmp(partColour[i], white)==0){glMaterialfv (GL_FRONT, GL_AMBIENT, mat_ambientWhite);}	

		glMaterialfv (GL_FRONT, GL_AMBIENT, mat_ambientBlue);
		
		glNormal3f(normal[p1[i]].x, normal[p1[i]].y, normal[p1[i]].z);
		glVertex3f(y[p1[i]], z[p1[i]], x[p1[i]]);
		glNormal3f(normal[p2[i]].x, normal[p2[i]].y, normal[p2[i]].z);
		glVertex3f(y[p2[i]], z[p2[i]], x[p2[i]]);
		glNormal3f(normal[p3[i]].x, normal[p3[i]].y, normal[p3[i]].z);
		glVertex3f(y[p3[i]], z[p3[i]], x[p3[i]]);
		glEnd();
//		printf("%f %f %f", normal[p1[i]].x, normal[p1[i]].y, normal[p1[i]].z);
	}

  
  glFlush();

  glPopMatrix();
/*
  float planeDiff[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
  float planeAmb[4] = { 0.3f, 0.3f, 0.3f, 1.0f };
  glMaterialfv (GL_FRONT, GL_AMBIENT, planeAmb);
  glMaterialfv (GL_FRONT, GL_DIFFUSE, planeDiff);
  glBegin(GL_POLYGON);
  glNormal3f(0.0, -1.0, 0.0);
  glVertex3f(1000, 0, 1000);
  glVertex3f(1000, 0, -1000);
  glVertex3f(-1000, 0, -1000);
  glVertex3f(-1000, 0, 1000);
  glEnd();*/
/*
  if(Fwd.x == 0){Fwd.x = 1;}
  if(Fwd.y == 0){Fwd.y = 1;}
  if(Fwd.z == 0){Fwd.z = 1;}
  if(Up.x == 0){Up.x = 1;}
  if(Up.y == 0){Up.y = 1;}
  if(Up.z == 0){Up.z = 1;}
  if(Right.x == 0){Right.x = 1;}
  if(Right.y == 0){Right.y = 1;}
  if(Right.z == 0){Right.z = 1;}
 */ 
	centerPosition.x = eyePosition.x + Fwd.x;
	centerPosition.y = eyePosition.y + Fwd.y;
	centerPosition.z = eyePosition.z + Fwd.z;
	curFwd = Fwd;
	curUp = Up;
	curRight = Right;

	glLoadIdentity();
    gluLookAt(eyePosition.x, eyePosition.y, eyePosition.z, centerPosition.x, centerPosition.y, centerPosition.z, Up.x, Up.y, Up.z);

  glutSwapBuffers();

  //angle++;
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0); // Clear background color to black
   
	//Lights initialization and activation
    glLightfv (GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv (GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv (GL_LIGHT1, GL_DIFFUSE, light_specular);
    glLightfv (GL_LIGHT1, GL_POSITION, light_position);    
    glEnable (GL_LIGHT1);
    glEnable (GL_LIGHTING);

    //Materials initialization and activation
/*	glMaterialfv (GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_specular);
    glMaterialfv (GL_FRONT, GL_POSITION, mat_shininess);    
*/
	//Other initializations
    glShadeModel(GL_SMOOTH); // Type of shading for the polygons
	//glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Texture mapping perspective correction (OpenGL... thank you so much!)
    //glEnable(GL_TEXTURE_2D); // Texture mapping ON
    glPolygonMode (GL_FRONT_AND_BACK, GL_FILL); // Polygon rasterization mode (polygon filled)
	//glEnable(GL_CULL_FACE); // Enable the back face culling
    glEnable(GL_DEPTH_TEST); // Enable the depth test (also called z buffer)
}



void resizeWindow(int w, int h)
{
  if (h == 0)
    h = 1;
  
  float ratio = 1.0 * w/h;

  

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0, 0, w, h);
  gluPerspective(45, ratio, 1, 1000);
  glMatrixMode(GL_MODELVIEW);
  
  //glScalef(1,1,1);
}

void main(int argc, char **argv) 
{

	if((fin = fopen("building3.m","r"))==NULL)
	{
		printf("\nerror on open input file!");

		getchar();
		exit(1);
	}

	while(fgetc(fin)!=EOF){
		fscanf(fin,"%s",t);
		
		if(strcmp(t,preword1)==0){
			fscanf(fin,"%s",t);
			if(strcmp(t,preword1)==0){
				fscanf(fin,"%s",colour);
//				printf("%s", colour);
			}
			
		}

		if(strcmp(t,preword4)==0){
			fscanf(fin,"%d",&num);
//			printf("%d\n",num);
			fscanf(fin,"%f",&x[num]);
//			printf("%f,", x[num]);
			fscanf(fin,"%f",&y[num]);
//			printf("%f,", y[num]);
			fscanf(fin,"%f",&z[num]);
//			printf("%f,\n", z[num]);
			x[num] = x[num]/1000;
			y[num] = y[num]/1000;
			z[num] = z[num]/1000;
			Vnum = num;
		}
		else if(strcmp(t,preword5)==0){
			fscanf(fin,"%d",&num);
//			printf("%f,\n", num);
			fscanf(fin,"%d",&p1[num]);
//			printf("%f,", p1[num]);
			fscanf(fin,"%d",&p2[num]);
//			printf("%f,", p2[num]);
			fscanf(fin,"%d",&p3[num]);
//			printf("%f,\n", p3[num]);
			strcpy(partColour[num],colour);
			Fnum = num;
		}
		
	}

	for(int l = 0; l < Vnum + 1; l++){
		normalAverage(l);
	}

//	normalAverage(1406);

  	
  glutInit(&argc, argv);
  glutInitWindowPosition(10,0);
  glutInitWindowSize(1380, 980);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow("CSI-Building");
  init();
  glutDisplayFunc(renderScene);
  glutIdleFunc(renderScene); 
  glutReshapeFunc(resizeWindow);
  glutKeyboardFunc (keyboard);
  glutSpecialFunc (keyboard_s);
  glutMainLoop();
  return;
}
