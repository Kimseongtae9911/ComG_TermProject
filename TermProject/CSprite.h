#pragma once
#include "CObj.h"
class CPlane;
class CTexture;

class CSprite : public CObj
{
public:
	CSprite();
	~CSprite();
public:
	virtual HRESULT Initialize(glm::vec3 vPos, glm::vec3 vScale, string strTexTag, string strTexPath, bool bAlpha);
	virtual GLint Update(const GLfloat fTimeDelta);
	virtual GLvoid Render();

private:
	CPlane* m_pPlane;
	CTexture* m_pTexture;
	glm::mat4 m_matView = glm::mat4(1.f);
	glm::mat4 m_matProj = glm::mat4(1.f);

private:
	GLvoid Release();

public:
	static CSprite* Create(glm::vec3 vPos, glm::vec3 vScale, string strTexTag, string strTexPath, bool bAlpha = true);
};

