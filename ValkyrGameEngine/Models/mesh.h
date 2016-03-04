#pragma once

#include <vector>
#include <fstream>

#include <GL/glew.h>

#include <glm/glm.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../Shaders/texture.h"
#include "../Buffers/index_buffer.h"
#include "../Buffers/vertex_buffer.h"
#include "../Buffers/vertex_array.h"

namespace Valkyr { namespace Graphics { 

	class Mesh
	{
	public:
		Mesh();
		~Mesh();

		bool loadMesh(const std::string & filePath);
		void render();

	private:
		struct MeshEntry
		{
			MeshEntry();
			~MeshEntry();

			VertexArray * VAO;
			VertexBuffer * VBO;
			IndexBuffer * IBO;
			unsigned int MaterialIndex;

			void init(const std::vector<Vertex> & vertices, const std::vector<unsigned int> & indices);
			void init(const std::vector<glm::vec3> & pos, const std::vector<glm::vec2> & uv, const std::vector<glm::vec3> & normal, const std::vector<unsigned int> & indices);
		};

		std::vector<MeshEntry> m_Entries;
		std::vector<Texture*> m_Textures;

		bool initFromAIScene(const aiScene * scene, const std::string & filePath);
		void initMesh(unsigned int index, const aiMesh * mesh);
		bool initMaterials(const aiScene * scene, const std::string & filePath);
		void clear();

	};

} }