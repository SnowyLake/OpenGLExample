#include "geometry.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
Geometry::Geometry(const std::vector<float>& vertices, unsigned int size[],
				   std::optional<std::reference_wrapper<const std::vector<float>>> indices)
	:m_vertices(vertices), m_indices(indices)
{
	SetBuffers(m_vertices, size);
}
Geometry::Geometry(BIGType geom, bool haveIdx)
	:m_vertices(BIData::s_vectices.at(geom))
{
	if (haveIdx)
	{
		//indices in builtin_data is unfinished
		//m_indices = s_vecIndices.at(geom);
	} else {
		m_indices = std::nullopt;
	}
	SetBuffers(geom);
}
Geometry::~Geometry()
{}

void Geometry::Render()
{

}

inline void Geometry::Delete()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
}

inline unsigned int Geometry::GetVAO() const 
{ return m_VAO; }
inline unsigned int Geometry::GetTexture() const
{ return m_texture; }

void Geometry::SetTexture(std::string_view path)
{
	unsigned int texture;
	glGenTextures(1, &texture);
	m_texture = LoadTextureFromFile(texture, path.data());
}
void Geometry::SetTexture(BITList tex)
{
	unsigned int texture;
	glGenTextures(1, &texture);
	const char* path = BIData::s_texturesPath.at(tex);
	m_texture = LoadTextureFromFile(texture, path);
}

void Geometry::SetBuffers(BIGType type)
{

}
void Geometry::SetBuffers(std::vector<float> vertices, unsigned int size[])
{

}
unsigned int Geometry::LoadTextureFromFile(unsigned int tex, const char* path)
{
	int width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);

	if (data)
	{
		GLenum format = NULL;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, tex);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	} else
	{
#if _MSVC_LANG >= 202002L	/*CXX20*/
		std::cout << std::format("Cubemap texture failed to load at path: {}", path);
#else	
		std::cout << "Cubemap texture failed to load at path: " << path << std::endl;
#endif
		stbi_image_free(data);
	}
	return tex;
}