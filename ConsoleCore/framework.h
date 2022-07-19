#pragma once
#include <windows.h>
#include <iostream>
#include <vector>
#include <cassert>
#include <ctime>
#include <conio.h>
#include <malloc.h>

#include "Screen.h"
#include "Fps.h"
#include "Color.h"
#include "Coord.h"

using namespace std;

static int g_nScreenIndex;
static HANDLE g_hScreen[2];