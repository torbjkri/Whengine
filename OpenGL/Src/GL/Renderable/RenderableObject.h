#pragma once


#include "glad/glad.h"
#include "GL/VertexArray.h"
#include "GL/ElementBuffer.h"
#include "GL/VertexBuffer.h"
#include "GL/Shader.h"
#include "GL/Texture.h"

#include "ObjectProperties.h"

#include <glm/glm.hpp>


struct RenderableObject {
	Shader shader_;
	
	VertexArray vao_;
	VertexBuffer vbo_;
	ElementBuffer ebo_;

	glm::vec3 position_ =  glm::vec3(0.0f, 0.0f, 0.0);
	glm::mat4 orientation_mat_ = glm::mat4(1.0f);
	float scale_ = 1.0f;

	RenderableObject(Shader shader) : shader_(shader) {}
	virtual ~RenderableObject() = default;
	virtual void InitRenderData() = 0;

	virtual void Bind() const = 0;
	virtual void Unbind() const = 0;

};
