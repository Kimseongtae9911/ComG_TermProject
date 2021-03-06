#pragma once
class CObj;
class CCamera;
class CKeyManager;

class CGameManager
{
	DECLARE_SINGLETON(CGameManager)

private:
	CGameManager();
	~CGameManager();

public:
	HRESULT Add_GameObj(OBJID eID, CObj* pObj);
	GLvoid Update(const GLfloat fTimeDelta);
	HRESULT Clear_ObjList();
	HRESULT Clear_Obj(OBJID eID);

public:
	bool& Get_boolPortal() { return bPortalCollide; };
	bool& Get_CollideMTP() { return bMonsterPlayerCollide; };

public:
	HRESULT Add_Camera(CCamera* pCamera);
	HRESULT Delete_Camera();
	GLvoid Render_Camera();
	GLvoid init();
	CCamera* Get_Camera() { return m_pCamera; };
	bool Get_View() { return m_bView; };
	list<CObj*>& Get_Obj(OBJID ID) { return m_ObjLst[ID]; };
	bool Collide(int num);
	GLvoid MonCollide(int num);
	bool JumpCollide(int num);
	bool bPortalCollide = false;
	bool bMonsterPlayerCollide = false;
	
private:
	CCamera* m_pCamera = nullptr;
	list<CObj*> m_ObjLst[OBJ_END];

private:
	bool m_bView = true;

};

