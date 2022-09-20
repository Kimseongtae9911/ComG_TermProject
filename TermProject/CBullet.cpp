#include "stdafx.h"
#include "CBullet.h"
#include "CMesh.h"
#include "CRenderManager.h"
#include "CGameManager.h"
#include "CShader.h"

CBullet::CBullet()
{
}

CBullet::~CBullet()
{
	Release();
}

HRESULT CBullet::Initialize(glm::vec3 vPos)
{
	CObj::Initialize();
	m_pBullet = CMesh::Create("../Resource/Bullet/itemKiller.obj", { 1.0, 1.0, 1.0, 1.0});
	m_pBullet->GetScale() = glm::vec3(0.05f, 0.05f, 0.05f);
	m_pBullet->GetPos() = vPos;
	m_pBullet->GetRotate().y = -80;
	return NOERROR;
}

GLint CBullet::Update(const GLfloat fTimeDelta)
{
	if (m_pBullet->GetPos().x >= -20.0f) {
		m_pBullet->GetPos().x -= 0.05f;
		m_pRender->Add_RenderObj(RENDER_ID::REDER_BULLET, this);
		CObj::UpdateAABB(m_pBullet->Get_Matrix(), glm::vec3(30.0f, 30.0f, 30.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	}
	return GLint();
}

GLvoid CBullet::Render()
{
	m_pShaderLoader->Use_Shader("Default");
	m_pGameMgr->Render_Camera();
	m_pBullet->Render();
	
	CObj::Render();

	return GLvoid();
}

GLvoid CBullet::Release()
{
	SafeDelete(m_pBullet);
	return GLvoid();
}

CBullet* CBullet::Create(glm::vec3 vPos)
{
	CBullet* pInstance = new CBullet;

	if (FAILED(pInstance->Initialize(vPos)))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
