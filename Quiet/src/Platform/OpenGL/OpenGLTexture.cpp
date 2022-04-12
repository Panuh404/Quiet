#include "Quiet_pch.h"

#include "Platform/OpenGL/OpenGLTexture.h"

#include <stb_image.h>

namespace Quiet {
	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height):
		m_Width(width), m_Height(height) 
	{
		QUIET_PROFILE_FUNCTION();
		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);
		// Texture Filtering Parameters
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		// Texture Wraping Parameters
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path) :
		m_Path(path) 
	{
		QUIET_PROFILE_FUNCTION();
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = nullptr;
		{
			QUIET_PROFILE_SCOPE("stbi_load - OpenGLTexture2D::OpenGLTexture2D(const std::string&)");
			data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		}
		QUIET_CORE_ASSERT(data, "Failed to load image!");
		m_Width = width;
		m_Height = height;		
		m_Channels = channels;
		
		GLenum internalFormat = 0;
		GLenum dataFormat = 0;
		if (m_Channels == 4){
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (m_Channels == 3) {
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		m_InternalFormat = internalFormat;
		m_DataFormat = dataFormat;
		
		QUIET_CORE_ASSERT(internalFormat && dataFormat, "Unsupported format!");
		// Create Texture
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID); 
		glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height); 
		// Texture Filtering Parameters
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		// Texture Wraping Parameters
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// Uploading the image data to the GPU
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data); 
		// Free the memory
		stbi_image_free(data); 
	}

	OpenGLTexture2D::~OpenGLTexture2D() {
		QUIET_PROFILE_FUNCTION();
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size) {
		QUIET_PROFILE_FUNCTION();
		uint32_t BytesPerChannel = m_DataFormat == GL_RGBA ? 4 : 3;
		QUIET_CORE_ASSERT(size == m_Width * m_Height * BytesPerChannel, "Data must be entire texture!");
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}
	
	void OpenGLTexture2D::Bind(uint32_t slot) const {
		QUIET_PROFILE_FUNCTION();
		glBindTextureUnit(slot, m_RendererID);
	}
}