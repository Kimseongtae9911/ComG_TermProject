#pragma once

class CRenderManager;
class CKeyManager;
class CGameManager;
class CSceneManager;
class CShader;
class CSoundManager;

class CObj
{
public:
	CObj();
	~CObj();

public:
	virtual HRESULT Initialize();
	virtual GLint Update(const GLfloat fTimeDelta);
	virtual GLvoid Render();
	virtual BB& Get_BB() { return m_Box; }

protected:
	CRenderManager* m_pRender = nullptr;
	CKeyManager* m_pKeyMgr = nullptr;
	CGameManager* m_pGameMgr = nullptr;
	CSceneManager* m_pSceneMgr = nullptr;
	CShader* m_pShaderLoader = nullptr;
	CSoundManager* m_pSoundMgr = nullptr;
	BB m_Box;

protected:
	
	GLvoid Release();
};

