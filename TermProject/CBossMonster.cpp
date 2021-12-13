#include "stdafx.h"
#include "CBossMonster.h"
#include "CMesh.h"
#include"CBullet.h"
#include "CRenderManager.h"
#include "CShader.h"
#include "CGameManager.h"

CBossMonster::CBossMonster()
{
}

CBossMonster::~CBossMonster()
{
}

HRESULT CBossMonster::Initialize()
{
	CObj::Initialize();
	m_pBossMonster = CMesh::Create("../Resource/Monster/podoboo.obj", { 1.0, 1.0, 1.0, 1.0});
	m_pBossMonster->GetPos() = glm::vec3(5.0f, 0, 0);
	m_pBossMonster->GetScale() = glm::vec3(0.2f, 0.2f, 0.2f);
	m_pBossMonster->GetRotate().y = -20.f;
	return NOERROR;
}

GLint CBossMonster::Update(const GLfloat fTimeDelta)
{
	if (m_pGameMgr->Get_View())
	{
		if (!bMoveUpDown && m_pBossMonster->GetPos().y >= 5.f)
		{
			bMoveUpDown = !bMoveUpDown;
		}
		else if (bMoveUpDown && m_pBossMonster->GetPos().y <= 0.f)
		{
			bMoveUpDown = !bMoveUpDown;
		}
		if(!bMoveUpDown)
			m_pBossMonster->GetPos().y += 0.05f;
		else
			m_pBossMonster->GetPos().y -= 0.05f;
		
	}
	if (!bMovingRotate && m_pGameMgr->Get_View() == false)
	{
		++iRotateCount;
		m_pBossMonster->GetRotate().x += 90.f / 80.f;
		if (iRotateCount >= 80)
		{
			iRotateCount = 0;
			bMovingRotate = !bMovingRotate;
		}
	}
	else if (bMovingRotate && m_pGameMgr->Get_View())
	{
		++iRotateCount;
		m_pBossMonster->GetRotate().x -= 90.f / 80.f;
		if (iRotateCount >= 80)
		{
			iRotateCount = 0;
			bMovingRotate = !bMovingRotate;
		}
	}

	fTime += fTimeDelta;
	if (fTime >= 5)
	{
		CObj* pObj = CBullet::Create(m_pBossMonster->GetPos() + glm::vec3(0,2.5f,0));
		if (FAILED(m_pGameMgr->Add_GameObj(OBJ_BULLET, pObj)))
			return E_FAIL;
		cout << "11" << endl;
		fTime = 0;
	}
	m_pRender->Add_RenderObj(REDER_NONAL, this);
	return GLint();
}

GLvoid CBossMonster::Render()
{
	m_pShaderLoader->Use_Shader("Default");
	m_pGameMgr->Render_Camera();
	m_pBossMonster->Render();
	return GLvoid();
}

float CBossMonster::LookPlayerAngle()
{
	return 0.0f;
}

CBossMonster* CBossMonster::Create()
{
	CBossMonster* pInstance = new CBossMonster;
	if (FAILED(pInstance->Initialize()))
		SafeDelete(pInstance);
	return pInstance;
}
