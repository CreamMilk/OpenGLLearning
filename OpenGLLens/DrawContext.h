#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct DrawContext
{
	int glHeight;
	int glWidth;

	glm::mat4 viewMatrix;

	DrawContext()
		: glHeight(0)
		, glWidth(0)
		, viewMatrix(glm::mat4(1.0f))
	{

	}
};