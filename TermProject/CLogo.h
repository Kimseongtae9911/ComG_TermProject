#pragma once
#include "CScene.h"

class CLogo : public CScene
{
public:
	CLogo();
	~CLogo();

public:
	virtual HRESULT Initialize();
	virtual GLint Update(const GLfloat fTimeDelta);
	virtual GLvoid Render();


private:


private:
	GLvoid Release();

public:
	static CLogo* Create();

};

