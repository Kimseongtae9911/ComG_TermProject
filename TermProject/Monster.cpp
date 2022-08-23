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

HRESULT Monster::Initialize(string strMesh, glm::vec3 vPos, glm::vec3 vScale, int iType)
{
	CObj::Initialize();
	m_pMonster = CMesh::Create(strMesh, { 1.0, 1.0, 1.0, m_fAlpha });
	m_pMonster->GetScale() = vScale;
	m_pMonster->GetPos() = vPos;
	m_iType = iType;
	//LookPlayerAngle();
	return NOERROR;
}

GLint Monster::Update(const GLfloat fTimeDelta)
{
	if (m_bDie) {
		m_pMonster->GetPos() = { -30, 0, 0 };
	}
	if (!bMovingRotate && m_pGameMgr->Get_View() == false)
	{
		++iRotateCount;
		m_pMonster->GetRotate().x += 90.f / 80.f;
		if (iRotateCount >= 80)
		{
			iRotateCount = 0;
			bMovingRotate = !bMovingRotate;
		}
	}
	else if (bMovingRotate && m_pGameMgr->Get_View())
	{
		++iRotateCount;
		m_pMonster->GetRotate().x -= 90.f / 80.f;
		if (iRotateCount >= 80)
		{
			iRotateCount = 0;
			bMovingRotate = !bMovingRotate;
		}
	}
	//LookPlayerAngle();

	if (!m_pGameMgr->Get_View() && m_pGameMgr->Get_Camera()->Get_Move())
	{
		float f = LookPlayerAngle();
		if (f >= m_pMonster->GetRotate().y)
		{
			if (f - m_pMonster->GetRotate().y <= m_pMonster->GetRotate().y + 360 - f /*&& f >= m_pMonster->GetRotate().y*/)
			{
				m_pMonster->GetRotate().y += 5.5;
			}
			else
			{
				m_pMonster->GetRotate().y -= 5.5;
			}
		}
		else
		{
			if (f + 360 - m_pMonster->GetRotate().y <= m_pMonster->GetRotate().y - f/* && f <= m_pMonster->GetRotate().y*/)
			{
				m_pMonster->GetRotate().y += 5.5;
			}
			else
			{
				m_pMonster->GetRotate().y -= 5.5;
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
		if (vecPlayer3dPos.x - m_pMonster->GetPos().x >= 0)
		{
			if (m_iType == 0) {
				if (!Collide(DIR::RIGHT)) {
					m_pMonster->GetPos().x += 0.03f;
				}
				m_iDir = 1;
			}
			else {
				m_pMonster->GetPos().x += 0.025f;
				m_iDir = 1;
			}
		}
		else
		{
			if (m_iType == 0) {
				if (!Collide(DIR::LEFT)) {
					m_pMonster->GetPos().x -= 0.03f;
				}
				m_iDir = -1;
			}
			else {
				m_pMonster->GetPos().x -= 0.025f;
				m_iDir = -1;
			}
		}
		if (vecPlayer3dPos.y - m_pMonster->GetPos().y >= 0) 
		{
			if (m_iType == 0) {
				if (!Collide(DIR::UP)) {
					m_pMonster->GetPos().y += 0.03f;
				}
			}
			else {
				m_pMonster->GetPos().y += 0.025f;
			}
		}
		else 
		{
			if (m_iType == 0) {
				if (!Collide(DIR::DOWN)) {
					m_pMonster->GetPos().y -= 0.03f;
				}
			}
			else {
				m_pMonster->GetPos().y -= 0.025f;
			}
		}
	}
	else if (m_pGameMgr->Get_View() && !m_pGameMgr->Get_Camera()->Get_Move())
	{
		m_pMonster->GetRotate().y = 0;
		m_pMonster->GetPos().x += 0.06f * m_iDir;

		if (m_pMonster->GetPos().x >= 13)
			m_iDir = -1;
		else if (m_pMonster->GetPos().x - 0.5 <= -14)
			m_iDir = 1;
		
		if (m_iType == 0) {
			if (!Collide(DIR::DOWN)) {
				m_pMonster->GetPos().y -= 0.2f;

				list<CObj*>::iterator iter_begin;
				list<CObj*>::iterator iter_end;
				BB monster_BB = Monster::Get_BB();

				iter_begin = m_pGameMgr->Get_Obj(OBJ_ID::OBJ_SPIKE).begin();
				iter_end = m_pGameMgr->Get_Obj(OBJ_ID::OBJ_SPIKE).end();
				for (; iter_begin != iter_end;)
				{
					BB OBJ_BB = (*iter_begin)->Get_BB();
					if (OBJ_BB.left > monster_BB.right || OBJ_BB.right < monster_BB.left || OBJ_BB.top < monster_BB.bottom || OBJ_BB.bottom > monster_BB.top);
					else {
						m_bDie = true;
					}
					++iter_begin;
				}
				if (m_pMonster->GetPos().y <= 0.6f) {
					m_pMonster->GetPos().y = 0.6f;
				}
			}
		}
	}
	if (m_pGameMgr->Get_View()) {
		Monster::Get_BB() = { m_pMonster->GetPos().x - 0.5f, m_pMonster->GetPos().x + 0.5f, m_pMonster->GetPos().y + 1.0f, m_pMonster->GetPos().y};
	}
	else {
		Monster::Get_BB() = { m_pMonster->GetPos().x - 0.5f, m_pMonster->GetPos().x + 0.5f, m_pMonster->GetPos().y + 0.5f, m_pMonster->GetPos().y - 0.5f };
	}

	CObj::UpdateAABB(m_pMonster->Get_Matrix());
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
	//fRatio = abs(vecPlayer3dPos.x - m_pMonster->GetPos().x) / abs(vecPlayer3dPos.z - m_pMonster->GetPos().z);
	//cout << fRatio << endl;
	float dAngle = atan((vecPlayer3dPos.x - m_pMonster->GetPos().x) / (vecPlayer3dPos.y - m_pMonster->GetPos().y)) * 180/ PI;
	//cout << dAngle << endl;
	if (m_pMonster->GetPos().y <= vecPlayer3dPos.y)
	{
		if (m_pMonster->GetPos().x <= vecPlayer3dPos.x) // 1
		{
			//cout << 180 - dAngle << endl;
			return 180.f - dAngle;
		}
			
		else //   4
		{
			//cout << 180 - dAngle << endl;
			return 180.f - dAngle;
		}
	}
	else
	{
		if (m_pMonster->GetPos().x <= vecPlayer3dPos.x) //2
		{
			//cout << -dAngle << endl;
			return -dAngle;
		}
			
		else // 3
		{
			//cout << 360 - dAngle << endl;
			return 360.f - dAngle;
		}
			
	}
}

bool Monster::Collide(DIR dir) {
	list<CObj*>::iterator iter_begin;
	list<CObj*>::iterator iter_end;

	BB monster_BB = Monster::Get_BB();
	for (int j = static_cast<int>(OBJ_ID::OBJ_MAP); j <= static_cast<int>(OBJ_ID::OBJ_BOX); ++j) {

		iter_begin = m_pGameMgr->Get_Obj(OBJ_ID(j)).begin();
		iter_end = m_pGameMgr->Get_Obj(OBJ_ID(j)).end();
		for (; iter_begin != iter_end;)
		{
			BB OBJ_BB = (*iter_begin)->Get_BB();
			switch (dir) {
			case DIR::LEFT:
				if (monster_BB.left <= OBJ_BB.right && monster_BB.right >= OBJ_BB.right)
				{
					if (OBJ_BB.bottom <= monster_BB.top && monster_BB.top <= OBJ_BB.top)
					{
						return true;
					}
					else if (OBJ_BB.bottom <= monster_BB.bottom && monster_BB.bottom <= OBJ_BB.top)
					{
						return true;
					}
					else if (monster_BB.bottom <= OBJ_BB.top && OBJ_BB.top <= monster_BB.top)
					{
						return true;
					}
					else if (monster_BB.bottom <= OBJ_BB.bottom && OBJ_BB.bottom <= monster_BB.top)
					{
						return true;
					}

				}
				break;
			case DIR::RIGHT:
				if (monster_BB.right >= OBJ_BB.left && monster_BB.left <= OBJ_BB.left)
				{
					if (OBJ_BB.bottom <= monster_BB.top && monster_BB.top <= OBJ_BB.top)
					{
						return true;
					}
					else if (OBJ_BB.bottom <= monster_BB.bottom && monster_BB.bottom <= OBJ_BB.top)
					{
						return true;
					}
					else if (monster_BB.bottom <= OBJ_BB.top && OBJ_BB.top <= monster_BB.top)
					{
						return true;
					}
					else if (monster_BB.bottom <= OBJ_BB.bottom && OBJ_BB.bottom <= monster_BB.top)
					{
						return true;
					}
				}
				break;
			case DIR::DOWN:
				if (OBJ_BB.top >= monster_BB.bottom && (OBJ_BB.bottom + OBJ_BB.top) / 2 <= monster_BB.bottom)
				{
					if (OBJ_BB.left <= monster_BB.left && monster_BB.left <= OBJ_BB.right)
					{
						return true;
					}
					else if (OBJ_BB.left <= monster_BB.right && monster_BB.right <= OBJ_BB.right)
					{
						return true;
					}
					else if (OBJ_BB.left >= monster_BB.left && monster_BB.right >= OBJ_BB.right)
					{
						return true;
					}
				}
				break;
			case DIR::UP:
				if (OBJ_BB.bottom <= monster_BB.top && (OBJ_BB.bottom + OBJ_BB.top) / 2 >= monster_BB.top)
				{
					if (OBJ_BB.left <= monster_BB.left && monster_BB.left <= OBJ_BB.right)
					{
						return true;
					}
					else if (OBJ_BB.left <= monster_BB.right && monster_BB.right <= OBJ_BB.right)
					{
						return true;
					}
					else if (OBJ_BB.left >= monster_BB.left && monster_BB.right >= OBJ_BB.right)
					{
						return true;
					}
				}
				break;
			default:
				break;
			}
			++iter_begin;
		}
	}

	return false;
}

GLvoid Monster::Release()
{
	SafeDelete(m_pMonster);
	return GLvoid();
}

Monster* Monster::Create(string strMesh, glm::vec3 vPos, glm::vec3 vScale, int iType)
{
	Monster* pInstance = new Monster;
	if (FAILED(pInstance->Initialize(strMesh, vPos, vScale, iType)))
		SafeDelete(pInstance);
	return pInstance;
}
