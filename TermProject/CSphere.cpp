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
		temp->m_vecVertices = m_prefab->m_vecVertices;
		temp->m_vecTexcoords = m_prefab->m_vecTexcoords;
		temp->m_vecNormals = m_prefab->m_vecNormals;

		return temp;
	}
	else {
		CSphere* temp = new CSphere;
		temp->m_vecVertices = m_prefab->m_vecVertices;
		temp->m_vecTexcoords = m_prefab->m_vecTexcoords;
		temp->m_vecNormals = m_prefab->m_vecNormals;

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
