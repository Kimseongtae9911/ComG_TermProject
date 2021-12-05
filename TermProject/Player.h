#include "CObj.h"
#include "CMesh.h"

class Player : public CObj
{
public:
	Player();
	~Player();

public:
	HRESULT Initialize();
    GLint Update(const GLfloat fTimeDelta);
	GLvoid Render();

private:
	CMesh* m_player_2D;
	CMesh* m_player_3D;

private:
	GLfloat m_fAlpha;
	bool m_bPlayer{ true }; // true ->2D, false ->3D
};

