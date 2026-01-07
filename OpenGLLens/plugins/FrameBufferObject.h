#pragma once

#include <glad/glad.h>

class FrameBufferObject
{
public:
	FrameBufferObject();
	~FrameBufferObject();

	bool init(unsigned int width, unsigned int height);
	void reset();
	bool start();
	void stop();

	inline bool isValid() const { return m_fboId; }

	bool initColor(GLint internalFormat = GL_RGBA,
		GLenum format = GL_RGBA,
		GLenum type = GL_UNSIGNED_BYTE,
		GLint minMagFilter = GL_NEAREST,
		GLenum target = GL_TEXTURE_2D);

	bool attachColor(unsigned int textureId,
		bool ownTexture = false,
		GLenum target = GL_TEXTURE_2D);

	bool initDepth(GLint warpMode = GL_CLAMP_TO_BORDER,
		GLenum internalFormat = GL_DEPTH_COMPONENT32F,
		GLint minMagFilter = GL_NEAREST,
		GLenum target = GL_TEXTURE_2D);

	bool attachDepth(GLuint textureId, 
		bool ownTexture = false,
		GLenum target = GL_TEXTURE_2D);

	inline unsigned int getID() const { return m_fboId; }
	inline unsigned int getColorTexture() const { return m_colorTexture; }
	inline unsigned int getDepthTexture() const { return m_depthTexture; }

	inline unsigned int width() const { return m_width; }
	inline unsigned int height() const { return m_height; }

protected:

	void deleteColorTexture();
	void deleteDepthTexture();	

private:

	bool m_isValid;

	unsigned int m_width;

	unsigned int m_height;

	unsigned int m_fboId;

	unsigned int m_colorTexture;

	unsigned int m_depthTexture;

	bool m_ownColorTexture;

	bool m_ownDepthTexture;


};

