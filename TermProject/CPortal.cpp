#include "stdafx.h"
#include "CPortal.h"
#include "CMesh.h"
#include "CRenderManager.h"
#include "CShader.h"
#include "CGameManager.h"
#include "Player2.h"
#include "Player3.h"

CPortal::CPortal()
{
}

CPortal::~CPortal()
{
}

HRESULT CPortal::Initialize(glm::vec3 vPos)
{
	CObj::Initialize();
	m_pPortal = CMesh::Create("../Resource/Portal Door/Portal Door.obj", { 1.0, 1.0, 1.0, 0.3 });
	m_pPortal->GetScale() = glm::vec3(0.15f, 0.15f, 0.15f);
	m_pPortal->GetPos() = vPos;
	
	CPortal::Get_BB() = { m_pPortal->GetPos().x - 1.0f, m_pPortal->GetPos().x  + 1.0f,  m_pPortal->GetPos().y + 1.0f, m_pPortal->GetPos().y - 1.0f};
	CObj::UpdateAABB(m_pPortal->Get_Matrix(), glm::vec3(10.0f, 10.0f, 4.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	return NOERROR;
}

GLint CPortal::Update(const GLfloat fTimeDelta)
{
	if (!bMovingRotate && VIEW::VIEW_3D == m_pGameMgr->Get_View())
	{
		++iRotateCount;
		m_pPortal->GetRotate().x += 90.f / 80.f;
		if (iRotateCount >= 80)
		{
			iRotateCount = 0;
			bMovingRotate = !bMovingRotate;
		}
	}
	else if (bMovingRotate && VIEW::VIEW_2D == m_pGameMgr->Get_View())
	{
		++iRotateCount;
		m_pPortal->GetRotate().x -= 90.f / 80.f;
		if (iRotateCount >= 80)
		{
			iRotateCount = 0;
			bMovingRotate = !bMovingRotate;
		}
	}

	if (dynamic_cast<Player2*>(m_pGameMgr->Get_Obj(OBJ_ID::OBJ_PLAYER1).front())->Get_Portal() && dynamic_cast<Player3*>(m_pGameMgr->Get_Obj(OBJ_ID::OBJ_PLAYER2).front())->Get_Portal()) {
		m_bNextStage = true;
	}

	// Portal alpha blending
	if (m_pGameMgr->Get_Obj(OBJ_ID::OBJ_KEY).empty()) {
		for (auto& i : m_pPortal->GetSMESH()) {
			for (size_t j = 0; j < i->color.size(); ++j) {
				i->color[j][3] = 1.0;
			}
		}
	}

	CObj::UpdateAABB(m_pPortal->Get_Matrix(), glm::vec3(10.0f, 10.0f, 4.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	m_pRender->Add_RenderObj(RENDER_ID::REDER_NONAL, this);
	return GLint();
}

GLvoid CPortal::Render()
{
	m_pShaderLoader->Use_Shader("Default");
	m_pGameMgr->Render_Camera();
	m_pPortal->Render();

	CObj::Render();
	
	return GLvoid();
}

GLvoid CPortal::Release()
{
	return GLvoid();
}

CPortal* CPortal::Create(glm::vec3 vPos)
{
	CPortal* pInstance = new CPortal;

	if (FAILED(pInstance->Initialize(vPos)))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
