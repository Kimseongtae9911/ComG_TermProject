#pragma once
#include "CScene.h"

class CStage3: public CScene
{
public:
	CStage3();
	~CStage3();

public:
	virtual HRESULT Initialize();
	virtual GLint Update(const GLfloat fTimeDelta);
	virtual GLvoid Render();


private:
	bool bMove = false;
	int iRotCount = 0;
	float fRotCount = 0;

private:
	GLvoid Release();

public:
	static CStage3* Create();
};

