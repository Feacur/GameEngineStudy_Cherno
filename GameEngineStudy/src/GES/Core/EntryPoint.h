#pragma once

#if defined(GES_PLATFORM_WINDOWS)
namespace GES
{
	extern Scope<Application> CreateApplication();
}

int main(int argc, char* argv[])
{
	GES::Log::Init();

	printf("Inititialized\n");
	GES_CORE_INFO("Inititialized");
	GES_INFO("Inititialized");

	GES_PROFILE_BEGIN_SESSION("Startup", "Profile-Startup.json");
	auto app = GES::CreateApplication();
	GES_PROFILE_END_SESSION();

	GES_PROFILE_BEGIN_SESSION("Runtime", "Profile-Runtime.json");
	app->Run();
	GES_PROFILE_END_SESSION();
	
	GES_PROFILE_BEGIN_SESSION("Shutdown", "Profile-Shutdown.json");
	return 0;
	GES_PROFILE_END_SESSION();
}
#endif
