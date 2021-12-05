#include "CObj.h"
#include "CMesh.h"

class Player : public CObj
{
public:
	Player();
	~Player();

public:
	virtual HRESULT Initialize();
    virtual GLint Update(const GLfloat fTimeDelta);
	virtual GLvoid Render();

private:
	CMesh* m_player_2D;
	CMesh* m_player_3D;

private:
	GLfloat m_fAlpha;
	bool m_bView{ true }; // true ->2D, false ->3D

public:
	static Player* Create();
};

