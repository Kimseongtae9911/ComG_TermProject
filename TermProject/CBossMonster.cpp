#include "stdafx.h"
#include "CBossMonster.h"
#include"CBullet.h"
#include "CMesh.h"
#include "Player3.h"
#include "Monster.h"
#include "CKeyManager.h"
#include "CRenderManager.h"
#include "CShader.h"
#include "CGameManager.h"
#include "CCamera.h"


CBossMonster::CBossMonster()
{
}

CBossMonster::~CBossMonster()
{
}

HRESULT CBossMonster::Initialize()
{
	CObj::Initialize();
	m_pBossMonster = CMesh::Create("../Resource/Monster/podoboo.obj", { 1.0, 1.0, 1.0, 0.8});
	m_pBossMonster->GetPos() = glm::vec3(5.0f, 0, 0);
	m_pBossMonster->GetScale() = glm::vec3(0.2f, 0.2f, 0.2f);
	m_pBossMonster->GetRotate().y = -20.f;
	return NOERROR;
}

GLint CBossMonster::Update(const GLfloat fTimeDelta)
{
	if (VIEW::VIEW_3D == m_pGameMgr->Get_View() && m_pGameMgr->Get_Camera()->Get_Move())
	{
		LookPlayer(fTimeDelta);

		//Create Flying Monster
		if (f3DTime >= 5.0f) {
			CObj* pObj = Monster::Create("../Resource/Monster/bee.obj", m_pBossMonster->GetPos() + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0002, 0.0002, 0.0002));
			pObj->Set_OBJID(OBJ_ID::OBJ_MONSTER2);
			if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MONSTER2, pObj)))
				return E_FAIL;
			f3DTime = 0;
		}
	}
	if (VIEW::VIEW_2D == m_pGameMgr->Get_View())
	{
		BossMove(fTimeDelta);

		//Create Bullet
		if (fTime >= 3.0f) {
			int Height = RandHeight();
			float fHeight = 0;
			switch (Height)
			{
			case 0:
				fHeight = 4.5f;
				break;
			case 1:
				fHeight = 8.f;
				break;
			case 2:
				fHeight = 11.f;
				break;
			default:
				break;
			}
			if (m_bBullet) {
				CObj* pObj = CBullet::Create(glm::vec3(m_pBossMonster->GetPos().x, fHeight, 0));
				if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_BULLET, pObj)))
					return E_FAIL;
			}
			fTime = 0;
		}
	}
	else
	{
		f3DTime += fTimeDelta;
	}
	if (!bMovingRotate && VIEW::VIEW_3D == m_pGameMgr->Get_View())
	{
		++iRotateCount;
		m_pBossMonster->GetRotate().x += 90.f / 80.f;
		if (iRotateCount >= 80)
		{
			iRotateCount = 0;
			bMovingRotate = !bMovingRotate;
			if(m_iLife > 0)
				m_pBossMonster->GetPos() = glm::vec3(5.0f, 4.0f, 0.0f);
		}
	}
	else if (bMovingRotate && VIEW::VIEW_2D == m_pGameMgr->Get_View())
	{
		++iRotateCount;
		m_pBossMonster->GetRotate().x -= 90.f / 80.f;
		if (iRotateCount >= 80)
		{
			iRotateCount = 0;
			bMovingRotate = !bMovingRotate;
			if (m_iLife > 0) {
				m_pBossMonster->GetRotate().y = -20.f;
				m_fRotate = 0.0f;
			}
		}
	}

	m_pRender->Add_RenderObj(RENDER_ID::RENDER_BOSS, this);

	CObj::UpdateAABB(m_pBossMonster->Get_Matrix(), glm::vec3(30.5f, 35.0f, 30.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 3.5f, 0.0f));
	return GLint();
}


GLvoid CBossMonster::BossMove(const GLfloat fTimeDelta)
{
	if (!bMoveUpDown && m_pBossMonster->GetPos().y >= 4.45f)
	{
		bMoveUpDown = !bMoveUpDown;
	}
	else if (bMoveUpDown && m_pBossMonster->GetPos().y <= 0.f)
	{
		bMoveUpDown = !bMoveUpDown;
	}
	if (!bMoveUpDown)
	{
		if (m_pBossMonster->GetPos().y + 8.5 + 0.05 <= 13.0f) {
			m_pBossMonster->GetPos().y += fTimeDelta * BOSS_SPEED;
		}
	}
	else
		m_pBossMonster->GetPos().y -= fTimeDelta * BOSS_SPEED;


	fTime += fTimeDelta;

	return GLvoid();
}

int CBossMonster::RandHeight()
{
	std::random_device rd;
	std::default_random_engine dre(rd());
	std::uniform_int_distribution<int> uid(0, 2);
	int iRand = uid(dre);
	return iRand;
}

GLvoid CBossMonster::LookPlayer(const GLfloat fTimeDelta)
{
	Player3* p = dynamic_cast<Player3*>(m_pGameMgr->Get_Obj(OBJ_ID::OBJ_PLAYER2).front());
	glm::vec3 bosspos = glm::vec3(5.0f, 7.5f, 0.0f);

	glm::vec3 look = glm::normalize(glm::vec3(glm::sin(ToRadian(m_fRotate)), -glm::cos(ToRadian(m_fRotate)), 0.0f));
	glm::vec3 up(0.0f, 0.0f, -1.0f);
	glm::vec3 dest = glm::normalize(glm::vec3(p->Get_pMesh()->GetPos().x - bosspos.x, p->Get_pMesh()->GetPos().y - bosspos.y, 0.0f));

	float angle = glm::dot(up, glm::cross(look, dest));
	
	if (IsEqual(look.x, dest.x) && IsEqual(look.y, dest.y))
		return;

	if (angle > 0.f) {
		m_fRotate -= fTimeDelta * SPIN_SPEED;
		m_pBossMonster->GetRotate().y = m_fRotate;

		if (m_fRotate < 0)
			m_fRotate += 360.0f;
	}
	else {
		m_fRotate += fTimeDelta * SPIN_SPEED;
		m_pBossMonster->GetRotate().y = m_fRotate;
		if (m_fRotate >= 360.0f)
			m_fRotate -= 360.0f;
	}

	return GLvoid();
}

GLvoid CBossMonster::Render()
{
	m_pShaderLoader->Use_Shader("Default");
	m_pGameMgr->Render_Camera();
	m_pBossMonster->Render();
	CObj::Render();

	return GLvoid();
}


CBossMonster* CBossMonster::Create()
{
	CBossMonster* pInstance = new CBossMonster;
	if (FAILED(pInstance->Initialize()))
		SafeDelete(pInstance);
	return pInstance;
}
