#pragma once

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	HRESULT Initialize();
	GLint Update(const GLfloat fTimeDelta);
	GLvoid Render();

private:
	HRESULT Initialize_Manager();
	HRESULT Initialize_Shader();

private:
	GLvoid Release();

public:
	static CMainGame* Create();
};
