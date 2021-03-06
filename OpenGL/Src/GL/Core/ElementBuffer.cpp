#include "ElementBuffer.h"
#include <glad/glad.h>
#include <vector>

#include <GL/Core/VerticeStructs.h>

ElementBuffer::ElementBuffer(std::vector<GLuint>& indices)
	: m_RendererID(0)
	, m_NumElements(indices.size())
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), indices.data(), GL_STATIC_DRAW);
}


ElementBuffer::ElementBuffer(const std::vector<TriangleIndices>& indices)
	: m_RendererID(0)
	, m_NumElements(indices.size() * 3)
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), indices.data(), GL_STATIC_DRAW);
}


void ElementBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void ElementBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int ElementBuffer::NumElements()
{
	return m_NumElements;
}

