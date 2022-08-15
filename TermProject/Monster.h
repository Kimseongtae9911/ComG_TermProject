#pragma once
#include "CObj.h"

class CMesh;

class Monster : public CObj
{
public:
	Monster();
	~Monster();

public:
	virtual HRESULT Initialize(string strMesh, glm::vec3 vPos, glm::vec3 vScale, int iType);
	virtual GLint Update(const GLfloat fTimeDelta);
	virtual GLvoid Render();

public:
	float LookPlayerAngle();
	int& GetDir() { return m_iDir; }
	int& GetCollDir() { return m_iCollideDir; }

private:
	bool Collide(DIR dir);
	GLvoid Release();

private:
	CMesh* m_pMonster = nullptr;
	GLfloat m_fAlpha{ 1.0f };
	int m_iType = 0;
	int iRotateCount = 0;
	int iLookRotCount = 0;
	int iMovingCount = 0;
	bool bMovingRotate = false;
	glm::vec3 vecPlayer3dPos = glm::vec3(0.0f);
	float fRatio = 0;
	int m_iDir{ 1 };
	int m_iCollideDir{ 0 };
	int m_iDir_3D{ 0 };
	bool m_bDie{ false };


public:
	static Monster* Create(string strMesh, glm::vec3 vPos, glm::vec3 vScale, int iType);
};

