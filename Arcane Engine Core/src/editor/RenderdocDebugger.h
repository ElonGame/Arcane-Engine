#pragma once

class RenderdocDebugger
{
public:
	RenderdocDebugger();
	~RenderdocDebugger() = default;

	RENDERDOC_API_1_4_0* m_RenderdocApi;
	
	void startScreenCapture();
	void endScreenCapture();
};