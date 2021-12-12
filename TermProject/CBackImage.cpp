#include "stdafx.h"
#include "CBackImage.h"
#include "CTexture.h"
#include "CPlane.h"
#include "CRenderManager.h"
#include "CShader.h"

CBackImage::CBackImage()
{
}

CBackImage::~CBackImage()
{
}

HRESULT CBackImage::Initialize(string strTexTag, string strTexPath, bool bAlpha)
{
	CObj::Initialize();
	m_pTexture = CTexture::Create(strTexTag, strTexPath, bAlpha);
	m_pPlane = CPlane::Create();

	return NOERROR;
}

GLint CBackImage::Update(const GLfloat fTimeDelta)
{
	m_pRender->Add_RenderObj(REDER_BACK, this);
	return GLint();
}

GLvoid CBackImage::Render()
{
	glDisable(GL_DEPTH_TEST);
	
	m_pShaderLoader->Use_Shader("Back");
	m_pTexture->Render();
	m_pPlane->Render();
	glEnable(GL_DEPTH_TEST);
	

	return GLvoid();
}

GLvoid CBackImage::Release()
{
	return GLvoid();
}

CBackImage* CBackImage::Create(string strTexTag, string strTexPath, bool bAlpha)
{
	CBackImage* pInstance = new CBackImage;

	if (FAILED(pInstance->Initialize(strTexTag, strTexPath, bAlpha)))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
