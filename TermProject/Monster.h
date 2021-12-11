#pragma once
#include "CObj.h"

class CMesh;

class Monster : public CObj
{
public:
	Monster();
	~Monster();

public:
	virtual HRESULT Initialize(glm::vec3 vPos);
	virtual GLint Update(const GLfloat fTimeDelta);
	virtual GLvoid Render();

private:
	CMesh* m_pMonster;
	GLfloat m_fAlpha{ 1.0f };
	int iRotateCount = 0;
	bool bMovingRotate = false;
public:
	static Monster* Create(glm::vec3 vPos);
};

