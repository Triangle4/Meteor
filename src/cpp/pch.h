# pragma once

#include <windows.h>

#include "../h/resource.h"

#define MAX_NAME_LENGTH 256 // Used simply to make the codre more readable
#define HInstance() GetModuleHandle(NULL) // Used to call back our HINSTANCE