#include "CMesh.h"
#include "stdafx.h"

class CCube : public CMesh
{
public:
	CCube();
	~CCube();

public:
	CCube* Initialize(string path);
	//GLvoid Release();

private:
	static CCube* m_prefab;
};