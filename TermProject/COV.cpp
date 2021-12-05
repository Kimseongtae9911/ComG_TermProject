#include "stdafx.h"
#include "Manager.h"
#include "CMainGame.h"

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Input_Mouse(int button, int state, int x, int y);
GLvoid Input_MouseMotion(int x, int y);
GLvoid SpecialKeyboard(int key, int x, int y);
GLvoid DoTimer(int value);

GLvoid Check_Frame();

CMainGame* g_pMainGame;
CKeyManager* g_pKeyMgr;
CFrameManager* g_pFrameMgr;


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

	g_pKeyMgr = CKeyManager::GetInstance();
	g_pFrameMgr = CFrameManager::GetInstance();
	

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
	if (g_pFrameMgr->FrameLimit(60.f))
	{
		glClearColor(0, 0, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		g_pFrameMgr->UpdateTime();
		fTimeDelta = g_pFrameMgr->GetDelta();
		g_pKeyMgr->UpdateKey();
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

	g_fwTimerAcc += g_pFrameMgr->GetDelta();
	++g_iRenderCall;

	if (g_fwTimerAcc >= 1.0)
	{
		cout << "FPS : " << g_iRenderCall << endl;
		g_iRenderCall = 0;
		g_fwTimerAcc = 0.f;
	}
}