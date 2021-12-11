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

public:
	float LookPlayerAngle();

private:
	CMesh* m_pMonster;
	GLfloat m_fAlpha{ 1.0f };
	int iRotateCount = 0;
	int iLookRotCount = 0;
	int iMovingCount = 0;
	bool bMovingRotate = false;
	glm::vec3 vecPlayer3dPos = glm::vec3(0.0f);
	float fRatio = 0;
public:
	static Monster* Create(glm::vec3 vPos);
};

