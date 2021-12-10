#include "stdafx.h"
#include "CCube.h"

CCube* CCube::m_prefab = nullptr;

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
		temp->m_vecVertices = m_prefab->m_vecVertices;
		temp->m_vecTexcoords = m_prefab->m_vecTexcoords;
		temp->m_vecNormals = m_prefab->m_vecNormals;

		return temp;
	}
	else {
		CCube* temp = new CCube;
		temp->m_vecVertices = m_prefab->m_vecVertices;
		temp->m_vecTexcoords = m_prefab->m_vecTexcoords;
		temp->m_vecNormals = m_prefab->m_vecNormals;

		return temp;
	}
}

GLvoid CCube::Release()
{
}
