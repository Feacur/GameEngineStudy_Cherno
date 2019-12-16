#include "ges_pch.h"
#include "OpenGLTexture.h"

#include <stb_image.h>

#include <glad/glad.h>

namespace GES
{
	OpenGLTexture2D::OpenGLTexture2D(cstring source)
	{
		int32 width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc * data = stbi_load(source, &width, &height, &channels, 0);
		GES_CORE_ASSERT(data, "Failed to load image");

		m_Width = width;
		m_Height = height;

		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 3) {
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}
		else if (channels == 4) {
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else {
			GES_CORE_ASSERT(false, "Failed to select image format");
		}

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalFormat, width, height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::Bind(uint32 slot) const
	{
		m_Slot = slot;
		glBindTextureUnit(slot, m_RendererID);
	}

	void OpenGLTexture2D::Unbind(uint32 slot) const
	{
		m_Slot = slot;
		glBindTextureUnit(slot, 0);
	}
}
