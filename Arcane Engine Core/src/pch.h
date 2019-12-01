#pragma once

#include <cmath>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <deque>
#include <unordered_map>
#include <array>
#include <set>
#include <iterator>
#include <fstream>
#include <random>
#include <filesystem>

#include <gl/glew.h>

#include <GLFW/glfw3.h>

#include <stb_image_aug.h>

#include <SOIL.h>

#include <glm/glm.hpp>
#include <glm/common.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>
#include <vendor/imgui/include/imgui_impl_opengl3.h>
#include <vendor/imgui/include/imgui_impl_glfw.h>

#include <spdlog/spdlog.h>
#include <spdlog/logger.h>
#include <spdlog/sinks/basic_file_sink.h>

#include "runtime/renderer/Defs.h"
#include "editor/utils/Logger.h"


#ifdef _DEBUG

// CRT Memory debugger
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define DBG_NEW new (_NORMAL_BLOCK , __FILE__ , __LINE__)
#define new DBG_NEW

// Adding renderdoc api
#include <renderdoc/api/app/renderdoc_app.h>

#ifdef _WIN32
#include <Windows.h>
#elif (__linux__)
#include <dlfcn.h>
#endif
#endif

