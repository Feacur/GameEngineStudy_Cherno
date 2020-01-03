#pragma once
#include "GES/Core/Code.h"

namespace GES
{
	class Texture
	{
	public:
		virtual ~Texture() = default;

	public:
		virtual uint32 GetWidth() const = 0;
		virtual uint32 GetHeight() const = 0;
		virtual uint32 GetSlot() const = 0;
		
		virtual void SetData(void * data, uint32 size) = 0;

		virtual void Bind(uint32 slot) const = 0;
		virtual void Unbind(uint32 slot) const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		virtual ~Texture2D() = default;

	public:
		static Ref<Texture2D> Texture2D::CreateRaw(uint32 width, uint32 height);
		static Ref<Texture2D> Texture2D::CreatePath(cstring source);
	};
}
