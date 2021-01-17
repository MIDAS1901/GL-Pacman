/*
Computer Graphics ACADEMIC PROJECT for Semester 3
    PAC-MAN Game using Open Graphics Library
    Submitted by:
    1) NAVNEET DAS (3231 SE COMP-A)
    2) CHIRAG KAPIL(3213 SE COMP-A)
*/

//Add the <windows.h> header file if you are operating on Windows

#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <vector>
#include <deque>
#include <string>
#define _USE_MATH_DEFINES
#define M_PI 3.14159265359

using namespace std;

GLfloat r_bg = 0.73, g_bg = 0.16, b_bg = 0.96;
static bool replay = false;
static bool over = true;
static float squareSize = 50.0;
static float xIncrement = 0;
static float yIncrement = 0;
static int rotation = 0;
float* monster1 = new float[3] {10.5, 8.5, 1.0};
float* monster2 = new float[3] {13.5, 1.5, 2.0};
float* monster3 = new float[3] {4.5, 6.5, 3.0};
float* monster4 = new float[3] {2.5, 13.5, 4.0};
static vector<int> border = { 0, 0, 15, 1, 15, 15, 14, 1, 0, 14, 15, 15, 1, 14, 0, 0 };
static vector<int> obstaclesTop = { 2, 2, 3, 6, 3, 6, 4, 5, 4, 2, 5, 4, 5, 3, 6, 5, 6, 1, 9, 2, 7, 2, 8, 5, 9, 5, 10, 3, 10, 4, 11, 2, 11, 5, 12, 6, 12, 6, 13, 2 };
static vector<int> obstaclesMiddle = { 2, 9, 3, 7, 3, 7, 4, 8, 4, 9, 5, 11, 5, 6, 6, 10, 6, 10, 7, 8, 7, 8, 8, 9, 6, 7, 7, 6, 8, 6, 9, 7, 10, 6, 9, 10, 9, 10, 8, 8, 11, 9, 10, 11, 11, 8, 12, 7, 12, 7, 13, 9 };
static vector<int> obstaclesBottom = { 2, 10, 3, 13, 3, 13, 4, 12, 5, 12, 6, 13, 6, 13, 7, 11, 8, 11, 9, 13, 9, 13, 10, 12, 11, 12, 12, 13, 12, 13, 13, 10 };
static deque<float> food = { 1.5, 1.5, 1.5, 2.5, 1.5, 3.5, 1.5, 4.5, 1.5, 5.5, 1.5, 6.5, 1.5, 7.5, 1.5, 8.5, 1.5, 9.5, 1.5, 10.5, 1.5, 11.5, 1.5, 12.5, 1.5, 13.5, 2.5, 1.5, 2.5, 6.5, 2.5, 9.5, 2.5, 13.5, 3.5, 1.5, 3.5, 2.5, 3.5, 3.5, 3.5, 4.5, 3.5, 6.5, 3.5, 8.5, 3.5, 9.5, 3.5, 10.5, 3.5, 11.5, 3.5, 13.5, 4.5, 1.5, 4.5, 4.5, 4.5, 5.5, 4.5, 6.5, 4.5, 7.5, 4.5, 8.5, 4.5, 11.5, 4.5, 12.5, 4.5, 13.5, 5.5, 1.5, 5.5, 2.5, 5.5, 5.5, 5.5, 10.5, 5.5, 11.5, 5.5, 13.5, 6.5, 2.5, 6.5, 3.5, 6.5, 4.5, 6.5, 5.5, 6.5, 7.5, 6.5, 10.5, 6.5, 13.5, 7.5, 5.5, 7.5, 6.5, 7.5, 7.5, 7.5, 9.5, 7.5, 10.5, 7.5, 11.5, 7.5, 12.5, 7.5, 13.5, 8.5, 2.5, 8.5, 3.5, 8.5, 4.5, 8.5, 5.5, 8.5, 7.5, 8.5, 10.5, 8.5, 13.5, 9.5, 1.5, 9.5, 2.5, 9.5, 5.5, 9.5, 10.5, 9.5, 11.5, 9.5, 13.5, 10.5, 1.5, 10.5, 4.5, 10.5, 5.5, 10.5, 6.5, 10.5, 7.5, 10.5, 8.5, 10.5, 11.5, 10.5, 12.5, 10.5, 13.5, 11.5, 1.5, 11.5, 2.5, 11.5, 3.5, 11.5, 4.5, 11.5, 5.5, 11.5, 6.5, 11.5, 8.5, 11.5, 9.5, 11.5, 10.5, 11.5, 11.5, 11.5, 13.5, 12.5, 1.5, 12.5, 6.5, 12.5, 9.5, 12.5, 13.5, 13.5, 1.5, 13.5, 2.5, 13.5, 3.5, 13.5, 4.5, 13.5, 5.5, 13.5, 6.5, 13.5, 7.5, 13.5, 8.5, 13.5, 9.5, 13.5, 10.5, 13.5, 11.5, 13.5, 12.5, 13.5, 13.5 };
static vector<vector<bool>> bitmap;
bool* keyStates = new bool[256];
int points = 0;

void init(void){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	for (int i = 0; i < 256; i++){
		keyStates[i] = false;
	}
	bitmap.push_back({ true, true, true, true, true, true, true, true, true, true, true, true, true, true, true });
	bitmap.push_back({ true, false, false, false, false, false, false, false, false, false, false, false, false, false, true });
	bitmap.push_back({ true, false, true, true, true, true, false, true, true, false, true, true, true, false, true });
	bitmap.push_back({ true, false, false, false, false, true, false, true, false, false, false, false, true, false, true});
	bitmap.push_back({ true, false, true, true, false, false, false, false, false, true, true, false, false, false, true});
	bitmap.push_back({ true, false, false, true, true, false, true, true, true, true, false, false, true, false, true});
	bitmap.push_back({ true, true, false, false, false, false, true, false, true, true, false, true, true, false, true});
	bitmap.push_back({ true, true, true, true, true, false, false, false, true, false, false, false, false, false, true});
	bitmap.push_back({ true, true, false, false, false, false, true, false, true, true, false, true, true, false, true });
	bitmap.push_back({ true, false, false, true, true, false, true, true, true, true, false, false, true, false, true });
	bitmap.push_back({ true, false, true, true, false, false, false, false, false, true, true, false, false, false, true });
	bitmap.push_back({ true, false, false, false, false, true, false, true, false, false, false, false, true, false, true });
	bitmap.push_back({ true, false, true, true, true, true, false, true, true, false, true, true, true, false, true });
	bitmap.push_back({ true, false, false, false, false, false, false, false, false, false, false, false, false, false, true });
	bitmap.push_back({ true, true, true, true, true, true, true, true, true, true, true, true, true, true, true });
}

void Maze_Model(){
	glColor3f(1.0, 1.0, 1.0);
	for (int i = 0; i < border.size(); i = i + 4){
		glRectf(border.at(i) * squareSize, border.at(i + 1)*squareSize, border.at(i + 2)*squareSize, border.at(i + 3)*squareSize);
	}
	for (int j = 0; j < obstaclesBottom.size(); j = j + 4){
		glRectf(obstaclesBottom.at(j) * squareSize, obstaclesBottom.at(j + 1)*squareSize, obstaclesBottom.at(j + 2)*squareSize, obstaclesBottom.at(j + 3)*squareSize);
	}
	for (int k = 0; k < obstaclesMiddle.size(); k = k + 4){
		glRectf(obstaclesMiddle.at(k) * squareSize, obstaclesMiddle.at(k + 1)*squareSize, obstaclesMiddle.at(k + 2)*squareSize, obstaclesMiddle.at(k + 3)*squareSize);
	}
	for (int p = 0; p < obstaclesTop.size(); p = p + 4){
		glRectf(obstaclesTop.at(p) * squareSize, obstaclesTop.at(p + 1)*squareSize, obstaclesTop.at(p + 2)*squareSize, obstaclesTop.at(p + 3)*squareSize);
	}
}

bool foodEaten(int x, int y, float pacmanX, float pacmanY){
	if (x >= pacmanX - 16.0 *cos(359 * M_PI / 180.0) && x <= pacmanX + 16.0*cos(359 * M_PI / 180.0)){
		if (y >= pacmanY - 16.0*cos(359 * M_PI / 180.0) && y <= pacmanY + 16.0*cos(359 * M_PI / 180.0)){
			return true;
		}
	}
	return false;
}

void Dot_Food_Model(float pacmanX, float pacmanY){
	deque<float> temp;
	for (int i = 0; i < food.size(); i = i + 2){
		if (!foodEaten(food.at(i)*squareSize, food.at(i + 1)*squareSize, pacmanX, pacmanY)){
			temp.push_back(food.at(i));
			temp.push_back(food.at(i + 1));
		}
		else {
			points++;
		}
	}
	food.swap(temp);
	glPointSize(5.0);
	glBegin(GL_POINTS);
	glColor3f(1.0, 1.0, 1.0);
	for (int j = 0; j < food.size(); j = j + 2){
		glVertex2f(food.at(j)*squareSize, food.at(j + 1)*squareSize);
	}
	glEnd();
}

void Pacman_Model(float positionX, float positionY, float rotation){
	int x, y;
	glBegin(GL_LINES);
	glColor3f(1.0, 1.0, 0.0);
	for (int k = 0; k < 32; k++){
		x = (float)k / 2.0 * cos((30 + 90*rotation) * M_PI / 180.0) + (positionX*squareSize);
		y = (float)k / 2.0* sin((30 + 90 * rotation) * M_PI / 180.0) + (positionY*squareSize);
		for (int i = 30; i < 330; i++){
			glVertex2f(x, y);
			x = (float)k / 2.0 * cos((i + 90 * rotation) * M_PI / 180.0) + (positionX*squareSize);
			y = (float)k / 2.0* sin((i + 90 * rotation) * M_PI / 180.0) + (positionY*squareSize);
			glVertex2f(x, y);
		}
	}
	glEnd();
}

void Monster_Model(float positionX, float positionY, float r, float g, float b){
	int x, y;
	glBegin(GL_LINES);
	glColor3f(r, g, b);
	for (int k = 0; k < 32; k++){
		x = (float)k / 2.0 * cos(360 * M_PI / 180.0) + (positionX*squareSize);
		y = (float)k / 2.0* sin(360 * M_PI / 180.0) + (positionY*squareSize);
		for (int i = 180; i <= 360; i++){
			glVertex2f(x, y);
			x = (float)k / 2.0 * cos(i * M_PI / 180.0) + (positionX*squareSize);
			y = (float)k / 2.0* sin(i * M_PI / 180.0) + (positionY*squareSize);
			glVertex2f(x, y);
		}
	}
	glEnd();
	glRectf((positionX*squareSize) - 17, positionY*squareSize, (positionX*squareSize) + 15, (positionY*squareSize) + 15);
	glBegin(GL_POINTS);
	glColor3f(r_bg, g_bg, b_bg);
	glVertex2f((positionX*squareSize) - 11, (positionY*squareSize) + 14);
	glVertex2f((positionX*squareSize) - 1, (positionY*squareSize) + 14);
	glVertex2f((positionX*squareSize) + 8, (positionY*squareSize) + 14);
	glVertex2f((positionX*squareSize) + 4, (positionY*squareSize) - 3);
	glVertex2f((positionX*squareSize) - 7, (positionY*squareSize) - 3);
	glEnd();
}

void Monster_Movement(float* monster, int id){
		int x1Quadrant = (int)((monster[0] - (2/squareSize)) - (16.0 *cos(360 * M_PI / 180.0)) / squareSize);
		int x2Quadrant = (int)((monster[0] + (2/squareSize)) + (16.0 *cos(360 * M_PI / 180.0)) / squareSize);
		int y1Quadrant = (int)((monster[1] - (2/squareSize)) - (16.0 *cos(360 * M_PI / 180.0)) / squareSize);
		int y2Quadrant = (int)((monster[1] + (2/squareSize)) + (16.0 *cos(360 * M_PI / 180.0)) / squareSize);
		switch ((int)monster[2]){
		case 1:
			if (!bitmap.at(x1Quadrant).at((int)monster[1])){
				monster[0] -= 2 / squareSize;
			}else {
				int current = monster[2];
				do{
					monster[2] =  (rand() % 4) + 1;
				} while (current == (int) monster[2]);
			}
			break;
		case 2:
			if (!bitmap.at(x2Quadrant).at((int)monster[1])){
				monster[0] += 2 / squareSize;
			}
			else {
				int current = monster[2];
				do{
					monster[2] = (rand() % 4) + 1;
				} while (current == (int)monster[2]);
			}
			break;
		case 3:
			if (!bitmap.at((int)monster[0]).at(y1Quadrant)){
				monster[1] -= 2 / squareSize;
			}
			else {
				int current = monster[2];
				do{
					monster[2] = (rand() % 4) + 1;
				} while (current == (int)monster[2]);
			}
			break;
		case 4:
			if (!bitmap.at((int)monster[0]).at(y2Quadrant)){
				monster[1] += 2 / squareSize;
			}
			else {
				int current = monster[2];
				do{
					monster[2] = (rand() % 4) + 1;
				} while (current == (int)monster[2]);
			}
			break;
		default:
			break;
		}
}

void keyPressed(unsigned char key, int x, int y){

    if(key==27){
        exit(0);
    }
    keyStates[key] = true;
}

void keyUp(unsigned char key, int x, int y){
	keyStates[key] = false;
}

void resetGame(){
	over = false;
	xIncrement = 0;
	yIncrement = 0;
	rotation = 0;
	monster1 = new float[3] {10.5, 8.5, 1.0};
	monster2 = new float[3] {13.5, 1.5, 2.0};
	monster3 = new float[3] {4.5, 6.5, 3.0};
	monster4 = new float[3] {2.5, 13.5, 4.0};
	points = 0;
	for (int i = 0; i < 256; i++){
		keyStates[i] = false;
	}
	food = { 1.5, 1.5, 1.5, 2.5, 1.5, 3.5, 1.5, 4.5, 1.5, 5.5, 1.5, 6.5, 1.5, 7.5, 1.5, 8.5, 1.5, 9.5, 1.5, 10.5, 1.5, 11.5, 1.5, 12.5, 1.5, 13.5, 2.5, 1.5, 2.5, 6.5, 2.5, 9.5, 2.5, 13.5, 3.5, 1.5, 3.5, 2.5, 3.5, 3.5, 3.5, 4.5, 3.5, 6.5, 3.5, 8.5, 3.5, 9.5, 3.5, 10.5, 3.5, 11.5, 3.5, 13.5, 4.5, 1.5, 4.5, 4.5, 4.5, 5.5, 4.5, 6.5, 4.5, 7.5, 4.5, 8.5, 4.5, 11.5, 4.5, 12.5, 4.5, 13.5, 5.5, 1.5, 5.5, 2.5, 5.5, 5.5, 5.5, 10.5, 5.5, 11.5, 5.5, 13.5, 6.5, 2.5, 6.5, 3.5, 6.5, 4.5, 6.5, 5.5, 6.5, 7.5, 6.5, 10.5, 6.5, 13.5, 7.5, 5.5, 7.5, 6.5, 7.5, 7.5, 7.5, 9.5, 7.5, 10.5, 7.5, 11.5, 7.5, 12.5, 7.5, 13.5, 8.5, 2.5, 8.5, 3.5, 8.5, 4.5, 8.5, 5.5, 8.5, 7.5, 8.5, 10.5, 8.5, 13.5, 9.5, 1.5, 9.5, 2.5, 9.5, 5.5, 9.5, 10.5, 9.5, 11.5, 9.5, 13.5, 10.5, 1.5, 10.5, 4.5, 10.5, 5.5, 10.5, 6.5, 10.5, 7.5, 10.5, 8.5, 10.5, 11.5, 10.5, 12.5, 10.5, 13.5, 11.5, 1.5, 11.5, 2.5, 11.5, 3.5, 11.5, 4.5, 11.5, 5.5, 11.5, 6.5, 11.5, 8.5, 11.5, 9.5, 11.5, 10.5, 11.5, 11.5, 11.5, 13.5, 12.5, 1.5, 12.5, 6.5, 12.5, 9.5, 12.5, 13.5, 13.5, 1.5, 13.5, 2.5, 13.5, 3.5, 13.5, 4.5, 13.5, 5.5, 13.5, 6.5, 13.5, 7.5, 13.5, 8.5, 13.5, 9.5, 13.5, 10.5, 13.5, 11.5, 13.5, 12.5, 13.5, 13.5 };
}

void keyOperations(){
	float  x = (1.5 + xIncrement) * squareSize;
	float y = (1.5 + yIncrement) * squareSize;
	if (keyStates['a'] || keyStates['A']){
		x -= 2;
		int x1Quadrant = (int)((x - 16.0 *cos(360 * M_PI / 180.0)) / squareSize);
		if (!bitmap.at(x1Quadrant).at((int)y/squareSize)){
			xIncrement -= 2 / squareSize;
			rotation = 2;
		}
	}
	if (keyStates['d'] || keyStates['D']){
		x += 2;
		int x2Quadrant = (int)((x + 16.0 *cos(360 * M_PI / 180.0)) / squareSize);
		if (!bitmap.at(x2Quadrant).at((int)y / squareSize)){
			xIncrement += 2 / squareSize;
			rotation = 0;
		}
	}
	if (keyStates['w'] || keyStates['W']){
		y -= 2;
		int y1Quadrant = (int)((y - 16.0 *cos(360 * M_PI / 180.0)) / squareSize);
		if (!bitmap.at((int)x/squareSize).at(y1Quadrant)){
			yIncrement -= 2 / squareSize;
			rotation = 3;
		}
	}
	if (keyStates['s'] || keyStates['S']){
		y += 2;
		int y2Quadrant = (int)((y + 16.0 *cos(360 * M_PI / 180.0)) / squareSize);
		if (!bitmap.at((int)x / squareSize).at(y2Quadrant)){
			yIncrement += 2 / squareSize;
			rotation = 1;
		}
	}
	if (keyStates[' ']){
		if (!replay && over){
			resetGame();
			replay = true;
		}
		else if (replay && over){
			replay = false;
		}
	}
	if (keyStates['r'] || keyStates['R']){
        resetGame();
        replay = true;
	}
}

void gameOver(){
	int pacmanX = (int)(1.5 + xIncrement);
	int pacmanY = (int)(1.5 + yIncrement);
	int monster1X = (int)(monster1[0]);
	int monster1Y = (int)(monster1[1]);
	int monster2X = (int)(monster2[0]);
	int monster2Y = (int)(monster2[1]);
	int monster3X = (int)(monster3[0]);
	int monster3Y = (int)(monster3[1]);
	int monster4X = (int)(monster4[0]);
	int monster4Y = (int)(monster4[1]);
	if (pacmanX == monster1X && pacmanY == monster1Y){
		over = true;
	}
	if (pacmanX == monster2X && pacmanY == monster2Y){
		over = true;
	}
	if (pacmanX == monster3X && pacmanY == monster3Y){
		over = true;
	}
	if (pacmanX == monster4X && pacmanY == monster4Y){
		over = true;
	}
	if (points == 106){
		over = true;
	}
}

void resultsDisplay(){
    glClearColor(r_bg, g_bg, b_bg, 1.0);
	if (points == 106){
		char* message = "*************************************";
		glRasterPos2f(170, 250);
		while (*message)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
		message = "CONGRATULATIONS, YOU WON! ";
		glColor3f(1, 1, 1);
		glRasterPos2f(200, 300);
		while (*message)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
		message = "*************************************";
		glRasterPos2f(170, 350);
		while (*message)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
		message = "INSTRUCTIONS FOR THE GAME";
        glRasterPos2f(200, 420);
        while (*message)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
        message = "To control Pac-Man use A to go left, D to go right, W to go up and S to go down.";
        glRasterPos2f(40, 480);
        while (*message)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);
        message = "To restart the game at any point press the R key.";
        glRasterPos2f(170, 520);
        while (*message)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);
        message = "To start the game, press the space key.";
        glRasterPos2f(210, 560);
        while (*message)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);
        message = "Use the Right Mouse Button to change Background Color, Restart Game.";
        glRasterPos2f(80, 600);
        while (*message)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);
        message = "Use the Escape Key to exit the game.";
        glRasterPos2f(210, 640);
        while (*message)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);
        message = "Created by Navneet Das and Chirag Kapil";
        glRasterPos2f(180, 730);
        while (*message)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
	}
	else {
        char* message = "*************************";
		glRasterPos2f(210, 200);
		while (*message)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
		message = "SORRY, YOU LOST ... ";
		glColor3f(1, 1, 1);
		glRasterPos2f(250, 250);
		while (*message)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
		message = "*************************";
		glRasterPos2f(210, 300);
		while (*message)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
		message = "You got:  ";
		glRasterPos2f(260, 360);
		while (*message)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
		string result = to_string(points*2);
		message = (char*)result.c_str();
		glRasterPos2f(350, 360);
		while (*message)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
		message = " points!";
		glRasterPos2f(385, 360);
		while (*message)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
		message = "INSTRUCTIONS FOR THE GAME";
        glRasterPos2f(200, 420);
        while (*message)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
        message = "To control Pac-Man use A to go left, D to go right, W to go up and S to go down.";
        glRasterPos2f(40, 480);
        while (*message)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);
        message = "To restart the game at any point press the R key.";
        glRasterPos2f(170, 520);
        while (*message)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);
        message = "To start the game, press the space key.";
        glRasterPos2f(210, 560);
        while (*message)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);
        message = "Use the Right Mouse Button to change Background Color, Restart Game.";
        glRasterPos2f(80, 600);
        while (*message)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);
        message = "Use the Escape Key to exit the game.";
        glRasterPos2f(210, 640);
        while (*message)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);
        message = "Created by Navneet Das and Chirag Kapil";
        glRasterPos2f(180, 730);
        while (*message)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
	}
}

void welcomeScreen(){
	glClearColor(r_bg, g_bg, b_bg, 1.0);
	char* message = "*************************************";
	glRasterPos2f(150, 130);
	while (*message)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
	message = "COMPUTER GRAPHICS MINI PROJECT";
	glRasterPos2f(155, 60);
	while (*message)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
    message = "Game Development Using OpenGL Library";
	glRasterPos2f(150, 170);
	while (*message)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
	message = "PAC-MAN : THE GAME";
	glColor3f(1, 1, 1);
	glRasterPos2f(235, 210);
	while (*message)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
    message = "Created By :";
	glColor3f(1, 1, 1);
	glRasterPos2f(300, 250);
	while (*message)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
    message = "Navneet Das(3231 SE Comp-A)";
	glColor3f(1, 1, 1);
	glRasterPos2f(200, 290);
	while (*message)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
    message = "Chirag Kapil(3213 SE Comp-A)";
	glColor3f(1, 1, 1);
	glRasterPos2f(200, 330);
	while (*message)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
	message = "*************************************";
	glRasterPos2f(150, 380);
	while (*message)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
    message = "INSTRUCTIONS FOR THE GAME";
	glRasterPos2f(200, 420);
	while (*message)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
	message = "To control Pac-Man use A to go left, D to go right, W to go up and S to go down.";
	glRasterPos2f(40, 480);
	while (*message)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);
    message = "To restart the game at any point press the R key.";
	glRasterPos2f(170, 520);
	while (*message)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);
	message = "To start the game, press the space key.";
	glRasterPos2f(210, 560);
	while (*message)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);
    message = "Use the Right Mouse Button to change Background Color, Restart Game.";
	glRasterPos2f(80, 600);
	while (*message)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);
    message = "Use the Escape Key to exit the game.";
	glRasterPos2f(210, 640);
	while (*message)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);
}

void display(){
	if (points == 1){
		over = false;
	}
	keyOperations();
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(r_bg, g_bg, b_bg, 1.0);
	gameOver();
	if (replay){
		if (!over){
			Maze_Model();
			Dot_Food_Model((1.5 + xIncrement) * squareSize, (1.5 + yIncrement) * squareSize);
			Pacman_Model(1.5 + xIncrement, 1.5 + yIncrement, rotation);
			Monster_Movement(monster1, 1);
			Monster_Movement(monster2, 2);
			Monster_Movement(monster3, 3);
			Monster_Movement(monster4, 4);
			Monster_Model(monster1[0], monster1[1], 0.0, 1.0, 1.0);
			Monster_Model(monster2[0], monster2[1], 1.0, 0.0, 0.0);
			Monster_Model(monster3[0], monster3[1], 0.0, 1.0, 0.0);
			Monster_Model(monster4[0], monster4[1], 1.0, 0.5, 0.0);
			glColor3f(0,0,0);
			char *current_score = "YOUR  SCORE: ";
            glRasterPos2f(280, 433);
            while (*current_score)
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *current_score++);
            string result = to_string(points*2);
            current_score = (char*)result.c_str();
            glRasterPos2f(458, 433);
            while (*current_score)
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *current_score++);
            current_score = "Created by Navneet Das and Chirag Kapil";
            glRasterPos2f(180, 730);
            while (*current_score)
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *current_score++);
		}
		else {
			resultsDisplay();
		}
	}
	else {
		welcomeScreen();
	}
	glutSwapBuffers();
}

void specialKeyListener(int key, int x, int y){
    float  xx = (1.5 + xIncrement) * squareSize;
	float yy = (1.5 + yIncrement) * squareSize;
    if(key==GLUT_KEY_UP){
        yy -= 2;
		int y1Quadrant = (int)((yy - 16.0 *cos(360 * M_PI / 180.0)) / squareSize);
		if (!bitmap.at((int)xx/squareSize).at(y1Quadrant)){
			yIncrement -= 2 / squareSize;
			rotation = 3;
		}
    }
    if(key==GLUT_KEY_DOWN){
        y += 2;
		int y2Quadrant = (int)((yy + 16.0 *cos(360 * M_PI / 180.0)) / squareSize);
		if (!bitmap.at((int)xx/squareSize).at(y2Quadrant)){
			yIncrement += 2 / squareSize;
			rotation = 1;
		}
    }
    if(key==GLUT_KEY_RIGHT){
        xx += 2;
		int x2Quadrant = (int)((x + 16.0 *cos(360 * M_PI / 180.0)) / squareSize);
		if (!bitmap.at(x2Quadrant).at((int)yy/ squareSize)){
			xIncrement += 2 / squareSize;
			rotation = 0;
		}
    }
    if(key==GLUT_KEY_LEFT){
        xx -= 2;
		int x1Quadrant = (int)((xx - 16.0 *cos(360 * M_PI / 180.0)) / squareSize);
		if (!bitmap.at(x1Quadrant).at((int)yy/squareSize)){
			xIncrement -= 2 / squareSize;
			rotation = 2;
		}
    }
    glutPostRedisplay();
	glFlush();
}

void reshape(int w, int h){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glOrtho(0, 750, 750, 0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void menu_color(int n)
{
    switch(n)
    {
        case 0 : exit(0);
                 break;
        case 1: r_bg = 0.73; g_bg = 0.16; b_bg = 0.96;
                break;
        case 2: r_bg = 0.06; g_bg = 0.33; b_bg = 0.019;
                break;
        case 3: r_bg = 0; g_bg = 0.2; b_bg = 0.4;
                break;
        case 4: r_bg = 0.33; g_bg = 0.0; b_bg = 0.0;
                break;
        case 5:
        {
                resetGame();
                replay = true;
        }
                break;
    }
    glutPostRedisplay();
}

void create_right_menu(){
    int submenu_background_color = glutCreateMenu(menu_color);
        glutAddMenuEntry("Background 1(Initial)", 1);
        glutAddMenuEntry("Background 2", 2);
        glutAddMenuEntry("Background 3", 3);
        glutAddMenuEntry("Background 4", 4);

    glutCreateMenu(menu_color);
        glutAddSubMenu("Color of the Background", submenu_background_color);
        glutAddMenuEntry("Restart", 5);
        glutAddMenuEntry("Exit", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(750, 750);
	glutInitWindowPosition(300, 50);
	glutCreateWindow("PAC-MAN - Created by Navneet Das And Chirag Kapil");
	create_right_menu();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(display);
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);
	glutSpecialFunc(specialKeyListener);
	init();
	glutMainLoop();
	return 0;
}
