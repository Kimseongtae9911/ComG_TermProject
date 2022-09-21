#pragma once
#include "CObj.h"

class CMesh;

class Monster : public CObj
{
public:
	Monster();
	~Monster();

public:
	virtual HRESULT Initialize(string strMesh, glm::vec3 vPos, glm::vec3 vScale);
	virtual GLint Update(const GLfloat fTimeDelta);
	virtual GLvoid Render();

public:
	float LookPlayerAngle();
	int& GetDir() { return m_iDir; }
	int& GetCollDir() { return m_iCollideDir; }
	CMesh* Get_Mesh() { return m_pMonster; }

private:
	bool Collide();
	void ViewChange(const GLfloat fTimeDelta);
	void MonsterAI(const GLfloat fTimeDelta);
	void ChangeDir();
	GLvoid Release();

private:
	CMesh* m_pMonster = nullptr;
	GLfloat m_fAlpha{ 1.0f };
	int iRotateCount = 0;
	int iLookRotCount = 0;
	int iMovingCount = 0;
	bool bMovingRotate = false;
	glm::vec3 vecPlayer3dPos = glm::vec3(0.0f);
	glm::vec3 m_vec3PrevPos = glm::vec3(0.0f);
	glm::vec3 m_vec3PrevAngle = glm::vec3(0.0f);

	float fRatio = 0;
	int m_iDir{ 1 };
	int m_iDir2{ 1 };
	int m_iCollideDir{ 0 };
	int m_iDir_3D{ 0 };
	bool m_bDie{ false };


public:
	static Monster* Create(string strMesh, glm::vec3 vPos, glm::vec3 vScale);
};

#define LEFT_WALL -14.0f
#define RIGHT_WALL 13.0f

#define WALEMON_SPD 1.5f
#define BEEMON_SPD 0.025f