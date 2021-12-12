#pragma once
#include "CObj.h"

class CPlane;
class CTexture;

class CPortal : public CObj
{
public:
	CPortal();
	~CPortal();

public:
	virtual HRESULT Initialize(string strMesh, glm::vec3 vPos, glm::vec3 vScale);
	virtual GLint Update(const GLfloat fTimeDelta);
	virtual GLvoid Render();


private:
	glm::mat4 m_matView = glm::mat4(1.f);
	glm::mat4 m_matProj = glm::mat4(1.f);

private:
	CPlane* pPlane;
	CTexture* pTexture;

private:
	GLvoid Release();

public:
	static CPortal* Create(string strMesh, glm::vec3 vPos, glm::vec3 vScale);
};

