#pragma once
#include "CScene.h"

class CBossMonster;
class CObj;
class CStage4: public CScene
{
public:
	CStage4();
	~CStage4();

public:
	virtual HRESULT Initialize();
	virtual GLint Update(const GLfloat fTimeDelta);
	virtual GLvoid Render();


private:
	CObj* m_pBox = nullptr;
	CBossMonster* m_pBoss = nullptr;	

	bool bMove = false;
	int iRotCount = 0;
	float fRotCount = 0;

private:
	GLvoid Reset();
	GLvoid Release();

public:
	static CStage4* Create();
};

