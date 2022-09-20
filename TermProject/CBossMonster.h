#pragma once
#include"CObj.h"
class CMesh;

class CBossMonster : public CObj
{
public:
	CBossMonster();
	~CBossMonster();
public:
	virtual HRESULT Initialize();
	virtual GLint Update(const GLfloat fTimeDelta);
	virtual GLvoid Render();

public:
	float LookPlayerAngle();
	GLvoid LookPlayer();

	GLvoid BossMove(const GLfloat fTimeDelta);
	int RandHeight();

	int& GetDir() { return m_iDir; }
	GLuint GetLife() { return m_iLife; }
	CMesh* Get_Mesh() { return m_pBossMonster; }
	bool GetBullet() { return m_bBullet; }

	GLvoid SetBullet(bool bBullet) { m_bBullet = bBullet; }
	GLvoid SetLife(const int ilife) { m_iLife = ilife; }

private:
	CMesh* m_pBossMonster;
	int m_iType;
	int iRotateCount = 0;
	int iLookRotCount = 0;
	int iMovingCount = 0;
	bool bMovingRotate = false;
	bool bMoveUpDown = false;
	glm::vec3 vecPlayer3dPos = glm::vec3(0.0f);
	int m_iDir{ 1 };
	float fTime = 0;
	float f3DTime = 0;
	GLuint m_iLife{ 3 };
	bool m_bBullet{ true };

	float m_fRotate = 0.0f;

public:
	static CBossMonster* Create();

};

