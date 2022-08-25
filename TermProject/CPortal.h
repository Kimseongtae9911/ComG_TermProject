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

public:
	CMesh* Get_pMesh() { return m_pPortal; };
	bool Get_NextStage() { return m_bNextStage; }
	void Set_NextStage(bool next) { m_bNextStage = next; }

private:
	CMesh* m_pPortal;
	int iRotateCount = 0;
	int iLookRotCount = 0;
	int iMovingCount = 0;
	bool bMovingRotate = false;
	bool m_bNextStage = false;

private:
	GLvoid Release();

public:
	static CPortal* Create(glm::vec3 vPos);
};

