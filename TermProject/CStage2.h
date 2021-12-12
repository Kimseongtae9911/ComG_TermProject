#pragma once
#include "CScene.h"

class CStage2 : public CScene
{
public:
	CStage2();
	~CStage2();

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
	static CStage2* Create();
};

