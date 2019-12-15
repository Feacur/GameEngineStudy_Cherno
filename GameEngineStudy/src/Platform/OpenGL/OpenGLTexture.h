#pragma once
#include "GES/Renderer/Texture.h"

namespace GES
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(cstring source);
		~OpenGLTexture2D() override;

	public:
		uint32 GetWidth() const override { return m_Width; }
		uint32 GetHeight() const override { return m_Height; }
		uint32 GetSlot() const override { return m_Slot; }

		void Bind(uint32 slot) const override;
		void Unbind(uint32 slot) const override;

	private:
		uint32 m_RendererID;
		uint32 m_Width, m_Height;
		uint32 mutable m_Slot;
	};
}
