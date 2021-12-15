#pragma once
#include "CObj.h"

class CMesh;

class CBullet : public CObj
{
public:
	CBullet();
	~CBullet();
public:
	virtual HRESULT Initialize(glm::vec3 vPos);
	virtual GLint Update(const GLfloat fTimeDelta);
	virtual GLvoid Render();

public:
	CMesh* Get_Mesh() { return m_pBullet; };

private:
	CMesh* m_pBullet;
	

private:
	GLvoid Release();

public:
	static CBullet* Create(glm::vec3 vPos);

};

