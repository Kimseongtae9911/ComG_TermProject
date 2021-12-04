#include "stdafx.h"
#include "main.h"

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Input_Mouse(int button, int state, int x, int y);
GLvoid Input_MouseMotion(int x, int y);
GLvoid SpecialKeyboard(int key, int x, int y);
GLvoid DoTimer(int value);


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINCX, WINCY);
	glutCreateWindow("Client");

	if (glewInit() != GLEW_OK) {
		cerr << "Unable to initialize GLEW" << endl;
		exit(EXIT_FAILURE);
	}
	else cout << "GLEW Initialized\n";


	glutReshapeFunc(Reshape);
	glutDisplayFunc(drawScene);

	glutMouseFunc(Input_Mouse);
	glutMotionFunc(Input_MouseMotion);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeyboard);

	glutMainLoop();

	return 0;
}

GLvoid drawScene(GLvoid)
{
	return GLvoid();
}

GLvoid Reshape(int w, int h)
{
	return GLvoid();
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	return GLvoid();
}

GLvoid Input_Mouse(int button, int state, int x, int y)
{
	return GLvoid();
}

GLvoid Input_MouseMotion(int x, int y)
{
	return GLvoid();
}

GLvoid SpecialKeyboard(int key, int x, int y)
{
	return GLvoid();
}

GLvoid DoTimer(int value)
{
	return GLvoid();
}