#include"stdafx.h"
#include "CGameManager.h"
#include "CKeyManager.h"
#include "CMesh.h"
#include "CObj.h"
#include "CObject.h"
#include "CCamera.h"
#include "CKeyManager.h"
#include "Monster.h"
#include "Player2.h"
#include "Player3.h"
#include "CPortal.h"
#include "CRenderManager.h"
#include "CSoundManager.h"

IMPLEMENT_SINGLETON(CGameManager)

CGameManager::CGameManager()
{
}

CGameManager::~CGameManager()
{
}

HRESULT CGameManager::Add_GameObj(OBJ_ID eID, CObj* pObj)
{
	if (!pObj)
		return E_FAIL;

	m_ObjLst[static_cast<int>(eID)].emplace_back(pObj);

	return NOERROR;
}

GLvoid CGameManager::Update(const GLfloat fTimeDelta)
{
	for (int i = 0; i < static_cast<int>(OBJ_ID::OBJ_END); ++i)
	{
		for (auto iter_begin = m_ObjLst[i].begin(); iter_begin != m_ObjLst[i].end();)
		{
			if (static_cast<int>(OBJ_ID::OBJ_END) == (*iter_begin)->Update(fTimeDelta))
			{
				SafeDelete(*iter_begin);
				iter_begin = m_ObjLst[i].erase(iter_begin);
			}
			else
				++iter_begin;
		}
	}

	// 2D, 3D View Change
	CheckViewChange();
	ChangeView();

	CheckCollide();	// Collide Check
	//PortalInteract(); // Portal

	if (m_pCamera)
		m_pCamera->Update(fTimeDelta);

	return GLvoid();
}

bool CGameManager::Collide(DIR dir)
{
	if (VIEW::VIEW_2D == m_View) {
		CObj* player = m_ObjLst[static_cast<int>(OBJ_ID::OBJ_PLAYER1)].front();
		BB player_BB = player->Get_BB();
		switch (dir) {
		case DIR::LEFT:
			for (int i = static_cast<int>(OBJ_ID::OBJ_MONSTER1); i <= static_cast<int>(OBJ_ID::OBJ_KEY); ++i)
			{
				list<CObj*>::iterator iter_begin = m_ObjLst[i].begin();
				list<CObj*>::iterator iter_end = m_ObjLst[i].end();
				for (; iter_begin != iter_end;)
				{
					BB OBJ_BB = (*iter_begin)->Get_BB();
					if (OBJ_BB.right >= player_BB.left && (OBJ_BB.left + OBJ_BB.right) / 2 <= player_BB.left)
					{
						if (OBJ_BB.bottom <= player_BB.top && player_BB.top <= OBJ_BB.top)
						{
							if (i == static_cast<int>(OBJ_ID::OBJ_PORTAL)) {
								return false;
							}
							if (i == static_cast<int>(OBJ_ID::OBJ_BULLET)) {
								dynamic_cast<Player2*>(player)->Get_Die() = true;
							}
							return true;
						}
						else if (OBJ_BB.bottom < player_BB.bottom && player_BB.bottom < OBJ_BB.top)
						{
							if (i == static_cast<int>(OBJ_ID::OBJ_PORTAL)) {
								return false;
							}
							if (i == static_cast<int>(OBJ_ID::OBJ_BULLET)) {
								dynamic_cast<Player2*>(player)->Get_Die() = true;
							}
							return true;
						}
						else if (player_BB.bottom < OBJ_BB.top && OBJ_BB.top <= player_BB.top)
						{
							if (i == static_cast<int>(OBJ_ID::OBJ_PORTAL)) {
								return false;
							}
							if (i == static_cast<int>(OBJ_ID::OBJ_BULLET)) {
								dynamic_cast<Player2*>(player)->Get_Die() = true;
							}
							return true;
						}
						else if (player_BB.bottom < OBJ_BB.bottom && OBJ_BB.bottom <= player_BB.top)
						{
							if (i == static_cast<int>(OBJ_ID::OBJ_PORTAL)) {
								return false;
							}
							if (i == static_cast<int>(OBJ_ID::OBJ_BULLET)) {
								dynamic_cast<Player2*>(player)->Get_Die() = true;
							}
							return true;
						}
					}
					++iter_begin;
				}
			}
			break;
		case DIR::RIGHT:
			for (int i = static_cast<int>(OBJ_ID::OBJ_MONSTER1); i <= static_cast<int>(OBJ_ID::OBJ_KEY); ++i)
			{
				list<CObj*>::iterator iter_begin = m_ObjLst[i].begin();
				list<CObj*>::iterator iter_end = m_ObjLst[i].end();
				for (; iter_begin != iter_end;)
				{
					BB OBJ_BB = (*iter_begin)->Get_BB();
					if (player_BB.right >= OBJ_BB.left && player_BB.left <= OBJ_BB.left)
					{
						if (OBJ_BB.bottom <= player_BB.top && player_BB.top <= OBJ_BB.top)
						{
							if (i == static_cast<int>(OBJ_ID::OBJ_PORTAL)) {
								return false;
							}
							if (i == static_cast<int>(OBJ_ID::OBJ_BULLET)) {
								dynamic_cast<Player2*>(player)->Get_Die() = true;
							}
							return true;
						}
						else if (OBJ_BB.bottom < player_BB.bottom && player_BB.bottom < OBJ_BB.top)
						{
							if (i == static_cast<int>(OBJ_ID::OBJ_PORTAL)) {
								return false;
							}
							if (i == static_cast<int>(OBJ_ID::OBJ_BULLET)) {
								dynamic_cast<Player2*>(player)->Get_Die() = true;
							}
							return true;
						}
						else if (player_BB.bottom < OBJ_BB.top && OBJ_BB.top <= player_BB.top)
						{
							if (i == static_cast<int>(OBJ_ID::OBJ_PORTAL)) {
								return false;
							}
							if (i == static_cast<int>(OBJ_ID::OBJ_BULLET)) {
								dynamic_cast<Player2*>(player)->Get_Die() = true;
							}
							return true;
						}
						else if (player_BB.bottom < OBJ_BB.bottom && OBJ_BB.bottom <= player_BB.top)
						{
							if (i == static_cast<int>(OBJ_ID::OBJ_PORTAL)) {
								return false;
							}
							if (i == static_cast<int>(OBJ_ID::OBJ_BULLET)) {
								dynamic_cast<Player2*>(player)->Get_Die() = true;
							}
							return true;
						}
					}
					++iter_begin;
				}
			}
			break;
		default:
			break;
		}
	}
	else {
		CObj* player = m_ObjLst[static_cast<int>(OBJ_ID::OBJ_PLAYER2)].front();
		BB player_BB = player->Get_BB();
		switch (dir) {
		case DIR::LEFT:
			for (int i = static_cast<int>(OBJ_ID::OBJ_MONSTER1); i < static_cast<int>(OBJ_ID::OBJ_KEY); ++i)
			{
				list<CObj*>::iterator iter_begin = m_ObjLst[i].begin();
				list<CObj*>::iterator iter_end = m_ObjLst[i].end();
				for (; iter_begin != iter_end;)
				{
					BB OBJ_BB = (*iter_begin)->Get_BB();
					if (OBJ_BB.right >= player_BB.left && (OBJ_BB.left + OBJ_BB.right) / 2 <= player_BB.left)
					{
						if (OBJ_BB.bottom <= player_BB.top && player_BB.top <= OBJ_BB.top)
						{
							if (i == static_cast<int>(OBJ_ID::OBJ_PORTAL)) {
								dynamic_cast<Player3*>(player)->Get_CollideB() = false;
								return false;
							}
							if (i == static_cast<int>(OBJ_ID::OBJ_BOX)) {
								dynamic_cast<Player3*>(player)->Get_CollideB() = true;
								if (!dynamic_cast<Player3*>(player)->Get_HoldingB()) {
									if (CKeyManager::GetInstance()->KeyDown(KEY_A)) {
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().x = dynamic_cast<Player3*>(player)->Get_pMesh()->GetPos().x;
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().y = dynamic_cast<Player3*>(player)->Get_pMesh()->GetPos().y;
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().z = 1.5f;
										glm::vec3 temp = dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos();
										(*iter_begin)->Get_BB() = { temp.x - 0.5f, temp.x + 0.5f, temp.y + 0.5f, temp.y - 0.5f };
										dynamic_cast<Player3*>(player)->Get_HoldingB() = true;
									}
									else {
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().x -= 0.15f;
										glm::vec3 temp = dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos();
										(*iter_begin)->Get_BB() = { temp.x - 0.5f, temp.x + 0.5f, temp.y + 0.5f, temp.y - 0.5f };
									}
								}
								return false;
							}
 							dynamic_cast<Player3*>(player)->Get_CollideB() = false;
							return true;
						}
						else if (OBJ_BB.bottom < player_BB.bottom && player_BB.bottom < OBJ_BB.top)
						{
							if (i == static_cast<int>(OBJ_ID::OBJ_PORTAL)) {
								dynamic_cast<Player3*>(player)->Get_CollideB() = false;
								return false;
							}
							if (i == static_cast<int>(OBJ_ID::OBJ_BOX)) {
								dynamic_cast<Player3*>(player)->Get_CollideB() = true;
								if (!dynamic_cast<Player3*>(player)->Get_HoldingB()) {
									if (CKeyManager::GetInstance()->KeyDown(KEY_A)) {
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().x = dynamic_cast<Player3*>(player)->Get_pMesh()->GetPos().x;
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().y = dynamic_cast<Player3*>(player)->Get_pMesh()->GetPos().y;
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().z = 1.5f;
										glm::vec3 temp = dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos();
										(*iter_begin)->Get_BB() = { temp.x - 0.5f, temp.x + 0.5f, temp.y + 0.5f, temp.y - 0.5f };
										dynamic_cast<Player3*>(player)->Get_HoldingB() = true;
									}
									else {
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().x -= 0.15f;
										glm::vec3 temp = dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos();
										(*iter_begin)->Get_BB() = { temp.x - 0.5f, temp.x + 0.5f, temp.y + 0.5f, temp.y - 0.5f };
									}
								}
								return false;
							}
							dynamic_cast<Player3*>(player)->Get_CollideB() = false;
							return true;
						}
						else if (player_BB.bottom < OBJ_BB.top && OBJ_BB.top <= player_BB.top)
						{
							if (i == static_cast<int>(OBJ_ID::OBJ_PORTAL)) {
								dynamic_cast<Player3*>(player)->Get_CollideB() = false;
								return false;
							}
							if (i == static_cast<int>(OBJ_ID::OBJ_BOX)) {
								dynamic_cast<Player3*>(player)->Get_CollideB() = true;
								if (!dynamic_cast<Player3*>(player)->Get_HoldingB()) {
									if (CKeyManager::GetInstance()->KeyDown(KEY_A)) {
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().x = dynamic_cast<Player3*>(player)->Get_pMesh()->GetPos().x;
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().y = dynamic_cast<Player3*>(player)->Get_pMesh()->GetPos().y;
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().z = 1.5f;
										glm::vec3 temp = dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos();
										(*iter_begin)->Get_BB() = { temp.x - 0.5f, temp.x + 0.5f, temp.y + 0.5f, temp.y - 0.5f };
										dynamic_cast<Player3*>(player)->Get_HoldingB() = true;
									}
									else {
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().x -= 0.15f;
										glm::vec3 temp = dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos();
										(*iter_begin)->Get_BB() = { temp.x - 0.5f, temp.x + 0.5f, temp.y + 0.5f, temp.y - 0.5f };
									}
								}
								return false;
							}
							dynamic_cast<Player3*>(player)->Get_CollideB() = false;
							return true;
						}
						else if (player_BB.bottom < OBJ_BB.bottom && OBJ_BB.bottom <= player_BB.top)
						{
							if (i == static_cast<int>(OBJ_ID::OBJ_PORTAL)) {
								dynamic_cast<Player3*>(player)->Get_CollideB() = false;
								return false;
							}
							if (i == static_cast<int>(OBJ_ID::OBJ_BOX)) {
								dynamic_cast<Player3*>(player)->Get_CollideB() = true;
								if (!dynamic_cast<Player3*>(player)->Get_HoldingB()) {
									if (CKeyManager::GetInstance()->KeyDown(KEY_A)) {
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().x = dynamic_cast<Player3*>(player)->Get_pMesh()->GetPos().x;
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().y = dynamic_cast<Player3*>(player)->Get_pMesh()->GetPos().y;
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().z = 1.5f;
										glm::vec3 temp = dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos();
										(*iter_begin)->Get_BB() = { temp.x - 0.5f, temp.x + 0.5f, temp.y + 0.5f, temp.y - 0.5f };
										dynamic_cast<Player3*>(player)->Get_HoldingB() = true;
									}
									else {
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().x -= 0.15f;
										glm::vec3 temp = dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos();
										(*iter_begin)->Get_BB() = { temp.x - 0.5f, temp.x + 0.5f, temp.y + 0.5f, temp.y - 0.5f };
									}
								}
								return false;
							}
							dynamic_cast<Player3*>(player)->Get_CollideB() = false;
							return true;
						}
					}
					++iter_begin;
				}
			}
			break;
		case DIR::RIGHT:
			for (int i = static_cast<int>(OBJ_ID::OBJ_MONSTER1); i < static_cast<int>(OBJ_ID::OBJ_KEY); ++i)
			{
				list<CObj*>::iterator iter_begin = m_ObjLst[i].begin();
				list<CObj*>::iterator iter_end = m_ObjLst[i].end();
				for (; iter_begin != iter_end;)
				{
					BB OBJ_BB = (*iter_begin)->Get_BB();
					if (OBJ_BB.left <= player_BB.right && (OBJ_BB.left + OBJ_BB.right) / 2 >= player_BB.right)
					{
						if (OBJ_BB.bottom <= player_BB.top && player_BB.top <= OBJ_BB.top)
						{
							if (i == static_cast<int>(OBJ_ID::OBJ_PORTAL)) {
								dynamic_cast<Player3*>(player)->Get_CollideB() = false;
								return false;
							}
							if (i == static_cast<int>(OBJ_ID::OBJ_BOX)) {
								dynamic_cast<Player3*>(player)->Get_CollideB() = true;
								if (!dynamic_cast<Player3*>(player)->Get_HoldingB()) {
									if (CKeyManager::GetInstance()->KeyDown(KEY_A)) {
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().x = dynamic_cast<Player3*>(player)->Get_pMesh()->GetPos().x;
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().y = dynamic_cast<Player3*>(player)->Get_pMesh()->GetPos().y;
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().z = 1.5f;
										glm::vec3 temp = dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos();
										(*iter_begin)->Get_BB() = { temp.x - 0.5f, temp.x + 0.5f, temp.y + 0.5f, temp.y - 0.5f };
										dynamic_cast<Player3*>(player)->Get_HoldingB() = true;
									}
									else {
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().x += 0.15f;
										glm::vec3 temp = dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos();
										(*iter_begin)->Get_BB() = { temp.x - 0.5f, temp.x + 0.5f, temp.y + 0.5f, temp.y - 0.5f };
									}
								}
								return false;
							}
							return true;
						}
						else if (OBJ_BB.bottom <= player_BB.bottom && player_BB.bottom <= OBJ_BB.top)
						{
							if (i == static_cast<int>(OBJ_ID::OBJ_PORTAL)) {
								dynamic_cast<Player3*>(player)->Get_CollideB() = false;
								return false;
							}
							if (i == static_cast<int>(OBJ_ID::OBJ_BOX)) {
								dynamic_cast<Player3*>(player)->Get_CollideB() = true;
								if (!dynamic_cast<Player3*>(player)->Get_HoldingB()) {
									if (CKeyManager::GetInstance()->KeyDown(KEY_A)) {
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().x = dynamic_cast<Player3*>(player)->Get_pMesh()->GetPos().x;
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().y = dynamic_cast<Player3*>(player)->Get_pMesh()->GetPos().y;
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().z = 1.5f;
										glm::vec3 temp = dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos();
										(*iter_begin)->Get_BB() = { temp.x - 0.5f, temp.x + 0.5f, temp.y + 0.5f, temp.y - 0.5f };
										dynamic_cast<Player3*>(player)->Get_HoldingB() = true;
									}
									else {
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().x += 0.15f;
										glm::vec3 temp = dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos();
										(*iter_begin)->Get_BB() = { temp.x - 0.5f, temp.x + 0.5f, temp.y + 0.5f, temp.y - 0.5f };
									}
								}
								return false;
							}
							return true;
						}
						else if (player_BB.bottom <= OBJ_BB.top && OBJ_BB.top <= player_BB.top)
						{
							if (i == static_cast<int>(OBJ_ID::OBJ_PORTAL)) {
								dynamic_cast<Player3*>(player)->Get_CollideB() = false;
								return false;
							}
							if (i == static_cast<int>(OBJ_ID::OBJ_BOX)) {
								dynamic_cast<Player3*>(player)->Get_CollideB() = true;
								if (!dynamic_cast<Player3*>(player)->Get_HoldingB()) {
									if (CKeyManager::GetInstance()->KeyDown(KEY_A)) {
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().x = dynamic_cast<Player3*>(player)->Get_pMesh()->GetPos().x;
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().y = dynamic_cast<Player3*>(player)->Get_pMesh()->GetPos().y;
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().z = 1.5f;
										glm::vec3 temp = dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos();
										(*iter_begin)->Get_BB() = { temp.x - 0.5f, temp.x + 0.5f, temp.y + 0.5f, temp.y - 0.5f };
										dynamic_cast<Player3*>(player)->Get_HoldingB() = true;
									}
									else {
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().x += 0.15f;
										glm::vec3 temp = dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos();
										(*iter_begin)->Get_BB() = { temp.x - 0.5f, temp.x + 0.5f, temp.y + 0.5f, temp.y - 0.5f };
									}
								}
								return false;
							}
							return true;
						}
						else if (player_BB.bottom <= OBJ_BB.bottom && OBJ_BB.bottom <= player_BB.top)
						{
							if (i == static_cast<int>(OBJ_ID::OBJ_PORTAL)) {
								dynamic_cast<Player3*>(player)->Get_CollideB() = false;
								return false;
							}
							if (i == static_cast<int>(OBJ_ID::OBJ_BOX)) {
								dynamic_cast<Player3*>(player)->Get_CollideB() = true;
								if (!dynamic_cast<Player3*>(player)->Get_HoldingB()) {
									if (CKeyManager::GetInstance()->KeyDown(KEY_A)) {
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().x = dynamic_cast<Player3*>(player)->Get_pMesh()->GetPos().x;
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().y = dynamic_cast<Player3*>(player)->Get_pMesh()->GetPos().y;
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().z = 1.5f;
										glm::vec3 temp = dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos();
										(*iter_begin)->Get_BB() = { temp.x - 0.5f, temp.x + 0.5f, temp.y + 0.5f, temp.y - 0.5f };
										dynamic_cast<Player3*>(player)->Get_HoldingB() = true;
									}
									else {
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().x += 0.15f;
										glm::vec3 temp = dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos();
										(*iter_begin)->Get_BB() = { temp.x - 0.5f, temp.x + 0.5f, temp.y + 0.5f, temp.y - 0.5f };
									}
								}
								return false;
							}
							return true;
						}
					}
					++iter_begin;
				}
			}
			break;
		case DIR::UP:
			for (int i = static_cast<int>(OBJ_ID::OBJ_MONSTER1); i < static_cast<int>(OBJ_ID::OBJ_KEY); ++i)
			{
				list<CObj*>::iterator iter_begin = m_ObjLst[i].begin();
				list<CObj*>::iterator iter_end = m_ObjLst[i].end();
				for (; iter_begin != iter_end;)
				{
					BB OBJ_BB = (*iter_begin)->Get_BB();
					if (OBJ_BB.bottom <= player_BB.top && (OBJ_BB.bottom + OBJ_BB.top) / 2 >= player_BB.top)
					{
						if (OBJ_BB.left <= player_BB.left && player_BB.left <= OBJ_BB.right)
						{
							if (i == static_cast<int>(OBJ_ID::OBJ_PORTAL)) {
								dynamic_cast<Player3*>(player)->Get_CollideB() = false;
								return false;
							}
							if (i == static_cast<int>(OBJ_ID::OBJ_BOX)) {
								dynamic_cast<Player3*>(player)->Get_CollideB() = true;
								if (!dynamic_cast<Player3*>(player)->Get_HoldingB()) {
									if (CKeyManager::GetInstance()->KeyDown(KEY_A)) {
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().x = dynamic_cast<Player3*>(player)->Get_pMesh()->GetPos().x;
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().y = dynamic_cast<Player3*>(player)->Get_pMesh()->GetPos().y;
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().z = 1.5f;
										glm::vec3 temp = dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos();
										(*iter_begin)->Get_BB() = { temp.x - 0.5f, temp.x + 0.5f, temp.y + 0.5f, temp.y - 0.5f };
										dynamic_cast<Player3*>(player)->Get_HoldingB() = true;
									}
									else {
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().y += 0.15f;
										glm::vec3 temp = dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos();
										(*iter_begin)->Get_BB() = { temp.x - 0.5f, temp.x + 0.5f, temp.y + 0.5f, temp.y - 0.5f };
									}
								}
								return false;
							}
							return true;
						}
						else if (OBJ_BB.left <= player_BB.right && player_BB.right <= OBJ_BB.right)
						{
							if (i == static_cast<int>(OBJ_ID::OBJ_PORTAL)) {
								dynamic_cast<Player3*>(player)->Get_CollideB() = false;
								return false;
							}
							if (i == static_cast<int>(OBJ_ID::OBJ_BOX)) {
								dynamic_cast<Player3*>(player)->Get_CollideB() = true;
								if (!dynamic_cast<Player3*>(player)->Get_HoldingB()) {
									if (CKeyManager::GetInstance()->KeyDown(KEY_A)) {
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().x = dynamic_cast<Player3*>(player)->Get_pMesh()->GetPos().x;
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().y = dynamic_cast<Player3*>(player)->Get_pMesh()->GetPos().y;
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().z = 1.5f;
										glm::vec3 temp = dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos();
										(*iter_begin)->Get_BB() = { temp.x - 0.5f, temp.x + 0.5f, temp.y + 0.5f, temp.y - 0.5f };
										dynamic_cast<Player3*>(player)->Get_HoldingB() = true;
									}
									else {
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().y += 0.15f;
										glm::vec3 temp = dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos();
										(*iter_begin)->Get_BB() = { temp.x - 0.5f, temp.x + 0.5f, temp.y + 0.5f, temp.y - 0.5f };
									}
								}
								return false;
							}
							return true;
						}
						else if (OBJ_BB.left >= player_BB.left && player_BB.right >= OBJ_BB.right)
						{
							if (i == static_cast<int>(OBJ_ID::OBJ_PORTAL)) {
								dynamic_cast<Player3*>(player)->Get_CollideB() = false;
								return false;
							}
							if (i == static_cast<int>(OBJ_ID::OBJ_BOX)) {
								dynamic_cast<Player3*>(player)->Get_CollideB() = true;
								if (!dynamic_cast<Player3*>(player)->Get_HoldingB()) {
									if (CKeyManager::GetInstance()->KeyDown(KEY_A)) {
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().x = dynamic_cast<Player3*>(player)->Get_pMesh()->GetPos().x;
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().y = dynamic_cast<Player3*>(player)->Get_pMesh()->GetPos().y;
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().z = 1.5f;
										glm::vec3 temp = dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos();
										(*iter_begin)->Get_BB() = { temp.x - 0.5f, temp.x + 0.5f, temp.y + 0.5f, temp.y - 0.5f };
										dynamic_cast<Player3*>(player)->Get_HoldingB() = true;
									}
									else {
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().y += 0.15f;
										glm::vec3 temp = dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos();
										(*iter_begin)->Get_BB() = { temp.x - 0.5f, temp.x + 0.5f, temp.y + 0.5f, temp.y - 0.5f };
									}
								}
								return false;
							}
							return true;
						}
					}
					++iter_begin;
				}
			}
			break;
		case DIR::DOWN:
			for (int i = static_cast<int>(OBJ_ID::OBJ_MONSTER1); i < static_cast<int>(OBJ_ID::OBJ_KEY); ++i)
			{
				list<CObj*>::iterator iter_begin = m_ObjLst[i].begin();
				list<CObj*>::iterator iter_end = m_ObjLst[i].end();
				for (; iter_begin != iter_end;)
				{
					BB OBJ_BB = (*iter_begin)->Get_BB();
					if (OBJ_BB.top >= player_BB.bottom && (OBJ_BB.bottom + OBJ_BB.top) / 2 <= player_BB.bottom)
					{
						if (OBJ_BB.left <= player_BB.left && player_BB.left <= OBJ_BB.right)
						{
							if (i == static_cast<int>(OBJ_ID::OBJ_PORTAL)) {
								dynamic_cast<Player3*>(player)->Get_CollideB() = false;
								return false;
							}
							if (i == static_cast<int>(OBJ_ID::OBJ_BOX)) {
								dynamic_cast<Player3*>(player)->Get_CollideB() = true;
								if (!dynamic_cast<Player3*>(player)->Get_HoldingB()) {
									if (CKeyManager::GetInstance()->KeyDown(KEY_A)) {
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().x = dynamic_cast<Player3*>(player)->Get_pMesh()->GetPos().x;
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().y = dynamic_cast<Player3*>(player)->Get_pMesh()->GetPos().y;
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().z = 1.5f;
										glm::vec3 temp = dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos();
										(*iter_begin)->Get_BB() = { temp.x - 0.5f, temp.x + 0.5f, temp.y + 0.5f, temp.y - 0.5f };
										dynamic_cast<Player3*>(player)->Get_HoldingB() = true;
									}
									else {
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().y -= 0.15f;
										glm::vec3 temp = dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos();
										(*iter_begin)->Get_BB() = { temp.x - 0.5f, temp.x + 0.5f, temp.y + 0.5f, temp.y - 0.5f };
									}
								}
								return false;
							}
							return true;
						}
						else if (OBJ_BB.left <= player_BB.right && player_BB.right <= OBJ_BB.right)
						{
							if (i == static_cast<int>(OBJ_ID::OBJ_PORTAL)) {
								dynamic_cast<Player3*>(player)->Get_CollideB() = false;
								return false;
							}
							if (i == static_cast<int>(OBJ_ID::OBJ_BOX)) {
								dynamic_cast<Player3*>(player)->Get_CollideB() = true;
								if (!dynamic_cast<Player3*>(player)->Get_HoldingB()) {
									if (CKeyManager::GetInstance()->KeyDown(KEY_A)) {
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().x = dynamic_cast<Player3*>(player)->Get_pMesh()->GetPos().x;
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().y = dynamic_cast<Player3*>(player)->Get_pMesh()->GetPos().y;
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().z = 1.5f;
										glm::vec3 temp = dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos();
										(*iter_begin)->Get_BB() = { temp.x - 0.5f, temp.x + 0.5f, temp.y + 0.5f, temp.y - 0.5f };
										dynamic_cast<Player3*>(player)->Get_HoldingB() = true;
									}
									else {
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().y -= 0.15f;
										glm::vec3 temp = dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos();
										(*iter_begin)->Get_BB() = { temp.x - 0.5f, temp.x + 0.5f, temp.y + 0.5f, temp.y - 0.5f };
									}
								}
								return false;
							}
							return true;
						}
						else if (OBJ_BB.left >= player_BB.left && player_BB.right >= OBJ_BB.right)
						{
							if (i == static_cast<int>(OBJ_ID::OBJ_PORTAL)) {
								dynamic_cast<Player3*>(player)->Get_CollideB() = false;
								return false;
							}
							if (i == static_cast<int>(OBJ_ID::OBJ_BOX)) {
								dynamic_cast<Player3*>(player)->Get_CollideB() = true;
								if (!dynamic_cast<Player3*>(player)->Get_HoldingB()) {
									if (CKeyManager::GetInstance()->KeyDown(KEY_A)) {
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().x = dynamic_cast<Player3*>(player)->Get_pMesh()->GetPos().x;
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().y = dynamic_cast<Player3*>(player)->Get_pMesh()->GetPos().y;
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().z = 1.5f;
										glm::vec3 temp = dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos();
										(*iter_begin)->Get_BB() = { temp.x - 0.5f, temp.x + 0.5f, temp.y + 0.5f, temp.y - 0.5f };
										dynamic_cast<Player3*>(player)->Get_HoldingB() = true;
									}
									else {
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().y -= 0.15f;
										glm::vec3 temp = dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos();
										(*iter_begin)->Get_BB() = { temp.x - 0.5f, temp.x + 0.5f, temp.y + 0.5f, temp.y - 0.5f };
									}
								}
								return false;
							}
							return true;
						}
					}
					++iter_begin;
				}
			}
			break;
		}
	}
	return false;
}

bool CGameManager::JumpCollide(int num) {
	CObj* player = m_ObjLst[static_cast<int>(OBJ_ID::OBJ_PLAYER1)].front();
	BB player_BB = player->Get_BB();
	if (dynamic_cast<Player2*>(player)->GetJump()) {
		switch (num) {
		case 1:
			for (int i = static_cast<int>(OBJ_ID::OBJ_MONSTER1); i < static_cast<int>(OBJ_ID::OBJ_SPIKE); ++i)
			{
				list<CObj*>::iterator iter_begin = m_ObjLst[i].begin();
				list<CObj*>::iterator iter_end = m_ObjLst[i].end();
				for (; iter_begin != iter_end;)
				{
					BB OBJ_BB = (*iter_begin)->Get_BB();
					if (OBJ_BB.bottom <= player_BB.top && (OBJ_BB.bottom + OBJ_BB.top) / 2 >= player_BB.top)
					{
						if (OBJ_BB.left <= player_BB.left && player_BB.left <= OBJ_BB.right)
						{
							if (i == static_cast<int>(OBJ_ID::OBJ_PORTAL)) {
								return false;
							}
							if (i == static_cast<int>(OBJ_ID::OBJ_BULLET)) {
								dynamic_cast<Player2*>(player)->Get_Die() = true;
							}
							return true;
						}
						else if (OBJ_BB.left <= player_BB.right && player_BB.right <= OBJ_BB.right)
						{
							if (i == static_cast<int>(OBJ_ID::OBJ_PORTAL)) {
								return false;
							}
							if (i == static_cast<int>(OBJ_ID::OBJ_BULLET)) {
								dynamic_cast<Player2*>(player)->Get_Die() = true;
							}
							return true;
						}
						else if (OBJ_BB.left >= player_BB.left && player_BB.right >= OBJ_BB.right)
						{
							if (i == static_cast<int>(OBJ_ID::OBJ_PORTAL)) {
								return false;
							}
							if (i == static_cast<int>(OBJ_ID::OBJ_BULLET)) {
								dynamic_cast<Player2*>(player)->Get_Die() = true;
							}
							return true;
						}
					}
					iter_begin++;
				}
			}
			break;
		case -1:
			for (int i = static_cast<int>(OBJ_ID::OBJ_MONSTER1); i < static_cast<int>(OBJ_ID::OBJ_SPIKE); ++i)
			{
				list<CObj*>::iterator iter_begin = m_ObjLst[i].begin();
				list<CObj*>::iterator iter_end = m_ObjLst[i].end();
				for (; iter_begin != iter_end;)
				{
					BB OBJ_BB = (*iter_begin)->Get_BB();
					if (OBJ_BB.top >= player_BB.bottom && (OBJ_BB.bottom + OBJ_BB.top) / 2 <= player_BB.bottom)
					{
						if (OBJ_BB.left <= player_BB.left && player_BB.left <= OBJ_BB.right)
						{
							if (i == static_cast<int>(OBJ_ID::OBJ_PORTAL)) {
								return false;
							}
							if (i == static_cast<int>(OBJ_ID::OBJ_BULLET)) {
								dynamic_cast<Player2*>(player)->Get_Die() = true;
							}
							float dis = OBJ_BB.top - player_BB.bottom;
							dynamic_cast<Player2*>(player)->GetP()->GetPos().y += dis;

							return true;
						}
						else if (OBJ_BB.left <= player_BB.right && player_BB.right <= OBJ_BB.right)
						{
							if (i == static_cast<int>(OBJ_ID::OBJ_PORTAL)) {
								return false;
							}
							if (i == static_cast<int>(OBJ_ID::OBJ_BULLET)) {
								dynamic_cast<Player2*>(player)->Get_Die() = true;
							}
							float dis = OBJ_BB.top - player_BB.bottom;
							dynamic_cast<Player2*>(player)->GetP()->GetPos().y += dis;
							return true;
						}
						else if (OBJ_BB.left >= player_BB.left && player_BB.right >= OBJ_BB.right)
						{
							if (i == static_cast<int>(OBJ_ID::OBJ_PORTAL)) {
								return false;
							}
							if (i == static_cast<int>(OBJ_ID::OBJ_BULLET)) {
								dynamic_cast<Player2*>(player)->Get_Die() = true;
							}
							float dis = OBJ_BB.top - player_BB.bottom;
							dynamic_cast<Player2*>(player)->GetP()->GetPos().y += dis;
							return true;
						}
					}
					iter_begin++;
				}
			}
			break;
		}
	}
	else {
		for (int i = static_cast<int>(OBJ_ID::OBJ_MONSTER1); i < static_cast<int>(OBJ_ID::OBJ_SPIKE); ++i)
		{
			list<CObj*>::iterator iter_begin = m_ObjLst[i].begin();
			list<CObj*>::iterator iter_end = m_ObjLst[i].end();
			for (; iter_begin != iter_end;)
			{
				BB OBJ_BB = (*iter_begin)->Get_BB();
				if (OBJ_BB.top >= player_BB.bottom && (OBJ_BB.bottom + OBJ_BB.top) / 2 <= player_BB.bottom)
				{
					if (OBJ_BB.left <= player_BB.left && player_BB.left <= OBJ_BB.right)
					{
						if (i == static_cast<int>(OBJ_ID::OBJ_PORTAL)) {
							return false;
						}
						if (i == static_cast<int>(OBJ_ID::OBJ_BULLET)) {
							dynamic_cast<Player2*>(player)->Get_Die() = true;
						}
						float dis = OBJ_BB.top - player_BB.bottom;
						dynamic_cast<Player2*>(player)->GetP()->GetPos().y += dis;

						return true;
					}
					else if (OBJ_BB.left <= player_BB.right && player_BB.right <= OBJ_BB.right)
					{
						if (i == static_cast<int>(OBJ_ID::OBJ_PORTAL)) {
							return false;
						}
						if (i == static_cast<int>(OBJ_ID::OBJ_BULLET)) {
							dynamic_cast<Player2*>(player)->Get_Die() = true;
						}
						float dis = OBJ_BB.top - player_BB.bottom;
						dynamic_cast<Player2*>(player)->GetP()->GetPos().y += dis;
						return true;
					}
					else if (OBJ_BB.left >= player_BB.left && player_BB.right >= OBJ_BB.right)
					{
						if (i == static_cast<int>(OBJ_ID::OBJ_PORTAL)) {
							return false;
						}
						if (i == static_cast<int>(OBJ_ID::OBJ_BULLET)) {
							dynamic_cast<Player2*>(player)->Get_Die() = true;
						}
						float dis = OBJ_BB.top - player_BB.bottom;
						dynamic_cast<Player2*>(player)->GetP()->GetPos().y += dis;
						return true;
					}
				}
				iter_begin++;
			}
		}
	}
	return false;
}

GLvoid CGameManager::CheckViewChange()
{
	// Check Key Pressed
	if (Get_Camera() != nullptr)
	{
		if (VIEW::VIEW_3D == m_View && Get_Camera()->Get_Move()) {
			if (CKeyManager::GetInstance()->KeyDown(KEY_F)) {
				m_View = VIEW::VIEW_2D;
			}
		}
		else if (VIEW::VIEW_2D == m_View && !Get_Camera()->Get_Move()) {
			if (CKeyManager::GetInstance()->KeyDown(KEY_F)) {
				m_View = VIEW::VIEW_3D;
			}
		}
	}
}

GLvoid CGameManager::ChangeView()
{
	list<CObj*>::iterator iter_begin;
	list<CObj*>::iterator iter_end;

	// Change View
	if (m_View == VIEW::VIEW_3D && Get_Camera()->Get_Move()) {
		CObj* player = m_ObjLst[static_cast<int>(OBJ_ID::OBJ_PLAYER2)].front();
		if (dynamic_cast<Player3*>(player)->Get_HoldingB()) {
			iter_begin = m_ObjLst[static_cast<int>(OBJ_ID::OBJ_BOX)].begin();
			iter_end = m_ObjLst[static_cast<int>(OBJ_ID::OBJ_BOX)].end();
			for (; iter_begin != iter_end;) {
				if (dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().z <= 1.6f && dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().z >= 1.4f) {
					dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().x = dynamic_cast<Player3*>(player)->Get_pMesh()->GetPos().x;
					dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().y = dynamic_cast<Player3*>(player)->Get_pMesh()->GetPos().y;
					glm::vec3 temp = dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos();
					(*iter_begin)->Get_BB() = { temp.x - 0.5f, temp.x + 0.5f, temp.y + 0.5f, temp.y - 0.5f };
					break;
				}
				++iter_begin;
			}
		}
	}
}

GLvoid CGameManager::CheckCollide()
{
	MonMapCollide();
	MonBulletCollide();
}

GLvoid CGameManager::MonMapCollide()
{
	list<CObj*>::iterator iter_begin;
	list<CObj*>::iterator iter_end;

	for (int i = static_cast<int>(OBJ_ID::OBJ_MONSTER1); i <= static_cast<int>(OBJ_ID::OBJ_MONSTER2); ++i) {
		list<CObj*>::iterator monster_iter_begin = m_ObjLst[i].begin();
		list<CObj*>::iterator monster_iter_end = m_ObjLst[i].end();
		for (; monster_iter_begin != monster_iter_end;) {
			BB monster_BB = (*monster_iter_begin)->Get_BB();

			for (int i = static_cast<int>(OBJ_ID::OBJ_MAP); i <= static_cast<int>(OBJ_ID::OBJ_BOX); ++i) {
				iter_begin = m_ObjLst[i].begin();
				iter_end = m_ObjLst[i].end();
				for (; iter_begin != iter_end;)
				{
					BB OBJ_BB = (*iter_begin)->Get_BB();
					if (!(OBJ_BB.bottom <= -0.1)) {
						if (monster_BB.left <= OBJ_BB.right && monster_BB.right >= OBJ_BB.right)
						{
							if (OBJ_BB.bottom <= monster_BB.top && monster_BB.top <= OBJ_BB.top)
							{
								dynamic_cast<Monster*>((*monster_iter_begin))->GetDir() = 1;
							}
							else if (OBJ_BB.bottom <= monster_BB.bottom && monster_BB.bottom <= OBJ_BB.top)
							{
								dynamic_cast<Monster*>((*monster_iter_begin))->GetDir() = 1;
							}
							else if (monster_BB.bottom <= OBJ_BB.top && OBJ_BB.top <= monster_BB.top)
							{
								dynamic_cast<Monster*>((*monster_iter_begin))->GetDir() = 1;
							}
							else if (monster_BB.bottom <= OBJ_BB.bottom && OBJ_BB.bottom <= monster_BB.top)
							{
								dynamic_cast<Monster*>((*monster_iter_begin))->GetDir() = 1;
							}
						}
						else if (monster_BB.right >= OBJ_BB.left && monster_BB.left <= OBJ_BB.left)
						{
							if (OBJ_BB.bottom <= monster_BB.top && monster_BB.top <= OBJ_BB.top)
							{
								dynamic_cast<Monster*>((*monster_iter_begin))->GetDir() = -1;
							}
							else if (OBJ_BB.bottom <= monster_BB.bottom && monster_BB.bottom <= OBJ_BB.top)
							{
								dynamic_cast<Monster*>((*monster_iter_begin))->GetDir() = -1;
							}
							else if (monster_BB.bottom <= OBJ_BB.top && OBJ_BB.top <= monster_BB.top)
							{
								dynamic_cast<Monster*>((*monster_iter_begin))->GetDir() = -1;
							}
							else if (monster_BB.bottom <= OBJ_BB.bottom && OBJ_BB.bottom <= monster_BB.top)
							{
								dynamic_cast<Monster*>((*monster_iter_begin))->GetDir() = -1;
							}
						}
					}
					++iter_begin;
				}
			}
			++monster_iter_begin;
		}
	}
}

GLvoid CGameManager::MonBulletCollide()
{
	for (list<CObj*>::iterator iter_bullet = m_ObjLst[static_cast<int>(OBJ_ID::OBJ_BULLET)].begin(); iter_bullet != m_ObjLst[static_cast<int>(OBJ_ID::OBJ_BULLET)].end() && VIEW::VIEW_2D == m_View; ++iter_bullet)
	{
		BB Bullet_BB = (*iter_bullet)->Get_BB();
		if (Bullet_BB.left <= -14.f)
		{
			SafeDelete((*iter_bullet));
			iter_bullet = m_ObjLst[static_cast<int>(OBJ_ID::OBJ_BULLET)].erase(iter_bullet);
			CRenderManager::GetInstance()->Get_RenderObj(RENDER_ID::REDER_BULLET).pop_front();
		}
		break;
	}
}

GLvoid CGameManager::PortalInteract()
{
	if (!m_ObjLst[static_cast<int>(OBJ_ID::OBJ_PORTAL)].empty())
	{
		CObj* player3D = m_ObjLst[static_cast<int>(OBJ_ID::OBJ_PLAYER2)].front();
		BB player3D_BB = player3D->Get_BB();
		CObj* portal = m_ObjLst[static_cast<int>(OBJ_ID::OBJ_PORTAL)].front();
		BB portal_BB = portal->Get_BB();

		if (portal_BB.left > player3D_BB.right || portal_BB.right < player3D_BB.left || portal_BB.top < player3D_BB.bottom || portal_BB.bottom > player3D_BB.top);
		else
		{
			if (VIEW::VIEW_3D == m_View) {
				if (m_ObjLst[static_cast<int>(OBJ_ID::OBJ_KEY)].empty()) {
					dynamic_cast<Player3*>(player3D)->Get_InPortal() = true;
				}
			}
		}
	}
}

HRESULT CGameManager::Clear_ObjList()
{
	for (int i = 0; i < static_cast<int>(OBJ_ID::OBJ_END); ++i)
		Clear_Obj((OBJ_ID)i);	

	return NOERROR;
}

HRESULT CGameManager::Clear_Obj(OBJ_ID eID)
{
	for (auto pObj : m_ObjLst[static_cast<int>(eID)])
		SafeDelete(pObj);
	m_ObjLst[static_cast<int>(eID)].clear();

	return NOERROR;
}

HRESULT CGameManager::Add_Camera(CCamera* pCamera)
{
	if (!pCamera)
		return E_FAIL;

	if (m_pCamera)
		SafeDelete(m_pCamera);
	m_pCamera = pCamera;

	return NOERROR;
}

HRESULT CGameManager::Delete_Camera()
{
	if(m_pCamera)
		SafeDelete(m_pCamera);
	return NOERROR;
}

GLvoid CGameManager::Render_Camera()
{
	if (m_pCamera)
		m_pCamera->Render();
	return GLvoid();
}

GLvoid CGameManager::init()
{
	bPortalCollide = false;
	bMonsterPlayerCollide = false;
	m_View = VIEW::VIEW_2D;
	return GLvoid();
}
