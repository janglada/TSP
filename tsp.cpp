/***************************************************************************
 *   Copyright (C) 2006 by Joan Anglada                                  *
 *   janglada(@)gmail.com                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <math.h>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <unistd.h>
//#include <GL/freeglut.h>
#include <GL/glut.h>
#include <zconf.h>
#include <GL/gl.h>
#include <cstring>
#include "ga.h"
#include "Sa.h"
#include "nn.h"

#define NCITIES 225
GA gen;
Sa sa;
nn Hop;

/*
*Funci� Render. S'executa constantment. Aqui �s crida evolve() i es pinten les linies i els cercles.
*/
void renderScene_SA(void);

void renderScene_GA(void);

void renderScene_NN(void);

void drawString(char *s, float cx, float cy);

void drawString2(char *st);

//void glutLeaveMainLoop(void);

void processNormalKeys(unsigned char key, int x, int y);

int generations;
double t0;
bool first;
int what;
using namespace std;

int main(int argc, char *argv[])
{

	first = false;
	t0 = 0.4;
	cout << "METODE?" << endl;
	cout << "1=GA" << endl;
	cout << "2=SIMULATED ANNEALTING" << endl;
	cout << "3=HOPFIELD NETWORK" << endl;
	cin >> what;
	switch (what) {
		case 1:

			glutInit(&argc, argv);
			glEnable(GL_DEPTH_TEST);
			glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
			glutInitWindowSize(500, 500);
			glutCreateWindow("TSP_GA");
			glutDisplayFunc(renderScene_GA);
			glutIdleFunc(renderScene_GA);
			glutKeyboardFunc(processNormalKeys);
			glEnable(GL_DEPTH_TEST);
			glutMainLoop();

			break;

		case 2:
			sa.inicialitza(NCITIES, t0);
			glutInit(&argc, argv);
			glEnable(GL_DEPTH_TEST);
			glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
			glutInitWindowSize(500, 500);
			glutCreateWindow("TSP_SA");
			glutDisplayFunc(renderScene_SA);
			glutIdleFunc(renderScene_SA);
			glutKeyboardFunc(processNormalKeys);
			glEnable(GL_DEPTH_TEST);
			glutMainLoop();

			break;

		case 3:
			Hop.init(t0, NCITIES);
			glutInit(&argc, argv);
			glEnable(GL_DEPTH_TEST);
			glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
			glutInitWindowSize(500, 500);
			glutCreateWindow("TSP_NN");
			glutDisplayFunc(renderScene_NN);
			glutIdleFunc(renderScene_NN);
			glutKeyboardFunc(processNormalKeys);
			glEnable(GL_DEPTH_TEST);
			glutMainLoop();

			break;
	}





	//     sa.~Sa();
	return EXIT_SUCCESS;
}

void renderScene_GA(void) {
	char str[100];
	char stri[100];
	int ngen = 7;
	float num_lines = 50;
	if (first == true) {
		for (int i = 0; i < ngen; i++)
			gen.evolve();
		// gen.go();
		generations = generations + ngen;
	} else usleep(10000);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 1.f, 0.0f, 1.0f);


	glColor3f(0, 0, 0);


	for (int k = 0; k < gen.getNcities(); k++) {
		glBegin(GL_LINES);
		if (k == gen.getNcities() - 1) {
			float x0 = 0;
			float y0 = 0;
			float x1 = 0;
			float y1 = 0;

			x0 = gen.getXcity(gen.getCity(k));
			y0 = gen.getYcity(gen.getCity(k));

			x1 = gen.getXcity(gen.getCity(0));
			y1 = gen.getYcity(gen.getCity(0));

			glVertex2f(x0, y0);
			glVertex2f(x1, y1);
		} else {
			float x0 = 0;
			float y0 = 0;
			float x1 = 0;
			float y1 = 0;

			x0 = gen.getXcity(gen.getCity(k));
			y0 = gen.getYcity(gen.getCity(k));

			x1 = gen.getXcity(gen.getCity(k + 1));
			y1 = gen.getYcity(gen.getCity(k + 1));

			glVertex2f(x0, y0);
			glVertex2f(x1, y1);
		}
		glEnd();

	}
	glColor3f(1.0, 0.0, 0.0);
	for (int j = 0; j < gen.getNcities(); j++) {

		glBegin(GL_POLYGON);

		float x0 = 0;
		float y0 = 0;
		x0 = gen.getXcity(j);
		y0 = gen.getYcity(j);
		// cout<<x0;
		float angle = 0;

		for (int i = 0; i < num_lines; i++) {
			// M_PI defined in cmath.h
			angle = i * 2 * M_PI / num_lines;
			// we use vertex2f since we are currently in working
			// in 2d.
			glVertex2f(x0 + 0.01 * cos(angle), y0 + 0.01 * sin(angle));
			// we don't need to multiply  by the length since the
			// radius is 1.
		}
		glEnd();

	}
	sprintf(stri, "%u", generations);
	sprintf(str, "%f", gen.getLength());

	//PrintString(str);
	//drawString (str);


	// drawString2 (stri);

	drawString(str, -0.975, -0.94);
	drawString(stri, -0.975, -0.99);
	glutSwapBuffers();          //FA LA ANIMACI� M�S SMOOTH

}


void renderScene_SA(void) {
	char str[100];
	char stri[100];
	char str2[100];
	float num_lines = 50;
	first = true;
	// for(int i=0;i<ngen;i++)
	// gen.evolve();
	usleep(1000);
	if (first == true) {
		sa.go();
		sa.changeT(generations);
		generations++;
		sa.go();
		sa.changeT(generations);
		generations++;
		sa.go();
		sa.changeT(generations);
		generations++;
		sa.go();
		sa.changeT(generations);
		generations++;
		sa.go();
		sa.changeT(generations);
		generations++;
		sa.go();
		sa.changeT(generations);
		generations++;
	} else { usleep(10000); }


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 1.f, 0.0f, 1.0f);


	glColor3f(0, 0, 0);


	for (int k = 0; k < sa.getNcities(); k++) {
		glBegin(GL_LINES);
		if (k == sa.getNcities() - 1) {
			float x0 = 0;
			float y0 = 0;
			float x1 = 0;
			float y1 = 0;

			x0 = sa.getXCity(k);
			y0 = sa.getYCity(k);

			x1 = sa.getXCity(0);
			y1 = sa.getYCity(0);


			glVertex2f(x0, y0);
			glVertex2f(x1, y1);
		} else {
			float x0 = 0;
			float y0 = 0;
			float x1 = 0;
			float y1 = 0;

			x0 = sa.getXCity(k);
			y0 = sa.getYCity(k);

			x1 = sa.getXCity(k + 1);
			y1 = sa.getYCity(k + 1);

			glVertex2f(x0, y0);
			glVertex2f(x1, y1);
		}
		glEnd();

	}
	glColor3f(1.0, 0.0, 0.0);
	for (int j = 0; j < sa.getNcities(); j++) {

		glBegin(GL_POLYGON);

		float x0 = 0;
		float y0 = 0;
		x0 = sa.getXCity(j);
		y0 = sa.getYCity(j);
		// cout<<x0;
		float angle = 0;

		for (int i = 0; i < num_lines; i++) {
			// M_PI defined in cmath.h
			angle = i * 2 * M_PI / num_lines;
			// we use vertex2f since we are currently in working
			// in 2d.
			glVertex2f(x0 + 0.01 * cos(angle), y0 + 0.01 * sin(angle));
			// we don't need to multiply  by the length since the
			// radius is 1.
		}
		glEnd();

	}


	//PrintString(str);


	sprintf(stri, "%u", generations);
	sprintf(str, "%f", sa.getLength());
	sprintf(str2, "%.20f", sa.getTemp());

	drawString(str, -0.95, -0.94);
	drawString(stri, -0.95, -0.99);
	drawString(str2, -0.8, -0.99);
	//drawString2 (stri);

	glutSwapBuffers();          //FA LA ANIMACI� M�S SMOOTH

}


void renderScene_NN(void) {
	char str[100];
	char stri[100];
	char str2[100];
	float num_lines = 50;
	usleep(10000);
	// for(int i=0;i<ngen;i++)
	// gen.evolve();
	if (first == true) {
		Hop.step();
		generations++;
		Hop.increaseParameters();
		Hop.getLength();
	}
	else { usleep(10000); }


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 1.f, 0.0f, 1.0f);


	glColor3f(0, 0, 0);


	for (int k = 0; k < NCITIES; k++) {
		glBegin(GL_LINES);
		if (k == NCITIES - 1) {
			float x0 = 0;
			float y0 = 0;
			float x1 = 0;
			float y1 = 0;

			x0 = Hop.getXCity(k);
			y0 = Hop.getYCity(k);

			x1 = Hop.getXCity(0);
			y1 = Hop.getYCity(0);


			glVertex2f(x0, y0);
			glVertex2f(x1, y1);
		} else {
			float x0 = 0;
			float y0 = 0;
			float x1 = 0;
			float y1 = 0;

			x0 = Hop.getXCity(k);
			y0 = Hop.getYCity(k);

			x1 = Hop.getXCity(k + 1);
			y1 = Hop.getYCity(k + 1);

			glVertex2f(x0, y0);
			glVertex2f(x1, y1);
		}
		glEnd();

	}
	glColor3f(1.0, 0.0, 0.0);
	for (int j = 0; j < NCITIES; j++) {

		glBegin(GL_POLYGON);

		float x0 = 0;
		float y0 = 0;
		x0 = Hop.getXCity(j);
		y0 = Hop.getYCity(j);
		// cout<<x0;
		float angle = 0;

		for (int i = 0; i < num_lines; i++) {
			// M_PI defined in cmath.h
			angle = i * 2 * M_PI / num_lines;
			// we use vertex2f since we are currently in working
			// in 2d.
			glVertex2f(x0 + 0.01 * cos(angle), y0 + 0.01 * sin(angle));
			// we don't need to multiply  by the length since the
			// radius is 1.
		}
		glEnd();

	}


	//PrintString(str);


	sprintf(stri, "%u", generations);
	sprintf(str, "%f", Hop.getLength());
	//   sprintf(str2,"%.20f",sa.getTemp());

	drawString(str, -0.95, -0.895);
	drawString(stri, -0.95, -0.99);
	//   drawString( str2,-0.7,-0.99);
	//drawString2 (stri);

	glutSwapBuffers();          //FA LA ANIMACI� M�S SMOOTH

}

void drawString(char *s, float cx, float cy) {
	glColor3f(0, 0, 1);
	glRasterPos2f(cx, cy);

	unsigned int i;
	for (i = 0; i < strlen(s); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, s[i]);
};

void drawString2(char *st) {
	glColor3f(0, 0, 1);
	glRasterPos2f(-0.9, -0.99);
	unsigned int i;
	for (i = 0; i < strlen(st); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, st[i]);
};

void processNormalKeys(unsigned char key, int x, int y) {

	switch (key) {
		//	sa.~Sa();

		case 27:
			first = true;
			break;
		case 113:
//			glutLeaveMainLoop();
			break;
		case 103:
			switch (what) {
				case 1:
					gen.printBestSolution();
					break;
				case 2:
					sa.printBestSolution();
					break;

				default:

					break;
			}
			// sa.changeT();
			//sa.go();

			//  Hop.step();
			generations++;
			break;
		case 112:
			//  Hop.printMaxtrix();
			// Hop.printVectorSol();
			break;
		case 115:
			if (first == true) first = false;
			else first = true;

			break;
		default:
			break;
			// sa.printSol();
			//first=true;
	}
}
