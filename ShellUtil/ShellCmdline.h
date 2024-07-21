#pragma once

#ifndef SHELL_CMDLINE_H
#define SHELL_CMDLINE_H

#include "ShellType.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
	SHELL_EXPORT const char** SHELL_API ShellSplitCmdlineA(const char* Cmdline);
	SHELL_EXPORT void SHELL_API ShellReleaseCmdlineA(const char** Cmdline);
	SHELL_EXPORT const wchar_t** SHELL_API ShellSplitCmdlineW(const wchar_t* Cmdline);
	SHELL_EXPORT void SHELL_API ShellReleaseCmdlineW(const wchar_t** Cmdline);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !SHELL_CMDLINE_H
