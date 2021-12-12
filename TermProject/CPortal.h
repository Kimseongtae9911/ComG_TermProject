#pragma once
#include "CObj.h"

class CMesh;

class CPortal : public CObj
{
public:
	CPortal();
	~CPortal();

public:
	virtual HRESULT Initialize(glm::vec3 vPos);
	virtual GLint Update(const GLfloat fTimeDelta);
	virtual GLvoid Render();


private:
	CMesh* m_pPortal;
	int iRotateCount = 0;
	int iLookRotCount = 0;
	int iMovingCount = 0;
	bool bMovingRotate = false;

private:
	GLvoid Release();

public:
	static CPortal* Create(glm::vec3 vPos);
};

