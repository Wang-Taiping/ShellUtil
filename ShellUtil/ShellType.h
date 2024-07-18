#pragma once

#ifndef SHELL_TYPE_H
#define SHELL_TYPE_H

#include <stdint.h>

#ifdef SHELL_EXPORT
#undef SHELL_EXPORT
#endif // SHELL_EXPORT
#ifdef SHELL_BUILD
#define SHELL_EXPORT __declspec(dllexport)
#else
#define SHELL_EXPORT __declspec(dllimport)
#endif // SHELL_BUILD

#define TYPEHANDLE(name)	typedef struct __##name { int unused; } *name

#define MAX_ARRAY_ELEM	2048
#define MAX_STRING_ELEM	65536

typedef void* ShellHandle;
typedef char ShellBool;

#endif // !SHELL_TYPE_H
