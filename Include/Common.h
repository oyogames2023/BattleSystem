#pragma once

#include "BattleConfig.h"

#include <string>
#include <cstdint>
#include <iostream>
#include <strstream>
#include <fstream>
#include <filesystem>
#include <locale>
#include <codecvt>
#include <regex>

#include <map>
#include <vector>
#include <set>
#include <deque>
#include <list>
#include <array>
#include <queue>
#include <unordered_map>
#include <unordered_set>

#include <memory>
#include <utility>
#include <type_traits>
#include <typeinfo>
#include <functional>
#include <algorithm>
#include <cmath>
#include <limits>
#include <mutex>
#include <thread>
#include <chrono>
#include <assert.h>

#include "uv.h"


#define ASSERT_WITH_LOG(condition, format, ...) \
    do { \
        if (!(condition)) { \
            char buffer[1024]; \
            std::snprintf(buffer, sizeof(buffer), (format), ##__VA_ARGS__); \
            std::cerr << "Assertion failed: " << buffer << std::endl; \
            assert(condition); \
        } \
    } while (false)
