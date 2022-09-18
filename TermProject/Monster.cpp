#include "stdafx.h"
#include "Monster.h"
#include "CMesh.h"
#include "Player3.h"
#include "CKeyManager.h"
#include "CRenderManager.h"
#include "CShader.h"
#include "CGameManager.h"
#include "CCamera.h"

Monster::Monster()
{
}

Monster::~Monster()
{
	Release();
}

HRESULT Monster::Initialize(string strMesh, glm::vec3 vPos, glm::vec3 vScale)
{
	CObj::Initialize();
	m_pMonster = CMesh::Create(strMesh, { 1.0, 1.0, 1.0, m_fAlpha });
	m_pMonster->GetScale() = vScale;
	m_pMonster->GetPos() = vPos;

	if (OBJ_ID::OBJ_MONSTER1 == m_idObj)
		CObj::UpdateAABB(m_pMonster->Get_Matrix(), glm::vec3(4.0f, 4.0f, 4.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	else if (OBJ_ID::OBJ_MONSTER2 == m_idObj)
		CObj::UpdateAABB(m_pMonster->Get_Matrix(), glm::vec3(4000.0f, 4000.0f, 4000.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	return NOERROR;
}

GLint Monster::Update(const GLfloat fTimeDelta)
{
	if (m_bDie) {
		m_pMonster->GetPos() = { -30, 0, 0 };
	}
	
	ViewChange(fTimeDelta);

	MonsterAI(fTimeDelta);

	m_pRender->Add_RenderObj(RENDER_ID::REDER_NONAL, this);
	return GLint();
}

GLvoid Monster::Render()
{
	m_pShaderLoader->Use_Shader("Default");
	m_pGameMgr->Render_Camera();
	m_pMonster->Render();
	CObj::Render();

	return GLvoid();
}

float Monster::LookPlayerAngle()
{
	vecPlayer3dPos = dynamic_cast<Player3*>(m_pGameMgr->Get_Obj(OBJ_ID::OBJ_PLAYER2).front())->Get_pMesh()->GetPos();
	float dAngle = atan((vecPlayer3dPos.x - m_pMonster->GetPos().x) / (vecPlayer3dPos.y - m_pMonster->GetPos().y)) * 180/ PI;

	if (m_pMonster->GetPos().y <= vecPlayer3dPos.y)
	{
		if (m_pMonster->GetPos().x <= vecPlayer3dPos.x) // 1
		{
			return 180.f - dAngle;
		}
			
		else //   4
		{
			return 180.f - dAngle;
		}
	}
	else
	{
		if (m_pMonster->GetPos().x <= vecPlayer3dPos.x) //2
		{
			return -dAngle;
		}
		else // 3
		{
			return 360.f - dAngle;
		}
			
	}
}

bool Monster::Collide() {

	for (int j = static_cast<int>(OBJ_ID::OBJ_MAP); j <= static_cast<int>(OBJ_ID::OBJ_BOX); ++j) {
		for (const auto& obj : m_pGameMgr->Get_Obj(OBJ_ID(j))) {
			if (m_AABB.Intersects(obj->Get_AABB()))
				return true;
		}
	}

	return false;
}


void Monster::ViewChange(const GLfloat fTimeDelta)
{
	if (!bMovingRotate && VIEW::VIEW_3D == m_pGameMgr->Get_View())
	{
		++iRotateCount;
		m_pMonster->GetRotate().x += 90.f / 80.f;
		if (iRotateCount >= 80)
		{
			iRotateCount = 0;
			bMovingRotate = !bMovingRotate;
		}
	}
	else if (bMovingRotate && VIEW::VIEW_2D == m_pGameMgr->Get_View())
	{
		++iRotateCount;
		m_pMonster->GetRotate().x -= 90.f / 80.f;
		if (iRotateCount >= 80)
		{
			iRotateCount = 0;
			bMovingRotate = !bMovingRotate;
		}
	}
}

void Monster::MonsterAI(const GLfloat fTimeDelta)
{
	if (VIEW::VIEW_3D == m_pGameMgr->Get_View() && m_pGameMgr->Get_Camera()->Get_Move())
	{
		
		//Monster Rotate
		float f = LookPlayerAngle();
		if (f >= m_pMonster->GetRotate().y)
		{
			if (!Collide()) {
				m_vec3PrevAngle = m_pMonster->GetRotate();
				if (f - m_pMonster->GetRotate().y <= m_pMonster->GetRotate().y + 360 - f /*&& f >= m_pMonster->GetRotate().y*/)
				{
					m_pMonster->GetRotate().y += 5.5;
				}
				else
				{
					m_pMonster->GetRotate().y -= 5.5;
				}
			}
		}
		else
		{
			if (!Collide()) {
				m_vec3PrevAngle = m_pMonster->GetRotate();
				if (f + 360 - m_pMonster->GetRotate().y <= m_pMonster->GetRotate().y - f/* && f <= m_pMonster->GetRotate().y*/)
				{
					m_pMonster->GetRotate().y += 5.5;
				}
				else
				{
					m_pMonster->GetRotate().y -= 5.5;
				}
			}
		}

		if (m_pMonster->GetRotate().y >= 360)
		{
			m_pMonster->GetRotate().y -= 360;
		}
		else if (m_pMonster->GetRotate().y <= 0)
		{
			m_pMonster->GetRotate().y += 360;
		}

		//Monster Move
		m_iDir = (vecPlayer3dPos.x - m_pMonster->GetPos().x >= 0) ? 1 : -1; //x
		m_iDir2 = (vecPlayer3dPos.y - m_pMonster->GetPos().y >= 0) ? 1 : -1; //y

		if (Collide())
		{
			m_pMonster->SetPos(m_vec3PrevPos);
			m_pMonster->SetRotate(m_vec3PrevAngle);
		}
		else
		{
			m_vec3PrevPos = m_pMonster->GetPos();
			if (OBJ_ID::OBJ_MONSTER1 == m_idObj) {
				m_pMonster->Move(glm::vec3(m_iDir * WALEMON_SPD, m_iDir2 * WALEMON_SPD, 0.0f));
			}
			else {
				m_pMonster->Move(glm::vec3(m_iDir * BEEMON_SPD, m_iDir2 * BEEMON_SPD, 0.0f));
			}
		}
		
	}
	else if (VIEW::VIEW_2D == m_pGameMgr->Get_View() && !m_pGameMgr->Get_Camera()->Get_Move())
	{
		m_pMonster->GetRotate().y = 0;
		m_pMonster->Move(glm::vec3(0.06f * m_iDir, 0.0f, 0.0f));

		if (m_pMonster->GetPos().x >= RIGHT_WALL)
			m_iDir = -1;
		else if (m_pMonster->GetPos().x - 0.5 <= LEFT_WALL)
			m_iDir = 1;

		for (const auto& spike : m_pGameMgr->Get_Obj(OBJ_ID::OBJ_SPIKE)) {
			if (m_AABB.Intersects(spike->Get_AABB()))
				m_bDie = true;
		}

		if (OBJ_ID::OBJ_MONSTER1 == m_idObj) {
			if (!Collide()) {
				m_pMonster->Move(glm::vec3(0.0f, -0.2f, 0.0f));
								
				if (m_pMonster->GetPos().y <= 0.6f) {
					m_pMonster->GetPos().y = 0.6f;
				}
			}
		}
	}

	if (OBJ_ID::OBJ_MONSTER1 == m_idObj)
		CObj::UpdateAABB(m_pMonster->Get_Matrix(), glm::vec3(4.0f, 4.0f, 4.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	else if (OBJ_ID::OBJ_MONSTER2 == m_idObj)
		CObj::UpdateAABB(m_pMonster->Get_Matrix(), glm::vec3(4000.0f, 4000.0f, 4000.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
}

GLvoid Monster::Release()
{
	SafeDelete(m_pMonster);
	return GLvoid();
}

Monster* Monster::Create(string strMesh, glm::vec3 vPos, glm::vec3 vScale)
{
	Monster* pInstance = new Monster;
	if (FAILED(pInstance->Initialize(strMesh, vPos, vScale)))
		SafeDelete(pInstance);
	return pInstance;
}
