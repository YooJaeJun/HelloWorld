#pragma once
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
#include <Windows.h>
#include <memory>
#include <cassert>
#include <string>
//#include <tchar.h>
//#include <wchar.h>
// #include <stdlib.h>
// #include <malloc.h>

namespace yjj {
	typedef std::basic_string<TCHAR> tstring;
}