#include "FrameBufferObject.h"

#include <assert.h>

FrameBufferObject::FrameBufferObject()
	: m_isValid(false),
	m_width(0),
	m_height(0),
	m_fboId(0),
	m_colorTexture(0),
	m_depthTexture(0),
	m_ownColorTexture(false),
	m_ownDepthTexture(false)
{

}

FrameBufferObject::~FrameBufferObject()
{
	reset();
}

void FrameBufferObject::reset()
{
	if (!m_isValid)
	{
		return;
	}

	deleteColorTexture();
	deleteDepthTexture();

	if (m_fboId != 0)
	{
		glDeleteFramebuffers(1, &m_fboId);
		m_fboId = 0;
	}

	m_width = 0;
	m_height = 0;
}

bool FrameBufferObject::init(unsigned int width, unsigned int height)
{
	if (m_isValid)
	{
		reset();
	}

	m_width = width;
	m_height = height;

	glGenFramebuffers(1, &m_fboId);

	m_isValid = (m_fboId != 0);

	return m_isValid;
}

bool FrameBufferObject::start()
{
	if (m_isValid && m_fboId != 0)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_fboId);
		return true;
	}
	else
	{
		return false;
	}
}

void FrameBufferObject::stop()
{
	if (m_isValid && m_fboId != 0)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}

void FrameBufferObject::deleteColorTexture()
{
	if (m_isValid && m_ownColorTexture && m_colorTexture != 0)
	{
		glDeleteTextures(1, &m_colorTexture);
	}
	m_colorTexture = 0;
	m_ownColorTexture = false;
}

void FrameBufferObject::deleteDepthTexture()
{
	if (m_isValid && m_ownDepthTexture && m_depthTexture != 0)
	{
		glDeleteTextures(1, &m_depthTexture);
	}
	m_depthTexture = 0;
	m_ownDepthTexture = false;
}

bool FrameBufferObject::initColor(GLint internalFormat,
	GLenum format,
	GLenum type,
	GLint minMagFilter,
	GLenum target)
{
	if (!m_isValid || m_fboId == 0)
	{
		assert(false);
		return false;
	}

	// create new texture
	unsigned int textureId = 0;
	glGenTextures(1, &textureId);
	glBindTexture(target, textureId);
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, minMagFilter);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, minMagFilter);
	glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(target, 0, internalFormat, m_width, m_height, 0, format, type, NULL);

	if (attachColor(textureId, true, target))
	{
		return true;
	}
	else
	{
		glDeleteTextures(1, &textureId);
		return false;
	}
}

bool FrameBufferObject::attachColor(unsigned int textureId,
	bool ownTexture,
	GLenum target)
{
	if (!m_isValid || m_fboId == 0 || textureId == 0)
	{
		assert(false);
		return false;
	}

	if(!start())
	{
		return false;
	}

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, target, textureId, 0);

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	stop();

	bool success = true;

	switch (status)
	{
	case GL_FRAMEBUFFER_COMPLETE:
		// remove the previous texture(if any)
		deleteColorTexture();

		// save new one
		m_colorTexture = textureId;
		m_ownColorTexture = ownTexture;
		break;
	default:
		success = false;
		break;
	}

	return success;
}

bool FrameBufferObject::initDepth(GLint warpMode, 
	GLenum internalFormat, 
	GLint minMagFilter, 
	GLenum target)
{
	if (!m_isValid || m_fboId == 0)
	{
		assert(false);
		return false;
	}

	if (!start())
	{
		return false;
	}

	unsigned int textureId = 0;
	glGenTextures(1, &textureId);
	glBindTexture(target, textureId);
	glTexParameteri(target, GL_TEXTURE_WRAP_S, warpMode);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, warpMode);
	glTexParameteri(target, GL_TEXTURE_COMPARE_MODE, GL_NONE);
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, minMagFilter);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, minMagFilter);
	glTexImage2D(target, 0, internalFormat, m_width, m_height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, nullptr);
	glBindTexture(target, 0);

	if (attachDepth(textureId, true, target))
	{
		return true;
	}
	else
	{
		glDeleteTextures(1, &textureId);
		return false;
	}
}

bool FrameBufferObject::attachDepth(GLuint textureId, bool ownTexture, GLenum target)
{

	if (!m_isValid || m_fboId == 0 || textureId == 0)
	{
		assert(false);
		return false;
	}

	if (!start())
	{
		return false;
	}

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, target, textureId, 0);
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	stop();

	bool success = true;
	switch (status)
	{
	case GL_FRAMEBUFFER_COMPLETE:
		// remove the previous texture(if any)
		deleteDepthTexture();
		// save the new one
		m_depthTexture = textureId;
		m_ownDepthTexture = ownTexture;
		break;

	default:
		success = false;
		break;
	}

	return success;
}