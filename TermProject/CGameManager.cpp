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

HRESULT CGameManager::Add_GameObj(OBJID eID, CObj* pObj)
{
	if (!pObj)
		return E_FAIL;

	m_ObjLst[eID].emplace_back(pObj);

	return NOERROR;
}

GLvoid CGameManager::Update(const GLfloat fTimeDelta)
{
	list<CObj*>::iterator iter_begin;
	list<CObj*>::iterator iter_end;

	for (int i = 0; i < OBJ_END; ++i)
	{
		iter_begin = m_ObjLst[i].begin();
		iter_end = m_ObjLst[i].end();
		for (; iter_begin != iter_end;)
		{
			if (OBJ_END == (*iter_begin)->Update(fTimeDelta))
			{
				SafeDelete(*iter_begin);
				iter_begin = m_ObjLst[i].erase(iter_begin);
			}
			else
				++iter_begin;
		}
	}

	if (Get_Camera() != nullptr)
	{
		if (!Get_View() && Get_Camera()->Get_Move()) {
			if (CKeyManager::GetInstance()->KeyDown(KEY_F)) {
				m_bView = !m_bView;
			}
		}
		else if (Get_View() && !Get_Camera()->Get_Move()) {
			if (CKeyManager::GetInstance()->KeyDown(KEY_F)) {
				m_bView = !m_bView;
			}
		}
	}


	if (!Get_View() && Get_Camera()->Get_Move()) {
		CObj* player = m_ObjLst[OBJ_PLAYER2].front();
		if (dynamic_cast<Player3*>(player)->Get_HoldingB()) {
			iter_begin = m_ObjLst[OBJ_BOX].begin();
			iter_end = m_ObjLst[OBJ_BOX].end();
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


	//Monster Map Collide
	for (int i = OBJ_MONSTER1; i <= OBJ_MONSTER2; ++i) {
		list<CObj*>::iterator monster_iter_begin = m_ObjLst[i].begin();
		list<CObj*>::iterator monster_iter_end = m_ObjLst[i].end();
		for (; monster_iter_begin != monster_iter_end;) {
			BB monster_BB = (*monster_iter_begin)->Get_BB();

			for (int i = OBJ_MAP; i <= OBJ_BOX; ++i) {
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
								dynamic_cast<Monster*>((*monster_iter_begin))->GetDir() = LEFT;
							}
							else if (OBJ_BB.bottom <= monster_BB.bottom && monster_BB.bottom <= OBJ_BB.top)
							{
								dynamic_cast<Monster*>((*monster_iter_begin))->GetDir() = LEFT;
							}
							else if (monster_BB.bottom <= OBJ_BB.top && OBJ_BB.top <= monster_BB.top)
							{
								dynamic_cast<Monster*>((*monster_iter_begin))->GetDir() = LEFT;
							}
							else if (monster_BB.bottom <= OBJ_BB.bottom && OBJ_BB.bottom <= monster_BB.top)
							{
								dynamic_cast<Monster*>((*monster_iter_begin))->GetDir() = LEFT;
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
	// map and bullet
	for (list<CObj*>::iterator iter_bullet = m_ObjLst[OBJ_BULLET].begin(); iter_bullet != m_ObjLst[OBJ_BULLET].end() && m_bView; ++iter_bullet ) // ����
	{
		BB Bullet_BB = (*iter_bullet)->Get_BB();
		if (Bullet_BB.left <= -14.f)
		{
			SafeDelete((*iter_bullet));
			iter_bullet = m_ObjLst[OBJ_BULLET].erase(iter_bullet);
			//--iter_bullet;
			CRenderManager::GetInstance()->Get_RenderObj(REDER_BULLET).pop_front();
		}
		break;
	}
	if (!m_ObjLst[OBJ_PORTAL].empty())
	{
		CObj* player2D = m_ObjLst[OBJ_PLAYER1].front();
		BB player2D_BB = player2D->Get_BB();
		CObj* player3D = m_ObjLst[OBJ_PLAYER2].front();
		BB player3D_BB = player3D->Get_BB();
		CObj* portal = m_ObjLst[OBJ_PORTAL].front();
		BB portal_BB = portal->Get_BB();
		if (portal_BB.left > player2D_BB.right || portal_BB.right < player2D_BB.left || portal_BB.top < player2D_BB.bottom || portal_BB.bottom > player2D_BB.top);
		else
		{
			if (Get_View()) {
				if (CKeyManager::GetInstance()->KeyDown(KEY_A)) {
					if (m_ObjLst[OBJ_KEY].empty()) {
						dynamic_cast<Player2*>(player2D)->Get_Portal() = true;
					}
				}
			}
		}
		if (portal_BB.left > player3D_BB.right || portal_BB.right < player3D_BB.left || portal_BB.top < player3D_BB.bottom || portal_BB.bottom > player3D_BB.top);
		else
		{
			if (!Get_View()) {
				if (m_ObjLst[OBJ_KEY].empty()) {
					dynamic_cast<Player3*>(player3D)->Get_InPortal() = true;
				}
			}
		}
		if (dynamic_cast<Player2*>(player2D)->Get_Portal() && dynamic_cast<Player3*>(player3D)->Get_Portal()) {
			CSoundManager::GetInstance()->Play_Sound(L"portal.wav", CSoundManager::PORTAL);
			bPortalCollide = true;
		}


		if (m_ObjLst[OBJ_KEY].empty()) {
			for (auto i : dynamic_cast<CPortal*>(portal)->Get_pMesh()->GetSMESH()) {
				for (int j = 0; j < i->color.size(); ++j) {
					i->color[j][3] = 1.0;
				}
			}
		}
	}
	if (!m_ObjLst[OBJ_PLAYER1].empty())
	{
		CObj* player2D = m_ObjLst[OBJ_PLAYER1].front();
		BB player2D_BB = player2D->Get_BB();
		CObj* player3D = m_ObjLst[OBJ_PLAYER2].front();
		BB player3D_BB = player3D->Get_BB();
		for (int i = OBJ_MONSTER1; i <= OBJ_MONSTER2; ++i)
		{
			list<CObj*>::iterator monster_iter_begin = m_ObjLst[i].begin();
			list<CObj*>::iterator monster_iter_end = m_ObjLst[i].end();
			for (; monster_iter_begin != monster_iter_end;)
			{
				BB monster_BB = (*monster_iter_begin)->Get_BB();
				if (m_bView)
				{
					if (monster_BB.left > player2D_BB.right || monster_BB.right < player2D_BB.left || monster_BB.top < player2D_BB.bottom || monster_BB.bottom > player2D_BB.top);
					else
					{
						bMonsterPlayerCollide = true;
						CSoundManager::GetInstance()->Play_Sound(L"playerDead.wav", CSoundManager::DEAD);
					}
				}
				else
				{
					if (monster_BB.left > player3D_BB.right || monster_BB.right < player3D_BB.left || monster_BB.top < player3D_BB.bottom || monster_BB.bottom > player3D_BB.top);
					else
					{
						bMonsterPlayerCollide = true;
						CSoundManager::GetInstance()->Play_Sound(L"playerDead.wav", CSoundManager::DEAD);
					}
				}
				++monster_iter_begin;
			}
		}
		/*for (list<CObj*>::iterator iter_M1 = m_ObjLst[OBJ_MONSTER1].begin(); iter_M1 != m_ObjLst[OBJ_MONSTER1].end(); ++iter_M1)
		{
			BB Monster1_BB = (*iter_M1)->Get_BB();
			if (Monster1_BB.left > player2D_BB.right || Monster1_BB.right < player2D_BB.left || Monster1_BB.top < player2D_BB.bottom || Monster1_BB.bottom > player2D_BB.top);
			else
			{
				bMonsterPlayerCollide = true;
			}
			if (Monster1_BB.left > player3D_BB.right || Monster1_BB.right < player3D_BB.left || Monster1_BB.top < player3D_BB.bottom || Monster1_BB.bottom > player3D_BB.top);
			else
			{
				bMonsterPlayerCollide = true;
			}
		}*/
	}
	






	if (m_pCamera)
		m_pCamera->Update(fTimeDelta);

	return GLvoid();
}

GLvoid CGameManager::MonCollide(int num) {
	list<CObj*>::iterator iter_begin;
	list<CObj*>::iterator iter_end;
	for (int i = OBJ_MONSTER1; i <= OBJ_MONSTER2; ++i) {
		list<CObj*>::iterator monster_iter_begin = m_ObjLst[i].begin();
		list<CObj*>::iterator monster_iter_end = m_ObjLst[i].end();
		for (; monster_iter_begin != monster_iter_end;) {
			BB monster_BB = (*monster_iter_begin)->Get_BB();
			for (int j = OBJ_MAP; j <= OBJ_BOX; ++j) {

				iter_begin = m_ObjLst[j].begin();
				iter_end = m_ObjLst[j].end();
				for (; iter_begin != iter_end;)
				{
					BB OBJ_BB = (*iter_begin)->Get_BB();
					switch (num) {
					case LEFT:
						if (monster_BB.left <= OBJ_BB.right && monster_BB.right >= OBJ_BB.right)
						{
							if (OBJ_BB.bottom <= monster_BB.top && monster_BB.top <= OBJ_BB.top)
							{
								dynamic_cast<Monster*>((*monster_iter_begin))->GetCollDir() = LEFT;
								//return true;
							}
							else if (OBJ_BB.bottom <= monster_BB.bottom && monster_BB.bottom <= OBJ_BB.top)
							{
								dynamic_cast<Monster*>((*monster_iter_begin))->GetCollDir() = LEFT;
							}
							else if (monster_BB.bottom <= OBJ_BB.top && OBJ_BB.top <= monster_BB.top)
							{
								dynamic_cast<Monster*>((*monster_iter_begin))->GetCollDir() = LEFT;
							}
							else if (monster_BB.bottom <= OBJ_BB.bottom && OBJ_BB.bottom <= monster_BB.top)
							{
								dynamic_cast<Monster*>((*monster_iter_begin))->GetCollDir() = LEFT;
							}

						}
						break;
					case RIGHT:
						if (monster_BB.right >= OBJ_BB.left && monster_BB.left <= OBJ_BB.left)
						{
							if (OBJ_BB.bottom <= monster_BB.top && monster_BB.top <= OBJ_BB.top)
							{
								dynamic_cast<Monster*>((*monster_iter_begin))->GetCollDir() = RIGHT;
							}
							else if (OBJ_BB.bottom <= monster_BB.bottom && monster_BB.bottom <= OBJ_BB.top)
							{
								dynamic_cast<Monster*>((*monster_iter_begin))->GetCollDir() = RIGHT;
							}
							else if (monster_BB.bottom <= OBJ_BB.top && OBJ_BB.top <= monster_BB.top)
							{
								dynamic_cast<Monster*>((*monster_iter_begin))->GetCollDir() = RIGHT;
							}
							else if (monster_BB.bottom <= OBJ_BB.bottom && OBJ_BB.bottom <= monster_BB.top)
							{
								dynamic_cast<Monster*>((*monster_iter_begin))->GetCollDir() = RIGHT;
							}
						}
						break;
					case DOWN:
						if (OBJ_BB.top >= monster_BB.bottom && (OBJ_BB.bottom + OBJ_BB.top) / 2 <= monster_BB.bottom)
						{
							if (OBJ_BB.left <= monster_BB.left && monster_BB.left <= OBJ_BB.right)
							{
								dynamic_cast<Monster*>((*monster_iter_begin))->GetCollDir() = DOWN;
							}
							else if (OBJ_BB.left <= monster_BB.right && monster_BB.right <= OBJ_BB.right)
							{
								dynamic_cast<Monster*>((*monster_iter_begin))->GetCollDir() = DOWN;
							}
							else if (OBJ_BB.left >= monster_BB.left && monster_BB.right >= OBJ_BB.right)
							{
								dynamic_cast<Monster*>((*monster_iter_begin))->GetCollDir() = DOWN;
							}
						}
						break;
					case UP:
						if (OBJ_BB.bottom <= monster_BB.top && (OBJ_BB.bottom + OBJ_BB.top) / 2 >= monster_BB.top)
						{
							if (OBJ_BB.left <= monster_BB.left && monster_BB.left <= OBJ_BB.right)
							{
								dynamic_cast<Monster*>((*monster_iter_begin))->GetCollDir() = UP;
							}
							else if (OBJ_BB.left <= monster_BB.right && monster_BB.right <= OBJ_BB.right)
							{
								dynamic_cast<Monster*>((*monster_iter_begin))->GetCollDir() = UP;
							}
							else if (OBJ_BB.left >= monster_BB.left && monster_BB.right >= OBJ_BB.right)
							{
								dynamic_cast<Monster*>((*monster_iter_begin))->GetCollDir() = UP;
							}
						}
						break;
					default:
						break;
					}
					++iter_begin;
				}
			}
			++monster_iter_begin;
		}
	}
}

bool CGameManager::Collide(int num)
{
	if (m_bView) {
		CObj* player = m_ObjLst[OBJ_PLAYER1].front();
		BB player_BB = player->Get_BB();
		switch (num) {
		case LEFT:
			for (int i = OBJ_MONSTER1; i <= OBJ_KEY; ++i)
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
							if (i == OBJ_KEY) {
								iter_begin = m_ObjLst[i].erase(iter_begin);
								return false;
							}
							if (i == OBJ_PORTAL) {
								return false;
							}
							if (i == OBJ_BULLET) {
								dynamic_cast<Player2*>(player)->Get_Die() = true;
							}
							return true;
						}
						else if (OBJ_BB.bottom < player_BB.bottom && player_BB.bottom < OBJ_BB.top)
						{
							if (i == OBJ_KEY) {
								iter_begin = m_ObjLst[i].erase(iter_begin);
								return false;
							}
							if (i == OBJ_PORTAL) {
								return false;
							}
							if (i == OBJ_BULLET) {
								dynamic_cast<Player2*>(player)->Get_Die() = true;
							}
							return true;
						}
						else if (player_BB.bottom < OBJ_BB.top && OBJ_BB.top <= player_BB.top)
						{
							if (i == OBJ_KEY) {
								iter_begin = m_ObjLst[i].erase(iter_begin);
								return false;
							}
							if (i == OBJ_PORTAL) {
								return false;
							}
							if (i == OBJ_BULLET) {
								dynamic_cast<Player2*>(player)->Get_Die() = true;
							}
							return true;
						}
						else if (player_BB.bottom < OBJ_BB.bottom && OBJ_BB.bottom <= player_BB.top)
						{
							if (i == OBJ_KEY) {
								iter_begin = m_ObjLst[i].erase(iter_begin);
								return false;
							}
							if (i == OBJ_PORTAL) {
								return false;
							}
							if (i == OBJ_BULLET) {
								dynamic_cast<Player2*>(player)->Get_Die() = true;
							}
							return true;
						}
					}
					++iter_begin;
				}
			}
			break;
		case RIGHT:
			for (int i = OBJ_MONSTER1; i <= OBJ_KEY; ++i)
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
							if (i == OBJ_KEY) {
								iter_begin = m_ObjLst[i].erase(iter_begin);
								return false;
							}
							if (i == OBJ_PORTAL) {
								return false;
							}
							if (i == OBJ_BULLET) {
								dynamic_cast<Player2*>(player)->Get_Die() = true;
							}
							return true;
						}
						else if (OBJ_BB.bottom < player_BB.bottom && player_BB.bottom < OBJ_BB.top)
						{
							if (i == OBJ_KEY) {
								iter_begin = m_ObjLst[i].erase(iter_begin);
								return false;
							}
							if (i == OBJ_PORTAL) {
								return false;
							}
							if (i == OBJ_BULLET) {
								dynamic_cast<Player2*>(player)->Get_Die() = true;
							}
							return true;
						}
						else if (player_BB.bottom < OBJ_BB.top && OBJ_BB.top <= player_BB.top)
						{
							if (i == OBJ_KEY) {
								iter_begin = m_ObjLst[i].erase(iter_begin);
								return false;
							}
							if (i == OBJ_PORTAL) {
								return false;
							}
							if (i == OBJ_BULLET) {
								dynamic_cast<Player2*>(player)->Get_Die() = true;
							}
							return true;
						}
						else if (player_BB.bottom < OBJ_BB.bottom && OBJ_BB.bottom <= player_BB.top)
						{
							if (i == OBJ_KEY) {
								iter_begin = m_ObjLst[i].erase(iter_begin);
								return false;
							}
							if (i == OBJ_PORTAL) {
								return false;
							}
							if (i == OBJ_BULLET) {
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
		CObj* player = m_ObjLst[OBJ_PLAYER2].front();
		BB player_BB = player->Get_BB();
		switch (num) {
		case LEFT:
			for (int i = OBJ_MONSTER1; i < OBJ_KEY; ++i)
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
							if (i == OBJ_PORTAL) {
								dynamic_cast<Player3*>(player)->Get_CollideB() = false;
								return false;
							}
							if (i == OBJ_BOX) {
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
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().x -= 0.15;
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
							if (i == OBJ_PORTAL) {
								dynamic_cast<Player3*>(player)->Get_CollideB() = false;
								return false;
							}
							if (i == OBJ_BOX) {
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
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().x -= 0.15;
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
							if (i == OBJ_PORTAL) {
								dynamic_cast<Player3*>(player)->Get_CollideB() = false;
								return false;
							}
							if (i == OBJ_BOX) {
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
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().x -= 0.15;
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
							if (i == OBJ_PORTAL) {
								dynamic_cast<Player3*>(player)->Get_CollideB() = false;
								return false;
							}
							if (i == OBJ_BOX) {
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
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().x -= 0.15;
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
		case RIGHT:
			for (int i = OBJ_MONSTER1; i < OBJ_KEY; ++i)
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
							if (i == OBJ_PORTAL) {
								dynamic_cast<Player3*>(player)->Get_CollideB() = false;
								return false;
							}
							if (i == OBJ_BOX) {
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
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().x += 0.15;
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
							if (i == OBJ_PORTAL) {
								dynamic_cast<Player3*>(player)->Get_CollideB() = false;
								return false;
							}
							if (i == OBJ_BOX) {
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
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().x += 0.15;
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
							if (i == OBJ_PORTAL) {
								dynamic_cast<Player3*>(player)->Get_CollideB() = false;
								return false;
							}
							if (i == OBJ_BOX) {
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
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().x += 0.15;
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
							if (i == OBJ_PORTAL) {
								dynamic_cast<Player3*>(player)->Get_CollideB() = false;
								return false;
							}
							if (i == OBJ_BOX) {
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
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().x += 0.15;
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
		case UP:
			for (int i = OBJ_MONSTER1; i < OBJ_KEY; ++i)
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
							if (i == OBJ_PORTAL) {
								dynamic_cast<Player3*>(player)->Get_CollideB() = false;
								return false;
							}
							if (i == OBJ_BOX) {
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
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().y += 0.15;
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
							if (i == OBJ_PORTAL) {
								dynamic_cast<Player3*>(player)->Get_CollideB() = false;
								return false;
							}
							if (i == OBJ_BOX) {
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
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().y += 0.15;
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
							if (i == OBJ_PORTAL) {
								dynamic_cast<Player3*>(player)->Get_CollideB() = false;
								return false;
							}
							if (i == OBJ_BOX) {
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
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().y += 0.15;
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
		case DOWN:
			for (int i = OBJ_MONSTER1; i < OBJ_KEY; ++i)
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
							if (i == OBJ_PORTAL) {
								dynamic_cast<Player3*>(player)->Get_CollideB() = false;
								return false;
							}
							if (i == OBJ_BOX) {
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
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().y -= 0.15;
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
							if (i == OBJ_PORTAL) {
								dynamic_cast<Player3*>(player)->Get_CollideB() = false;
								return false;
							}
							if (i == OBJ_BOX) {
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
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().y -= 0.15;
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
							if (i == OBJ_PORTAL) {
								dynamic_cast<Player3*>(player)->Get_CollideB() = false;
								return false;
							}
							if (i == OBJ_BOX) {
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
										dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().y -= 0.15;
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
	CObj* player = m_ObjLst[OBJ_PLAYER1].front();
	BB player_BB = player->Get_BB();
	if (dynamic_cast<Player2*>(player)->GetJump()) {
		switch (num) {
		case 1:
			for (int i = OBJ_MONSTER1; i < OBJ_SPIKE; ++i)
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
							if (i == OBJ_KEY) {
								iter_begin = m_ObjLst[i].erase(iter_begin);
								return false;
							}
							if (i == OBJ_PORTAL) {
								return false;
							}
							if (i == OBJ_BULLET) {
								dynamic_cast<Player2*>(player)->Get_Die() = true;
							}
							return true;
						}
						else if (OBJ_BB.left <= player_BB.right && player_BB.right <= OBJ_BB.right)
						{
							if (i == OBJ_KEY) {
								iter_begin = m_ObjLst[i].erase(iter_begin);
								return false;
							}
							if (i == OBJ_PORTAL) {
								return false;
							}
							if (i == OBJ_BULLET) {
								dynamic_cast<Player2*>(player)->Get_Die() = true;
							}
							return true;
						}
						else if (OBJ_BB.left >= player_BB.left && player_BB.right >= OBJ_BB.right)
						{
							if (i == OBJ_KEY) {
								iter_begin = m_ObjLst[i].erase(iter_begin);
								return false;
							}
							if (i == OBJ_PORTAL) {
								return false;
							}
							if (i == OBJ_BULLET) {
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
			for (int i = OBJ_MONSTER1; i < OBJ_SPIKE; ++i)
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
							if (i == OBJ_KEY) {
								iter_begin = m_ObjLst[i].erase(iter_begin);
								return false;
							}
							if (i == OBJ_PORTAL) {
								return false;
							}
							if (i == OBJ_BULLET) {
								dynamic_cast<Player2*>(player)->Get_Die() = true;
							}
							float dis = OBJ_BB.top - player_BB.bottom;
							dynamic_cast<Player2*>(player)->GetP()->GetPos().y += dis;

							return true;
						}
						else if (OBJ_BB.left <= player_BB.right && player_BB.right <= OBJ_BB.right)
						{
							if (i == OBJ_KEY) {
								iter_begin = m_ObjLst[i].erase(iter_begin);
								return false;
							}
							if (i == OBJ_PORTAL) {
								return false;
							}
							if (i == OBJ_BULLET) {
								dynamic_cast<Player2*>(player)->Get_Die() = true;
							}
							float dis = OBJ_BB.top - player_BB.bottom;
							dynamic_cast<Player2*>(player)->GetP()->GetPos().y += dis;
							return true;
						}
						else if (OBJ_BB.left >= player_BB.left && player_BB.right >= OBJ_BB.right)
						{
							if (i == OBJ_KEY) {
								iter_begin = m_ObjLst[i].erase(iter_begin);
								return false;
							}
							if (i == OBJ_PORTAL) {
								return false;
							}
							if (i == OBJ_BULLET) {
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
		for (int i = OBJ_MONSTER1; i < OBJ_SPIKE; ++i)
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
						if (i == OBJ_KEY) {
							iter_begin = m_ObjLst[i].erase(iter_begin);
							return false;
						}
						if (i == OBJ_PORTAL) {
							return false;
						}
						if (i == OBJ_BULLET) {
							dynamic_cast<Player2*>(player)->Get_Die() = true;
						}
						float dis = OBJ_BB.top - player_BB.bottom;
						dynamic_cast<Player2*>(player)->GetP()->GetPos().y += dis;

						return true;
					}
					else if (OBJ_BB.left <= player_BB.right && player_BB.right <= OBJ_BB.right)
					{
						if (i == OBJ_KEY) {
							iter_begin = m_ObjLst[i].erase(iter_begin);
							return false;
						}
						if (i == OBJ_PORTAL) {
							return false;
						}
						if (i == OBJ_BULLET) {
							dynamic_cast<Player2*>(player)->Get_Die() = true;
						}
						float dis = OBJ_BB.top - player_BB.bottom;
						dynamic_cast<Player2*>(player)->GetP()->GetPos().y += dis;
						return true;
					}
					else if (OBJ_BB.left >= player_BB.left && player_BB.right >= OBJ_BB.right)
					{
						if (i == OBJ_KEY) {
							iter_begin = m_ObjLst[i].erase(iter_begin);
							return false;
						}
						if (i == OBJ_PORTAL) {
							return false;
						}
						if (i == OBJ_BULLET) {
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

HRESULT CGameManager::Clear_ObjList()
{
	for (int i = 0; i < OBJ_END; ++i)
		Clear_Obj((OBJID)i);
	//

	return NOERROR;
}

HRESULT CGameManager::Clear_Obj(OBJID eID)
{
	for (auto pObj : m_ObjLst[eID])
		SafeDelete(pObj);
	m_ObjLst[eID].clear();

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
	m_bView = true;
	return GLvoid();
}
