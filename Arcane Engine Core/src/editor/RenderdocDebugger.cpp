#include "pch.h"
#include "RenderdocDebugger.h"

RenderdocDebugger::RenderdocDebugger()
{
	// Setup renderdoc api
#ifdef _DEBUG
	// PS: Make sure your using the right bit version for your dlls
	// For android replace librenderdoc.so with libVkLayer_GLES_RenderDoc.so
	std::string dir = std::filesystem::current_path().string();
	pRENDERDOC_GetAPI RENDERDOC_GetAPI;
	void* mod = nullptr;

#ifdef _WIN32
	mod = LoadLibrary("renderdoc.dll");
#elif (__Linux__)	
	mod = dlopen("librenderdoc.so", RTLD_NOW | RTLD_NOLOAD);
#endif

	if (!mod)
		return 0;

#ifdef _WIN32
	RENDERDOC_GetAPI = (pRENDERDOC_GetAPI)GetProcAddress((HMODULE)mod, "RENDERDOC_GetAPI");
#elif (__linux__)	
	RENDERDOC_GetAPI = (pRENDERDOC_GetAPI)dlsym(mod, "RENDERDOC_GetAPI");
#endif

	int ret = RENDERDOC_GetAPI(eRENDERDOC_API_Version_1_4_0, (void**)&m_RenderdocApi);
	assert(ret == 1);

	m_RenderdocApi->SetLogFilePathTemplate((dir + "/logs/").c_str());
#endif
}

void RenderdocDebugger::startScreenCapture()
{
	// To start a frame capture, call StartFrameCapture.
	// You can specify NULL, NULL for the device to capture on if you have only one device and
	// either no windows at all or only one window, and it will capture from that device.
	// See the documentation below for a longer explanation
	m_RenderdocApi->StartFrameCapture(NULL, NULL);
}

void RenderdocDebugger::endScreenCapture()
{
	// Stop screen capture
	m_RenderdocApi->EndFrameCapture(NULL, NULL);
}