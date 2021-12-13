#include "stdafx.h"
#include "CSprite.h"
#include "CTexture.h"
#include "CPlane.h"
#include "CRenderManager.h"
#include "CShader.h"

CSprite::CSprite()
{
}

CSprite::~CSprite()
{
}

HRESULT CSprite::Initialize(glm::vec3 vPos, glm::vec3 vScale, string strTexTag, string strTexPath, bool bAlpha)
{
	CObj::Initialize();
	m_pTexture = CTexture::Create(strTexTag, strTexPath, bAlpha);
	m_pPlane = CPlane::Create();
	m_pPlane->GetPos() = vPos;
	m_pPlane->GetScale() = vScale * glm::vec3(m_pTexture->Get_Width() * 0.5f, m_pTexture->Get_Height() * 0.5f, 1.f);

	m_matProj = glm::ortho(0.f, (float)WINCX, 0.f, (float)WINCY, 0.f, 100.0f);

	m_matView = glm::mat4(1.f);

	return NOERROR;
}

GLint CSprite::Update(const GLfloat fTimeDelta)
{
	m_pRender->Add_RenderObj(REDER_UI, this);
	return GLint();
}

GLvoid CSprite::Render()
{
	GLuint program = m_pShaderLoader->Use_Shader("UI");
	int viewLoc = glGetUniformLocation(program, "viewTransform");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(m_matView));
	int ProjLoc = glGetUniformLocation(program, "projectionTransform");
	glUniformMatrix4fv(ProjLoc, 1, GL_FALSE, value_ptr(m_matProj));

	m_pTexture->Render();
	m_pPlane->Render();

	return GLvoid();
}

GLvoid CSprite::Release()
{
	return GLvoid();
}

CSprite* CSprite::Create(glm::vec3 vPos, glm::vec3 vScale, string strTexTag, string strTexPath, bool bAlpha)
{
	CSprite* pInstance = new CSprite;

	if (FAILED(pInstance->Initialize(vPos, vScale, strTexTag, strTexPath, bAlpha)))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}