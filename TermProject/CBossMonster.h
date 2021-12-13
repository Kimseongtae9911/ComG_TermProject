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
	int& GetDir() { return m_iDir; }

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

public:
	static CBossMonster* Create();

};

