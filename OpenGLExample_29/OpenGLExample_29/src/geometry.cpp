#include "geometry.h"

Geometry::Geometry(const std::vector<float>& vertices, const std::vector<uint>& vertOffset,
				   std::optional<std::reference_wrapper<const std::vector<float>>> indices)
	:m_vertices(vertices), m_indices(indices)
{
	SetBuffers(vertOffset);
}
Geometry::Geometry(BIGType geom, bool haveIdx)
	:m_vertices(BIData::Geometries.at(geom).vertices)
{
	if (haveIdx)
	{
		//indices in builtin_data is unfinished
		//m_indices = s_vecIndices.at(geom);
	} else {
		m_indices = std::nullopt;
		m_EBO = 0;
	}
	SetBuffers(geom);
}
Geometry::~Geometry()
{}

void Geometry::Render(Shader& shader,
					  bool  whetherUseTexture/* = true*/,
					  int   glDrawMode/* = GL_TRIANGLES*/,
					  float pixelSize/* = 1.0f*/,
					  std::optional<uint> tex/* =std::nullopt */,
					  std::optional<uint> glTex/* =std::nullopt */)
{
	if (whetherUseTexture)
	{
		if (tex == std::nullopt)
		{
			if (!m_texture.has_value())
			{
				std::cout << "Texture does not exist." << std::endl;
				tex = 0;
			}
			tex = m_texture->Get();
		}
		if (glTex == std::nullopt)
			glTex = GL_TEXTURE_2D;

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(*glTex, *tex);
	}
	glBindVertexArray(m_VAO);

	shader.Use();

	if (glDrawMode == GL_POINTS)
		glPointSize(pixelSize);
	if (glDrawMode == GL_LINES || glDrawMode == GL_LINE_STRIP || glDrawMode == GL_LINE_LOOP)
		glLineWidth(pixelSize);

	glDrawArrays(glDrawMode, 0, m_vertexCount);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(0);
}

void Geometry::Destory()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
}

unsigned int Geometry::GetVAO() const 
{ return m_VAO; }
const Geometry::GeomTexType& Geometry::GetTexture() const
{ return m_texture; }

void Geometry::SetTexture(const Texture<TextureType::_2D>& tex)
{
	m_texture = tex;
}
void Geometry::SetTexture(BITType tex)
{
	m_texture = ResourceMananger::GetInstance().LoadTexture(BIData::Textures.at(tex), MapType::DIFFUSE);
}

void Geometry::SetBuffers(BIGType geom)
{
	auto& parm = BIData::Geometries.at(geom);
	uint stride = 3;
	if (parm.normal == true)
		stride += 3;
	if (parm.texCoord == true)
		stride += 2;
	m_vertexCount = m_vertices.size() / stride;

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), m_vertices.data(), GL_STATIC_DRAW);

	int location = 0, offset = 3;
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)0);
	if (parm.normal == true)
	{
		glEnableVertexAttribArray(++location);
		glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE,
							  stride * sizeof(float), (void*)(offset * sizeof(float)));
		offset += 3;
	}
	if (parm.texCoord == true)
	{
		glEnableVertexAttribArray(++location);
		glVertexAttribPointer(location, 2, GL_FLOAT, GL_FALSE,
							  stride * sizeof(float), (void*)(offset * sizeof(float)));
		offset += 2;
	}

	glBindVertexArray(0);
}
void Geometry::SetBuffers(const std::vector<uint>& vertOffset)
{
	uint stride = 0;
	uint count = vertOffset.size();

	for (auto& i : vertOffset)
	{
		stride += i;
	}
	m_vertexCount = m_vertices.size() / stride;

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), m_vertices.data(), GL_STATIC_DRAW);
	uint offset = 0;
	for (size_t locat = 0; locat < count; locat++)
	{
		glEnableVertexAttribArray(locat);
		glVertexAttribPointer(locat, vertOffset.at(locat), GL_FLOAT, GL_FALSE,
							  stride * sizeof(float), (void*)(offset * sizeof(float)));
		offset += vertOffset.at(locat);
	}
}
