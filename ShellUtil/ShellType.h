#pragma once

#ifndef SHELL_TYPE_H
#define SHELL_TYPE_H

#include <stdint.h>

#ifdef SHELL_EXPORT
#error Macro 'SHELL_EXPORT' already defined.
#endif // SHELL_EXPORT

#ifdef SHELL_BUILD
#define SHELL_EXPORT	__declspec(dllexport)
#else
#define SHELL_EXPORT	__declspec(dllimport)
#endif // SHELL_BUILD

#ifdef SHELL_STATIC
#undef SHELL_EXPORT
#define SHELL_EXPORT
#endif // SHELL_STATIC

#define SHELL_API		__stdcall
#define SHELL_CALLBACK	__stdcall

#define SHELL_TYPENAME(name)	struct __##name { int unused; }; typedef struct __##name* name

#define MAX_ARRAY_ELEM	2048
#define MAX_STRING_ELEM	65536

typedef void* ShellHandle;
typedef char ShellBool;

#endif // !SHELL_TYPE_H
