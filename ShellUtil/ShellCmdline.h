#pragma once

#ifndef SHELL_CMDLINE_H
#define SHELL_CMDLINE_H

#include "ShellType.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
	SHELL_EXPORT const char** ShellSplitCmdlineA(const char* Cmdline);
	SHELL_EXPORT void ShellReleaseCmdlineA(const char** Cmdline);
	SHELL_EXPORT const wchar_t** ShellSplitCmdlineW(const wchar_t* Cmdline);
	SHELL_EXPORT void ShellReleaseCmdlineW(const wchar_t** Cmdline);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !SHELL_CMDLINE_H
