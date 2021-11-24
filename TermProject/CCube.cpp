#include "CCube.h"

CCube::CCube()
{
}

CCube::~CCube()
{
	Release();
}

CCube* CCube::Initialize(string path)
{
	if (m_prefab == nullptr) {
		m_prefab = new CCube;
		m_prefab->Load_Mesh(path);
		CCube* temp = new CCube;
		temp->m_vecVertex = m_prefab->m_vecVertex;
		temp->m_vecUVS = m_prefab->m_vecUVS;
		temp->m_vecNormal = m_prefab->m_vecNormal;

		return temp;
	}
	else {
		CCube* temp = new CCube;
		temp->m_vecVertex = m_prefab->m_vecVertex;
		temp->m_vecUVS = m_prefab->m_vecUVS;
		temp->m_vecNormal = m_prefab->m_vecNormal;

		return temp;
	}
}

//GLvoid CCube::Release()
//{
//	m_vecVertex.clear();
//	m_vecUVS.clear();
//	m_vecNormal.clear();
//	m_vecColor.clear();
//}
