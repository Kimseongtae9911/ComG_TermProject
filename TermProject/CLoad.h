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
	CObj* m_pLifeWord;
	CObj* m_pLifePlayer1;
	CObj* m_pLifePlayer2;
	CObj* m_pLifePlayer3;
	CObj* m_pBox;
	int iAniCounter = 0;
	float fTime = 0;
	float fNextScene = 0;
	int m_iLife = 3;

private:
	GLvoid Release();

public:
	static CLoad* Create();
};

