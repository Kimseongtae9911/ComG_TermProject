#pragma once
#include "CScene.h"
#include "CObj.h"

class CLoad : public CScene
{
public:
	CLoad();
	~CLoad();

public:
	virtual HRESULT Initialize();
	virtual GLint Update(const GLfloat fTimeDelta);
	virtual GLvoid Render();

private:
	CObj** m_pAni;
	int iAniCounter = 0;
	float fTime = 0;
	float fNextScene = 0;

private:
	GLvoid Release();

public:
	static CLoad* Create();
};

