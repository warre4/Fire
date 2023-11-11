#pragma once


#include <concepts>
#include <cstdint>
#include <string>
#include <stdexcept>
#include <iostream> // cout for logging

constexpr char ENGINE_NAME[] = "Fire";
constexpr char ENGINE_INITIALS[] = "F";


// ----------------------------------------------------------------------------------------------
// NAMESPACES
// ----------------------------------------------------------------------------------------------

#define _F ::Fire::


// ----------------------------------------------------------------------------------------------
// GENERAL
// ----------------------------------------------------------------------------------------------

#define STR(s) std::string(s)
#define WSTR(ws) std::wstring(ws)

// remove unreferenced parameter warning for this parameter
#define UNREF_PARAM(parameter) (void)parameter

// delete memory and remove dangling pointer
#define SAFE_DELETE(ptr) delete ptr; ptr = nullptr


// ----------------------------------------------------------------------------------------------
// LOGGING
// ----------------------------------------------------------------------------------------------

constexpr const char* LOG_COLOR_RESET_COLOR = "\033[0m";
constexpr const char* LOG_COLOR_BLACK       = "\033[30m";
constexpr const char* LOG_COLOR_RED         = "\033[31m";
constexpr const char* LOG_COLOR_GREEN       = "\033[32m";
constexpr const char* LOG_COLOR_YELLOW      = "\033[33m";
constexpr const char* LOG_COLOR_BLUE        = "\033[34m";
constexpr const char* LOG_COLOR_MAGENTA     = "\033[35m";
constexpr const char* LOG_COLOR_CYAN        = "\033[36m";
constexpr const char* LOG_COLOR_WHITE       = "\033[37m";

// Set log color (mostly for LOG_RAW usage)
#define LOG_SET_COLOR(logColorMacro) std::cout << logColorMacro
// Log without any pre or postfix
#define LOGRAW(data)        std::cout << data
// Log an empty line
#define LOG_EMPTY_LINE()     std::cout << "\n"
// Log trace (color: blue)
#define LOGT(message)        std::cout << LOG_COLOR_CYAN   << "[Trace] "          << message << "\n"
#ifdef _DEBUG
// Log debug (color: white)
#define LOGD(message)        std::cout << LOG_COLOR_WHITE  << "[Debug] "          << message << "\n"
#else
// Log debug (empty in release mode)
#define LOGD(message)
#endif
// Log info (color: white)
#define LOGI(message)        std::cout << LOG_COLOR_WHITE  << "[Info]  "          << message << "\n"
// Log warning (color: yellow)
#define LOGWARN(message)     std::cout << LOG_COLOR_YELLOW << "[Warning] "        << message << "\n"
// Log error (color: red)
#define LOGERROR(message)    std::cout << LOG_COLOR_RED    << "[Error] "          << message << "\n"
// Log critical error (color: red)
#define LOGCRITICAL(message) std::cout << LOG_COLOR_RED    << "[" << LOG_COLOR_YELLOW << "Critical Error" << LOG_COLOR_RED << "] " << message << "\n"



// ----------------------------------------------------------------------------------------------
// EXCEPTIONS
// ----------------------------------------------------------------------------------------------

#define EXCEPTION(message) throw std::exception((    STR(ENGINE_NAME) + STR(": ") + message).c_str())
//Runtime error
#define RTE(message)       throw std::runtime_error((STR(ENGINE_NAME) + STR(": ") + message).c_str())


// ----------------------------------------------------------------------------------------------
// VULKAN
// ----------------------------------------------------------------------------------------------

// Put this over a function that produces a VkResult to check the result
#define CHECK(vkResult, message)                                                                \
{                                                                                               \
	VkResult temporaryResultInMacro = vkResult;                                                 \
	if (temporaryResultInMacro != VK_SUCCESS)                                                   \
		RTE(STR(message) + " \nError: " + std::to_string(int(temporaryResultInMacro)));         \
}


// ----------------------------------------------------------------------------------------------
// TYPEDEFS
// ----------------------------------------------------------------------------------------------

typedef unsigned char Byte;


// ----------------------------------------------------------------------------------------------
// ENUMS
// ----------------------------------------------------------------------------------------------

namespace Fire
{
	// add enums here

	
}