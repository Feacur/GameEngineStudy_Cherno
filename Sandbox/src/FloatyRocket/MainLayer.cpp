#include "MainLayer.h"

#include <imgui.h>
#include <lua.hpp>

namespace FloatyRocket
{
	static bool CheckLua(lua_State * L, int32 result)
	{
		if (result == LUA_OK) { return true; }
		cstring errorMessage = lua_tostring(L, -1);
		GES_ERROR("Lua error: '{0}'", errorMessage);
		return false;
	}
	
	static int32 NativeCustomAdd(lua_State * L)
	{
		LUA_NUMBER a = lua_tonumber(L, -1);
		LUA_NUMBER b = lua_tonumber(L, -2);
		lua_pushnumber(L, a + b);
		return 1;
	}

	static void TestLua()
	{
		lua_State *L = luaL_newstate();

		// luaL_openlibs(L);
		luaL_requiref(L, "_G", luaopen_base, 1);
		lua_pop(L, 1);
		luaL_requiref(L, LUA_STRLIBNAME, luaopen_string, 1);
		lua_pop(L, 1);

		lua_register(L, "NativeCustomAdd", NativeCustomAdd);

		// luaL_dostring(L, "a = 7 + 11");
		if (CheckLua(L, luaL_dofile(L, "assets/scripts/test.lua")))
		{
			lua_getglobal(L, "CustomAdd");
			if (lua_isfunction(L, -1))
			{
				lua_pushnumber(L, 3.5f);
				lua_pushnumber(L, 7.125f);
				if (CheckLua(L, lua_pcall(L, 2, 1, 0)))
				{
					GES_TRACE("[Native] 'CustomAdd' result: '{0}'", lua_tonumber(L, -1));
					lua_pop(L, 1);
				}
			}
			lua_pop(L, 1);
			
			lua_getglobal(L, "CallNativeCustomAdd");
			if (lua_isfunction(L, -1))
			{
				lua_pushnumber(L, 2.5f);
				lua_pushnumber(L, 10.125f);
				CheckLua(L, lua_pcall(L, 2, 1, 0));
			}
			lua_pop(L, 1);
			
			lua_getglobal(L, "entity");
			if (lua_istable(L, -1))
			{
				lua_pushstring(L, "id");
				lua_gettable(L, -2);
				GES_TRACE("[Native] 'entity.id': '{0}'", lua_tointeger(L, -1));
				lua_pop(L, 1);
				
				lua_pushstring(L, "name");
				lua_gettable(L, -2);
				GES_TRACE("[Native] 'entity.name': '{0}'", lua_tostring(L, -1));
				lua_pop(L, 1);
			}
			lua_pop(L, 1);
		}

		lua_close(L);
	}

	MainLayer::MainLayer()
		: Layer("MainLayer")
		, m_Camera(-16.0f, 16.0f, -9.0f, 9.0f)
		, m_ParticleSystem(1024)
	{
		GES_PROFILE_FUNCTION();
		m_Player.Reset();
		m_Level.Reset();
	}

	void MainLayer::OnAttach()
	{
		GES_PROFILE_FUNCTION();
		m_PlayerTexture = GES::Texture2D::CreatePath("assets/textures/ship.png");
		m_LevelTexture = GES::Texture2D::CreatePath("assets/textures/triangle.png");
		m_PostVignetteProcedural = GES::Shader::CreatePath("assets/shaders/post_vignette_procedural.glsl");
		m_PostVignette = GES::Shader::CreatePath("assets/shaders/post_vignette.glsl");
		m_NoiseTexture = GES::Texture2D::CreatePath("assets/textures/blue_noise.png");
		TestLua();
	}

	void MainLayer::OnDetach()
	{
		GES_PROFILE_FUNCTION();
		m_PlayerTexture = nullptr;
		m_LevelTexture = nullptr;
		m_PostVignetteProcedural = nullptr;
		m_PostVignette = nullptr;
		m_NoiseTexture = nullptr;
	}

	void MainLayer::OnUpdate(GES::Timestep ts)
	{
		GES_PROFILE_FUNCTION();

		if (m_Level.IsCollision())
		{
			if (GES::Input::IsKeyPressed(GES_KEY_ESCAPE))
			{
				m_Player.Reset();
				m_Level.Reset();
			}
		}

		if (!m_Level.IsCollision())
		{
			m_Player.OnUpdate(ts, m_ParticleSystem);

			glm::vec3 cameraPosition(m_Player.GetPosition(), 0.0f);
			m_Camera.SetPosition(cameraPosition);
			m_Camera.RecalculateViewMatrix();
		}

		m_Level.OnUpdate(ts, m_Player.GetPosition(), m_Player.GetRotation());
		m_ParticleSystem.OnUpdate(ts);

		// Render
		{
			GES_PROFILE_SCOPE("Renderer -> clear");
			GES::RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			GES::RendererCommand::Clear();
		}

		{
			GES_PROFILE_SCOPE("Renderer -> draw");
			GES::Renderer2D::BeginScene(m_Camera);
			m_Level.OnRender(m_LevelTexture, m_Player.GetPosition());
			m_ParticleSystem.OnRender();
			m_Player.OnRender(m_PlayerTexture);

			GES::Window & window = GES::Application::Get().GetWindow();
			glm::vec2 screenSize((float)window.GetWidth(), (float)window.GetHeight());
			// GES::Renderer2D::DrawPost(m_PostVignetteProcedural, screenSize, {0.0f, 0.0f, 0.0f, 0.5f});
			GES::Renderer2D::DrawPost(m_PostVignette, screenSize, {0.0f, 0.0f, 0.0f, 0.5f}, m_NoiseTexture);

			GES::Renderer2D::EndScene();
		}
	}

	void MainLayer::OnImGuiRender()
	{
		GES_PROFILE_FUNCTION();
	}

	void MainLayer::OnEvent(GES::Event& e)
	{
		GES_PROFILE_FUNCTION();
	}


	bool MainLayer::OnWindowResized(GES::WindowResizeEvent const & e)
	{
		GES_PROFILE_FUNCTION();
		float aspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		float zoomLevel = 10.0f;
		m_Camera.SetProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
		return false;
	}
}
