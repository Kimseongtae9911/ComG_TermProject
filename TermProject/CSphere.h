#include "CMesh.h"
#include "stdafx.h"

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