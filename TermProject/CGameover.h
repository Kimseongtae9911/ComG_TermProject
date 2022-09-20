#pragma once
#include "CScene.h"
class CGameover : public CScene
{
public:
	CGameover();
	~CGameover();

public:
	virtual HRESULT Initialize();
	virtual GLint Update(const GLfloat fTimeDelta);
	virtual GLvoid Render();


private:
	//CObj** m_pAni;
	//int iAniCounter = 0;
	float fTime = 0;
private:
	GLvoid Release();

public:
	static CGameover* Create();
};

