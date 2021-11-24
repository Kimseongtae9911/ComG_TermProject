#include "CSphere.h"

CSphere::CSphere()
{
}

CSphere::~CSphere()
{
	Release();
}

CSphere* CSphere::Initialize(string path)
{
	if (m_prefab == nullptr) {
		m_prefab = new CSphere;
		m_prefab->Load_Mesh(path);
		CSphere* temp = new CSphere;
		temp->m_vecVertex = m_prefab->m_vecVertex;
		temp->m_vecUVS = m_prefab->m_vecUVS;
		temp->m_vecNormal = m_prefab->m_vecNormal;

		return temp;
	}
	else {
		CSphere* temp = new CSphere;
		temp->m_vecVertex = m_prefab->m_vecVertex;
		temp->m_vecUVS = m_prefab->m_vecUVS;
		temp->m_vecNormal = m_prefab->m_vecNormal;

		return temp;
	}
}

//GLvoid CSphere::Release()
//{
//	m_vecVertex.clear();
//	m_vecUVS.clear();
//	m_vecNormal.clear();
//	m_vecColor.clear();
//}
