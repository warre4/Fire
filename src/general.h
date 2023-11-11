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

// Log without any pre or postfix
#define LOG_RAW(data)        std::cout << data
// Log an empty line
#define LOG_EMPTY_LINE()     std::cout << "\n"
// Log trace
#define LOGT(message)        std::cout << "[Trace] "          << message << "\n"
#ifdef _DEBUG
// Log debug
#define LOGD(message)        std::cout << "[Debug] "          << message << "\n"
#else
// Log debug (empty in release mode)
#define LOGD(message)
#endif
// Log info
#define LOGI(message)        std::cout << "[Info]  "          << message << "\n"
#define LOGWARN(message)     std::cout << "[Warning] "        << message << "\n"
#define LOGERROR(message)    std::cout << "[Error] "          << message << "\n"
#define LOGCRITICAL(message) std::cout << "[Critical Error] " << message << "\n"



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