#pragma once

#ifndef SHELL_OPTION_H
#define SHELL_OPTION_H

#include "ShellType.h"

#define SHELL_ARGUMENTS(x)	uint32_t(x)
#define SHELL_NOARGUMENT	SHELL_ARGUMENTS(0)
#define SHELL_ARGREQUIRE	SHELL_ARGUMENTS(1)
#define SHELL_ARGOPTIONAL	SHELL_ARGUMENTS(-1)

#define SHELL_OPTSTATUS(x)	uint32_t(x)
#define SHELL_OPTFINISH		SHELL_OPTSTATUS(-1) // End of cmdline.
#define SHELL_OPTIGNORE		SHELL_OPTSTATUS(-2) // Finded rule but invalid arguments.
#define SHELL_OPTUNKNOWN	SHELL_OPTSTATUS(-3) // Rule not found.
#define SHELL_OPTNORMAL		SHELL_OPTSTATUS(-4) // Normal

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
	TYPEHANDLE(ShellOptionStoreA);
	TYPEHANDLE(ShellOptionStoreW);
	typedef struct ShellOptionRuleA {
		const char* Name;
		uint32_t Args;
		uint32_t Identifier;
	} OptRuleA;
	typedef struct ShellOptionRuleW {
		const wchar_t* Name;
		uint32_t Args;
		uint32_t Identifier;
	} OptRuleW;

	SHELL_EXPORT ShellOptionStoreA ShellCreateOptionStoreA(int argc, const char** argv);
	SHELL_EXPORT ShellOptionStoreW ShellCreateOptionStoreW(int argc, const wchar_t** argv);
	SHELL_EXPORT uint32_t ShellAnalyzeOptionStoreA(ShellOptionStoreA OptionStore, ShellOptionRuleA* Rules);
	SHELL_EXPORT uint32_t ShellAnalyzeOptionStoreW(ShellOptionStoreW OptionStore, ShellOptionRuleW* Rules);
	SHELL_EXPORT const char* ShellGetKeyNameA(ShellOptionStoreA OptionStore);
	SHELL_EXPORT const wchar_t* ShellGetKeyNameW(ShellOptionStoreW OptionStore);
	SHELL_EXPORT const char* ShellGetResultA(ShellOptionStoreA OptionStore, uint32_t Index);
	SHELL_EXPORT const wchar_t* ShellGetResultW(ShellOptionStoreW OptionStore, uint32_t Index);
	SHELL_EXPORT void ShellReleaseOptionStoreA(ShellOptionStoreA OptionStore);
	SHELL_EXPORT void ShellReleaseOptionStoreW(ShellOptionStoreW OptionStore);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !SHELL_OPTION_H
