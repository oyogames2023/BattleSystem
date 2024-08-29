#if defined(_WIN32) || defined(_WIN64)
    // Windows 平台
    #if defined(BATTLE_EXPORTS)
        #define BATTLE_API __declspec(dllexport)
    #else
        #define BATTLE_API __declspec(dllimport)
    #endif
#else
    // Linux 和其他 Unix-like 系统
    #if defined(BATTLE_EXPORTS)
        #define BATTLE_API __attribute__((visibility("default")))
    #else
        #define BATTLE_API
    #endif
#endif