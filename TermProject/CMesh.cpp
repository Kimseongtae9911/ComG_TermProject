#include "CMesh.h"

CMesh::CMesh()
{
}

CMesh::~CMesh()
{
}

HRESULT CMesh::Initialize(string path)
{

	return E_NOTIMPL;
}

GLvoid CMesh::Render()
{
	return GLvoid();
}

HRESULT CMesh::Load_Mesh(string path)
{
	vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	vector< glm::vec3 > temp_vertices;
	vector< glm::vec2 > temp_uvs;
	vector< glm::vec3 > temp_normals;

	FILE* file = nullptr;
	if (FAILED(fopen_s(&file, path.c_str(), "r")))
	{
		cout << "Impossible to open the file !" << endl;
		return E_FAIL;
	}

	while (true)
	{
		char chLineHeader[128];
		int res = fscanf_s(file, "%s", chLineHeader, 128);
		if (res == EOF)
			break;

		if (strcmp(chLineHeader, "v") == 0)
		{
			glm::vec3 vertex;
			fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(chLineHeader, "vt") == 0)
		{
			glm::vec2 uv;
			fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(chLineHeader, "vn") == 0)
		{
			glm::vec3 normal;
			fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(chLineHeader, "f") == 0)
		{
			string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9)
			{
				cout << "File can't be read by our simple parser : ( Try exporting with other options" << endl;
				return E_FAIL;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}

	for (unsigned int i = 0; i < vertexIndices.size(); i++)
	{
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		m_vecVertex.push_back(vertex);
	}

	for (unsigned int i = 0; i < uvIndices.size(); i++)
	{
		unsigned int uvIndex = uvIndices[i];
		glm::vec2 uv = temp_uvs[uvIndex - 1];
		m_vecUVS.push_back(uv);
	}

	for (unsigned int i = 0; i < normalIndices.size(); i++)
	{
		unsigned int normalIndex = normalIndices[i];
		glm::vec3 normal = temp_normals[normalIndex - 1];
		m_vecNormal.push_back(normal);
	}

	return NOERROR;
}

GLvoid CMesh::Release()
{
	return GLvoid();
}

CMesh* CMesh::Create(string path)
{
	CMesh* pInstance = new CMesh;

	if (FAILED(pInstance->Initialize(path)))
	{
		SafeDelete(pInstance);
		return nullptr;
	}
	return pInstance;
}
