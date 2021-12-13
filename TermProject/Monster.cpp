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
				if (!m_pGameMgr->MonCollide(RIGHT)) {
					m_pMonster->GetPos().x += 0.04;
				}
				m_iDir = 1;
			}
			else {
				m_pMonster->GetPos().x += 0.035;
				m_iDir = 1;
			}
		}
		else
		{
			if (m_iType == 0) {
				if (!m_pGameMgr->MonCollide(LEFT)) {
					m_pMonster->GetPos().x -= 0.04;
				}
				m_iDir = -1;
			}
			else {
				m_pMonster->GetPos().x -= 0.035;
				m_iDir = -1;
			}
		}
		if (vecPlayer3dPos.y - m_pMonster->GetPos().y >= 0) 
		{
			if (m_iType == 0) {
				if (!m_pGameMgr->MonCollide(UP)) {
					m_pMonster->GetPos().y += 0.04;
				}
			}
			else {
				m_pMonster->GetPos().y += 0.035;
			}
		}
		else 
		{
			if (m_iType == 0) {
				if (!m_pGameMgr->MonCollide(DOWN)) {
					m_pMonster->GetPos().y -= 0.04;
				}
			}
			else {
				m_pMonster->GetPos().y -= 0.035;
			}
		}
	}
	else if (m_pGameMgr->Get_View() && !m_pGameMgr->Get_Camera()->Get_Move())
	{
		m_pMonster->GetRotate().y = 0;
		m_pMonster->GetPos().x += 0.06 * m_iDir;

		if (m_pMonster->GetPos().x + 0.5 >= 13)
			m_iDir = -1;
		else if (m_pMonster->GetPos().x - 0.5 <= -14)
			m_iDir = 1;
		
		if (m_iType == 0) {
			if (!m_pGameMgr->MonCollide(DOWN)) {
				m_pMonster->GetPos().y -= 0.2f;

				if (m_pMonster->GetPos().y <= 0.0f) {
					m_pMonster->GetPos().y = 0.0f;
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
	m_pRender->Add_RenderObj(REDER_NONAL, this);
	return GLint();
}

GLvoid Monster::Render()
{
	m_pShaderLoader->Use_Shader("Default");
	m_pGameMgr->Render_Camera();
	m_pMonster->Render();
	return GLvoid();
}

float Monster::LookPlayerAngle()
{
	vecPlayer3dPos = dynamic_cast<Player3*>(m_pGameMgr->Get_Obj(OBJ_PLAYER2).front())->Get_pMesh()->GetPos();
	//fRatio = abs(vecPlayer3dPos.x - m_pMonster->GetPos().x) / abs(vecPlayer3dPos.z - m_pMonster->GetPos().z);
	//cout << fRatio << endl;
	double dAngle = atan((vecPlayer3dPos.x - m_pMonster->GetPos().x) / (vecPlayer3dPos.y - m_pMonster->GetPos().y)) * 180/ PI;
	//cout << dAngle << endl;
	if (m_pMonster->GetPos().y <= vecPlayer3dPos.y)
	{
		if (m_pMonster->GetPos().x <= vecPlayer3dPos.x) // 1
		{
			//cout << 180 - dAngle << endl;
			return 180 - dAngle;
		}
			
		else //   4
		{
			//cout << 180 - dAngle << endl;
			return 180 - dAngle;
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
			return 360 - dAngle;
		}
			
	}
}

Monster* Monster::Create(string strMesh, glm::vec3 vPos, glm::vec3 vScale, int iType)
{
	Monster* pInstance = new Monster;
	if (FAILED(pInstance->Initialize(strMesh, vPos, vScale, iType)))
		SafeDelete(pInstance);
	return pInstance;
}
