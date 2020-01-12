#pragma once
#include "GES/Renderer/Texture.h"

namespace GES
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(u32 width, u32 height);
		OpenGLTexture2D(cstring source);
		~OpenGLTexture2D() override;

	public:
		u32 GetWidth() const override { return m_Width; }
		u32 GetHeight() const override { return m_Height; }
		u32 GetSlot() const override { return m_Slot; }
		
		void SetData(void * data, u32 size) override;

		void Bind(u32 slot) const override;
		void Unbind(u32 slot) const override;

	private:
		u32 m_RendererID;
		u32 m_Width, m_Height;
		u32 m_InternalFormat, m_DataFormat;
		u32 mutable m_Slot;
	};
}
