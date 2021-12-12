#pragma once
#include "CObj.h"
class CTexture;
class CPlane;
class CBackImage : public CObj 
{
public:
	CBackImage();
	~CBackImage();

public:
	virtual HRESULT Initialize(string strTexTag, string strTexPath, bool bAlpha);
	virtual GLint Update(const GLfloat fTimeDelta);
	virtual GLvoid Render();

private:
	CPlane* m_pPlane;
	CTexture* m_pTexture;

private:
	GLvoid Release();

public:
	static CBackImage* Create(string strTexTag, string strTexPath, bool bAlpha = true);
};

