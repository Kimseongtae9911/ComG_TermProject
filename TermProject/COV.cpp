#include "stdafx.h"
#include "CMainGame.h"
#include "CKeyManager.h"
#include "CFrameManager.h"

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Input_Mouse(int button, int state, int x, int y);
GLvoid Input_MouseMotion(int x, int y);
GLvoid SpecialKeyboard(int key, int x, int y);
GLvoid DoTimer(int value);

GLvoid Check_Frame();

CMainGame* g_pMainGame;

GLuint g_iRenderCall = 0;
float g_fwTimerAcc = 0.f;
float fTimeDelta = 0.f;


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

 	g_pMainGame = CMainGame::Create();
	if (!g_pMainGame)
	{
		cerr << "¡°Unable to initialize MainGame" << endl;
		exit(EXIT_FAILURE);
	}


	glutReshapeFunc(Reshape);
	glutDisplayFunc(drawScene);
	glutIdleFunc(drawScene);

	glutMouseFunc(Input_Mouse);
	glutMotionFunc(Input_MouseMotion);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeyboard);

	glutMainLoop();

	return 0;
}

GLvoid drawScene(GLvoid)
{
	if (CFrameManager::GetInstance()->FrameLimit(60.f))
	{
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		CFrameManager::GetInstance()->UpdateTime();
		fTimeDelta = CFrameManager::GetInstance()->GetDelta();
		CKeyManager::GetInstance()->UpdateKey();
		g_pMainGame->Update(fTimeDelta);
		g_pMainGame->Render();

		glutSwapBuffers();

		Check_Frame();
	}
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


GLvoid Check_Frame()
{

	g_fwTimerAcc += CFrameManager::GetInstance()->GetDelta();
	++g_iRenderCall;

	if (g_fwTimerAcc >= 1.0)
	{
		cout << "FPS : " << g_iRenderCall << endl;
		g_iRenderCall = 0;
		g_fwTimerAcc = 0.f;
	}
}