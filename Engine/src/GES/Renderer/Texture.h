#pragma once
#include "GES/Core/Code.h"

namespace GES
{
	class Texture
	{
	public:
		virtual ~Texture() = default;

	public:
		virtual u32 GetWidth() const = 0;
		virtual u32 GetHeight() const = 0;
		virtual u32 GetSlot() const = 0;
		
		virtual void SetData(void * data, u32 size) = 0;

		virtual void Bind(u32 slot) const = 0;
		virtual void Unbind(u32 slot) const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		virtual ~Texture2D() = default;

	public:
		static Ref<Texture2D> Texture2D::CreateRaw(u32 width, u32 height);
		static Ref<Texture2D> Texture2D::CreatePath(cstring source);
	};
}
