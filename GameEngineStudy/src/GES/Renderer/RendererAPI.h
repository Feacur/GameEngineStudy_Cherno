#pragma once

namespace GES
{
	class RendererAPI
	{
	public:
		enum class Type
		{
			None   = 0,
			OpenGL = 1,
		};

	public:
		inline static Type GetType() { return s_Type; }

	private:
		static Type s_Type;
	};
}
