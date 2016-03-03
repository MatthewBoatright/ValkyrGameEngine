#include "obj_model.h"

namespace Valkyr { namespace Graphics { 

	OBJModel::OBJModel(const char * filename)
		: IRenderable()
	{
		init(filename);
	}

	void OBJModel::bind()
	{
		m_VertexArray->bind();
		m_IndexBuffer->bind();
	}

	void OBJModel::unbind()
	{
		m_IndexBuffer->unbind();
		m_VertexArray->unbind();
	}

	bool OBJModel::init(const char * filename)
	{
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> uvs;
		std::vector<glm::vec3> normals;
		bool res = loadOBJ(filename, vertices, uvs, normals);

		if (!res)
			loadDefaultModel();

		std::vector<unsigned short> indices;
		std::vector<glm::vec3> indexed_vertices;
		std::vector<glm::vec2> indexed_uvs;
		std::vector<glm::vec3> indexed_normals;
		indexVBO(vertices, uvs, normals, indices, indexed_vertices, indexed_uvs, indexed_normals);

		m_VertexArray = new VertexArray();
		m_VertexArray->addBuffer(new VertexBuffer(indexed_vertices),	0);
		m_VertexArray->addBuffer(new VertexBuffer(indexed_uvs),		1);
		m_VertexArray->addBuffer(new VertexBuffer(indexed_normals),	2);
		m_IndexBuffer = new IndexBuffer(indices);

		return true;
	}

	void OBJModel::loadDefaultModel()
	{

	}

} }