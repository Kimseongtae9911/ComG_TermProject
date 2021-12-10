#pragma once
class CObj;
class CCamera;

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
	HRESULT Add_Camera(CCamera* pCamera);
	GLvoid Render_Camera();
	CCamera* Get_Camera() { return m_pCamera; }

private:
	CCamera* m_pCamera = nullptr;
	list<CObj*> m_ObjLst[OBJ_END];


};

