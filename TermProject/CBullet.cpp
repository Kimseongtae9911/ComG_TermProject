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
	m_pBullet->GetPos().x -= 0.5;
	m_pRender->Add_RenderObj(REDER_BULLET, this);
	CBullet::Get_BB() = { m_pBullet->GetPos().x - 9.5f * m_pBullet->GetScale().x, m_pBullet->GetPos().x + 9.5f * m_pBullet->GetScale().x, m_pBullet->GetPos().y + 9.2f * m_pBullet->GetScale().y, m_pBullet->GetPos().y - 9.2f * m_pBullet->GetScale().y };
	return GLint();
}

GLvoid CBullet::Render()
{
	m_pShaderLoader->Use_Shader("Default");
	m_pGameMgr->Render_Camera();
	m_pBullet->Render();
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
