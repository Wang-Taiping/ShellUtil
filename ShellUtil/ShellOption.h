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
	SHELL_TYPENAME(ShellOptionStoreA);
	SHELL_TYPENAME(ShellOptionStoreW);
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

	SHELL_EXPORT ShellOptionStoreA SHELL_API ShellCreateOptionStoreA(int argc, const char** argv);
	SHELL_EXPORT ShellOptionStoreW SHELL_API ShellCreateOptionStoreW(int argc, const wchar_t** argv);
	SHELL_EXPORT uint32_t SHELL_API ShellAnalyzeOptionStoreA(ShellOptionStoreA OptionStore, ShellOptionRuleA* Rules);
	SHELL_EXPORT uint32_t SHELL_API ShellAnalyzeOptionStoreW(ShellOptionStoreW OptionStore, ShellOptionRuleW* Rules);
	SHELL_EXPORT const char* SHELL_API ShellGetKeyNameA(ShellOptionStoreA OptionStore);
	SHELL_EXPORT const wchar_t* SHELL_API ShellGetKeyNameW(ShellOptionStoreW OptionStore);
	SHELL_EXPORT const char* SHELL_API ShellGetResultA(ShellOptionStoreA OptionStore, uint32_t Index);
	SHELL_EXPORT const wchar_t* SHELL_API ShellGetResultW(ShellOptionStoreW OptionStore, uint32_t Index);
	SHELL_EXPORT void SHELL_API ShellReleaseOptionStoreA(ShellOptionStoreA OptionStore);
	SHELL_EXPORT void SHELL_API ShellReleaseOptionStoreW(ShellOptionStoreW OptionStore);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !SHELL_OPTION_H
