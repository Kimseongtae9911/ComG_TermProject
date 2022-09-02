#pragma once
#include "Enum.h"

typedef struct tagShader
{
public:
	tagShader() { memset(this, 0, sizeof(tagShader)); }
	GLuint program;
	GLchar* vertexsource;
	GLchar* fragmentsource;
	GLuint vertexshader;
	GLuint fragmentshader;
}SHADER;

typedef struct tagTexture
{
public:
	tagTexture() { memset(this, 0, sizeof(tagTexture)); }
	GLuint id;
	GLint width;
	GLint height;
	GLint nrChannels;
}TEXTURE;

class CTexture;
typedef struct tagMaterial
{
	GLchar name[256] = "";
	GLint illum;
	string map_Kd = "";
	GLfloat Ns;
	GLfloat Ni;
	GLfloat d;
	GLfloat Ka[3];
	GLfloat Kd[3];
	GLfloat Ks[3];
	GLfloat Tf[3];
	CTexture* texture;
}MATERIAL;

typedef struct tagSubMesh
{
	GLchar name[256] = "";
	GLchar matname[256] = "";
	GLuint vao = 0;
	GLuint vbo[4] = {};
	vector<GLint> indices[4];
	vector<glm::vec3> vertex;
	vector<glm::vec2> texcoord;
	vector<glm::vec3> normal;
	vector<glm::vec4> color;
	MATERIAL* material;
}SUBMESH;

typedef struct BoundingBox2
{
	GLfloat left; //x
	GLfloat right; //x
	GLfloat top; //y
	GLfloat bottom; //y
}BB;

typedef struct BoundingBox
{
	glm::vec3 Center;
	glm::vec3 Extent;
	glm::vec3 TransCenter{};
	glm::vec3 TransExtent{};
	glm::mat4 TransMatrix{1.0f};

	BoundingBox() noexcept : Center{ 0.f, 0.f, 0.f }, Extent{ 0.5f, 0.5f, 0.5f } {}
	constexpr BoundingBox(const glm::vec3& center, const glm::vec3 extent, const int type) noexcept : Center{ center }, Extent{ extent } {}
	constexpr BoundingBox(const glm::vec3& min, const glm::vec3 max) noexcept : Center{ glm::vec3{(min.x + max.x) / 2.f, (min.y + max.y) / 2.f, (min.z + max.z) / 2.f} }
		, Extent{ glm::vec3{(max.x - min.x) / 2.f, (max.y - min.y) / 2.f, (max.z - min.z) / 2.f}} {}

    BoundingBox(const BoundingBox&) = default;
    BoundingBox& operator=(const BoundingBox&) = default;

    BoundingBox(BoundingBox&&) = default;
    BoundingBox& operator=(BoundingBox&&) = default;

    void Transform(const glm::mat4& Mat) noexcept
    {
		TransMatrix = glm::mat4(1.0f);
		TransMatrix = TransMatrix * Mat;
    }

	void Transform(const glm::mat4& Mat, const glm::vec3& Scale, const glm::vec3& Rotate, const glm::vec3& Translation) noexcept
	{
		TransMatrix = glm::mat4(1.0f);

		TransMatrix = glm::translate(TransMatrix, Translation);

		TransMatrix = TransMatrix * Mat * glm::scale(TransMatrix, Scale);
	}

	void Transform(float Scale, const glm::vec3& Rotate, const glm::vec3& Translation) noexcept
	{
		TransMatrix = glm::translate(TransMatrix, Translation);

		TransMatrix = glm::rotate(TransMatrix, glm::radians(Rotate.x), glm::vec3(1.0f, 0.0f, 0.0f));
		TransMatrix = glm::rotate(TransMatrix, glm::radians(Rotate.y), glm::vec3(0.0f, 1.0f, 0.0f));
		TransMatrix = glm::rotate(TransMatrix, glm::radians(Rotate.z), glm::vec3(0.0f, 0.0f, 1.0f));

		TransMatrix = glm::scale(TransMatrix, glm::vec3(Scale, Scale, Scale));	
	}

	bool Contains(const glm::vec3& point) const noexcept
	{
		glm::vec3 Min = TransCenter - TransExtent;
		glm::vec3 Max = TransCenter + TransExtent;

		bool out = point.x < Min.x ||
			point.y < Min.y ||
			point.z < Min.z ||
			point.x > Min.x ||
			point.y > Max.y ||
			point.z > Max.z;

		return !out;
	}

	bool Intersects(const BoundingBox& box) noexcept
	{
		glm::vec3 MinA = TransCenter - TransExtent;
		glm::vec3 MaxA = TransCenter + TransExtent;

		glm::vec3 MinB = box.TransCenter - box.TransExtent;
		glm::vec3 MaxB = box.TransCenter + box.TransExtent;

		bool intersect =
			MaxA.x < MinB.x ||
			MaxA.y < MinB.y ||
			MaxB.x < MinA.x ||
			MaxB.y < MinA.y;

		return !intersect;
	}

	bool IntersectsDis(const BoundingBox& box) const noexcept
	{
		float dis = glm::distance(TransCenter, box.TransCenter);

		float max_extent1 = max(box.TransExtent.x, box.TransExtent.y);
		float max_extent2 = max(TransExtent.x, TransExtent.y);

		bool instersect = dis < (max_extent1 + max_extent2);

		return instersect;
	}

	vector<glm::vec3> GetCorners() 
	{
		vector<glm::vec3> corners;
		corners.reserve(8);

		glm::vec4 corner[8];

		corner[0] = { Center.x - Extent.x, Center.y + Extent.y, Center.z + Extent.z, 1.0f };
		corner[1] = { Center.x - Extent.x, Center.y + Extent.y, Center.z - Extent.z, 1.0f };
		corner[2] = { Center.x + Extent.x, Center.y + Extent.y, Center.z - Extent.z, 1.0f };
		corner[3] = { Center.x + Extent.x, Center.y + Extent.y, Center.z + Extent.z, 1.0f };
		corner[4] = { Center.x - Extent.x, Center.y - Extent.y, Center.z + Extent.z, 1.0f };
		corner[5] = { Center.x - Extent.x, Center.y - Extent.y, Center.z - Extent.z, 1.0f };
		corner[6] = { Center.x + Extent.x, Center.y - Extent.y, Center.z - Extent.z, 1.0f };
		corner[7] = { Center.x + Extent.x, Center.y - Extent.y, Center.z + Extent.z, 1.0f };

		for (int i = 0; i < 8; ++i) {
			corner[i] = TransMatrix * corner[i];
			glm::vec3 temp = { corner[i].x, corner[i].y, corner[i].z };
			corners.push_back(temp);
		}

		return corners;
	}
	vector<glm::vec3> GetCornersBox()
	{
		vector<glm::vec3> corners;
		corners.reserve(28);

		glm::vec4 corner[28];
		int i = 0;

		//Top
		corner[i++] = { Center.x - Extent.x, Center.y + Extent.y, Center.z + Extent.z, 1.0f };
		corner[i++] = { Center.x - Extent.x, Center.y + Extent.y, Center.z - Extent.z, 1.0f };
		corner[i++] = { Center.x + Extent.x, Center.y + Extent.y, Center.z - Extent.z, 1.0f };
		corner[i++] = { Center.x + Extent.x, Center.y + Extent.y, Center.z + Extent.z, 1.0f };

		//Bottom
		corner[i++] = { Center.x - Extent.x, Center.y - Extent.y, Center.z + Extent.z, 1.0f };
		corner[i++] = { Center.x - Extent.x, Center.y - Extent.y, Center.z - Extent.z, 1.0f };
		corner[i++] = { Center.x + Extent.x, Center.y - Extent.y, Center.z - Extent.z, 1.0f };
		corner[i++] = { Center.x + Extent.x, Center.y - Extent.y, Center.z + Extent.z, 1.0f };

		//Left
		corner[i++] = { Center.x - Extent.x, Center.y + Extent.y, Center.z + Extent.z, 1.0f };
		corner[i++] = { Center.x - Extent.x, Center.y + Extent.y, Center.z - Extent.z, 1.0f };
		corner[i++] = { Center.x - Extent.x, Center.y - Extent.y, Center.z - Extent.z, 1.0f };
		corner[i++] = { Center.x - Extent.x, Center.y - Extent.y, Center.z + Extent.z, 1.0f };

		//Right
		corner[i++] = { Center.x + Extent.x, Center.y + Extent.y, Center.z + Extent.z, 1.0f };
		corner[i++] = { Center.x + Extent.x, Center.y - Extent.y, Center.z + Extent.z, 1.0f };
		corner[i++] = { Center.x + Extent.x, Center.y - Extent.y, Center.z - Extent.z, 1.0f };
		corner[i++] = { Center.x + Extent.x, Center.y + Extent.y, Center.z - Extent.z, 1.0f };

		//Front
		corner[i++] = { Center.x - Extent.x, Center.y + Extent.y, Center.z + Extent.z, 1.0f };
		corner[i++] = { Center.x - Extent.x, Center.y - Extent.y, Center.z + Extent.z, 1.0f };
		corner[i++] = { Center.x + Extent.x, Center.y - Extent.y, Center.z + Extent.z, 1.0f };
		corner[i++] = { Center.x + Extent.x, Center.y + Extent.y, Center.z + Extent.z, 1.0f };

		//Back
		corner[i++] = { Center.x - Extent.x, Center.y + Extent.y, Center.z - Extent.z, 1.0f };
		corner[i++] = { Center.x + Extent.x, Center.y + Extent.y, Center.z - Extent.z, 1.0f };
		corner[i++] = { Center.x + Extent.x, Center.y - Extent.y, Center.z - Extent.z, 1.0f };
		corner[i++] = { Center.x - Extent.x, Center.y - Extent.y, Center.z - Extent.z, 1.0f };

		for (int j = 0; j < 28; ++j) {
			corner[j] = TransMatrix * corner[j];
			glm::vec3 temp = { corner[j].x, corner[j].y, corner[j].z };
			corners.push_back(temp);
		}

		return corners;
	}

	void Update(const glm::vec3& min, const glm::vec3& max)
	{
		TransCenter = { (max.x + min.x) / 2.f, (max.y + min.y) / 2.f , (max.z + min.z) / 2.f };
		TransExtent = { abs(max.x - min.x) / 2.f, abs(max.y - min.y) / 2.f , abs(max.z - min.z) / 2.f };
	}
}BoundingBox;