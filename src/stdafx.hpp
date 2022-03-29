#include <codecvt>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <future>
#include <iomanip>
#include <locale>
#include <map>
#include <sstream>
#include <string>

#include <ISmmPlugin.h>
#include <igameevents.h>
#include <iplayerinfo.h>
#include <sh_vector.h>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

#ifdef null
#undef null
#endif

#undef and
#undef or

// Remove min/max definitions from some SDK versions
#undef min
#undef max