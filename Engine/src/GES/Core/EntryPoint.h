#pragma once

namespace GES
{
	GES_EXTERN Application * CreateApplication();
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

#if false && defined(GES_OS_WINDOWS)
// http://dslweb.nwnexus.com/~ast/dload/guicon.htm
// https://docs.microsoft.com/en-us/windows/console/console-handles

#include <Windows.h>
#include <fcntl.h>

FILE * WinMain_GetIoHandle(DWORD device, cstring mode) {
	intptr_t osFileHandle = (intptr_t)GetStdHandle(device);
	int fileDescriptor = _open_osfhandle(osFileHandle, _O_TEXT);
	FILE * file = _fdopen(fileDescriptor, mode);
	setvbuf(file, NULL, _IONBF, 0);
	return file;
}

void WinMain_CreateConsole() {
	if (AllocConsole()) {
		CONSOLE_SCREEN_BUFFER_INFO csbi = {};
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		csbi.dwSize.Y = 1500;
		SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), csbi.dwSize);

		// redirect unbuffered streams to the console
		*stdin  = *WinMain_GetIoHandle(STD_INPUT_HANDLE,  "r");
		*stdout = *WinMain_GetIoHandle(STD_OUTPUT_HANDLE, "w");
		*stderr = *WinMain_GetIoHandle(STD_ERROR_HANDLE,  "w");
	}
	// FreeConsole();
}

// https://docs.microsoft.com/ru-ru/windows/win32/desktop-programming
// https://docs.microsoft.com/en-us/windows/win32/dlls/dllmain
// https://docs.microsoft.com/en-us/windows/win32/learnwin32/winmain--the-application-entry-point
int WINAPI WinMain(
	HINSTANCE hInstance,     // is something called a "handle to an instance" or "handle to a module." The operating system uses this value to identify the executable (EXE) when it is loaded in memory. The instance handle is needed for certain Windows functions—for example, to load icons or bitmaps.
	HINSTANCE hPrevInstance, // has no meaning. It was used in 16-bit Windows, but is now always zero.
	PSTR      pCmdLine,      // contains the command-line arguments as an ANSI string.
	int       nCmdShow       // is a flag that says whether the main application window will be minimized, maximized, or shown normally.
) {
	WinMain_CreateConsole();
	return main(__argc, __argv);
}

// ShowWindow(GetConsoleWindow(), SW_HIDE);
// ShowWindow(GetConsoleWindow(), SW_SHOW);
#endif
