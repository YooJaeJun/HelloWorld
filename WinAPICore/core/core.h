#pragma once
#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
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