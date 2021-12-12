#include "stdafx.h"
#include "CPortal.h"
#include "CPlane.h"
#include "CTexture.h"
#include "CRenderManager.h"
#include "CShader.h"

CPortal::CPortal()
{
}

CPortal::~CPortal()
{
}

HRESULT CPortal::Initialize(string strMesh, glm::vec3 vPos, glm::vec3 vScale)
{
	CObj::Initialize();
	pPlane = CPlane::Create();
	pTexture = CTexture::Create("", strMesh);
	pPlane->GetPos() = vPos;
	pPlane->GetScale() = vScale * glm::vec3(pTexture->Get_Width() * 0.5f, pTexture->Get_Height() * 0.5f, 1.f);

	m_matProj = glm::ortho(0.f, (float)WINCX, 0.f, (float)WINCY, 0.f, 100.0f);					// 직교투영하는것임

	m_matView = glm::mat4(1.f);
	return NOERROR;
}

GLint CPortal::Update(const GLfloat fTimeDelta)
{
	m_pRender->Add_RenderObj(REDER_UI, this);
	return GLint();
}

GLvoid CPortal::Render()
{
	GLuint program = m_pShaderLoader->Use_Shader("UI");
	int viewLoc = glGetUniformLocation(program, "viewTransform");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(m_matView));
	int ProjLoc = glGetUniformLocation(program, "projectionTransform");
	glUniformMatrix4fv(ProjLoc, 1, GL_FALSE, value_ptr(m_matProj));

	pPlane->Render();
	pTexture->Render();
	return GLvoid();
}

GLvoid CPortal::Release()
{
	return GLvoid();
}

CPortal* CPortal::Create(string strMesh, glm::vec3 vPos, glm::vec3 vScale)
{
	CPortal* pInstance = new CPortal;

	if (FAILED(pInstance->Initialize(strMesh,vPos, vScale)))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
