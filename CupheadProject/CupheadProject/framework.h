// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <atlImage.h>

#include <ctime>

#define WORLD_START_POINT_X 0
#define WORLD_START_POINT_Y 700

#define MOVE_DISTANCE 5

#define WINDOWS_WIDTH 1280
#define WINDOWS_HEIGHT 800

#define LAST_FORWARD_IS_RIGHT 1
#define LAST_FORWARD_IS_LEFT 0
#define STAGE_READY_TIME 2300

// >> : for gid+
#include <objidl.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment(lib, "Gdiplus.lib")
