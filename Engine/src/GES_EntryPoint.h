#pragma once

#if defined(GES_OS_WINDOWS)
namespace GES
{
	extern Application * CreateApplication();
}

int main(int argc, char* argv[])
{
	GES::Log::Init();

	printf("Inititialized\n");
	GES_CORE_INFO("Inititialized");
	GES_INFO("Inititialized");

	GES_PROFILE_SET_ENABLED(true);
	GES_PROFILE_BEGIN_SESSION("Startup", "profiler_startup.json");
	GES::Application * app = GES::CreateApplication();
	GES_PROFILE_END_SESSION();

	GES_PROFILE_SET_ENABLED(false);
	GES_PROFILE_BEGIN_SESSION("Runtime", "profiler_runtime.json");
	app->Run();
	GES_PROFILE_END_SESSION();
	
	GES_PROFILE_SET_ENABLED(true);
	GES_PROFILE_BEGIN_SESSION("Shutdown", "profiler_shutdown.json");
	delete app;
	GES_PROFILE_END_SESSION();

	return 0;
}
#endif
