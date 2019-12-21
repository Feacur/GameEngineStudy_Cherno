#pragma once

#if defined(GES_PLATFORM_WINDOWS)
extern GES::Ref<GES::Application> GES::CreateApplication();

int main(int argc, char* argv[])
{
	GES::Log::Init();

	GES_CORE_INFO("Inititialized");
	GES_INFO("Inititialized");

	printf("Welcome to this study!\n");
	auto app = GES::CreateApplication();
	app->Run();
	return 0;
}
#endif
