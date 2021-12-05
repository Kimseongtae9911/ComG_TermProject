#pragma once
#include "CMesh.h"

class CSphere : public CMesh
{	
public:
	CSphere();
	~CSphere();

public:
	CSphere* Initialize(string path);
	//GLvoid Release();

private:
	static CSphere* m_prefab;
};

CSphere* CSphere::m_prefab = nullptr;