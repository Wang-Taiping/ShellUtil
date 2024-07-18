#include "ShellCmdline.h"
#include <string.h>
#include <ctype.h>

const char** ShellSplitCmdlineA(const char* Cmdline)
{
	if (!Cmdline) return nullptr;
	char** arrtmp = new char* [MAX_ARRAY_ELEM];
	char* strtmp = new char[MAX_STRING_ELEM];
	char** result = nullptr;
	size_t i = 0, j = 0, k = 0;
	bool dq = false, sq = false, bs = false;
	memset(arrtmp, 0, sizeof(char*) * MAX_ARRAY_ELEM);
	while (Cmdline[i] != 0) {
		if (isspace(Cmdline[i])) {
			if (dq || sq) {
				if (k < MAX_STRING_ELEM - 1) {
					strtmp[k] = Cmdline[i];
					k++;
				}
				else goto fail;
			}
			else if (k != 0 && j < MAX_ARRAY_ELEM - 1) {
				arrtmp[j] = new char[k + 1];
				strncpy_s(arrtmp[j], k + 1, strtmp, k);
				arrtmp[j][k] = 0;
				k = 0;
				j++;
			}
			else if (j >= MAX_ARRAY_ELEM - 1) goto fail;
		}
		else if (Cmdline[i] == '\\') {
			if (!dq) {
				if (k < MAX_STRING_ELEM - 1) {
					strtmp[k] = Cmdline[i];
					k++;
				}
				else goto fail;
			}
			else if (!bs) bs = true;
			else if (k < MAX_STRING_ELEM - 1) {
				strtmp[k] = Cmdline[i];
				k++;
				bs = false;
			}
			else goto fail;
		}
		else if (Cmdline[i] == '"') {
			if (sq || bs) {
				if (k < MAX_STRING_ELEM - 1) {
					strtmp[k] = Cmdline[i];
					k++;
					bs = false;
				}
				else goto fail;
			}
			else dq = !dq;
		}
		else if (Cmdline[i] == '\'') {
			if (dq) {
				if (k < MAX_STRING_ELEM - 1) {
					strtmp[k] = Cmdline[i];
					k++;
				}
				else goto fail;
			}
			else sq = !sq;
		}
		else if (bs) {
			if (k < MAX_STRING_ELEM - 1) {
				switch (Cmdline[i])
				{
				case 'a':
					strtmp[k] = '\a';
					break;
				case 'b':
					strtmp[k] = '\b';
					break;
				case 'f':
					strtmp[k] = '\f';
					break;
				case 'r':
					strtmp[k] = '\r';
						break;
				case 'n':
					strtmp[k] = '\n';
					break;
				case 't':
					strtmp[k] = '\t';
					break;
				case 'v':
					strtmp[k] = '\v';
					break;
				default:
					goto fail;
				}
				k++;
			}
			else goto fail;
			bs = false;
		}
		else if (k < MAX_STRING_ELEM - 1) {
			strtmp[k] = Cmdline[i];
			k++;
		}
		else goto fail;
		i++;
	}
	if (dq || sq) goto fail;
	else if (k != 0 && j < MAX_ARRAY_ELEM - 1) {
		arrtmp[j] = new char[k + 1];
		strncpy_s(arrtmp[j], k + 1, strtmp, k);
		arrtmp[j][k] = 0;
		k = 0;
		j++;
	}
	else if (j >= MAX_ARRAY_ELEM - 1) goto fail;
	delete[] strtmp;
	result = new char* [j + 1];
	for (size_t p = 0; p < j; p++) result[p] = arrtmp[p];
	result[j] = nullptr;
	delete[] arrtmp;
	return (const char**)result;
fail:
	for (size_t p = 0; p < j; p++) delete[] arrtmp[p];
	delete[] arrtmp;
	return nullptr;
}

void ShellReleaseCmdlineA(const char** Cmdline)
{
	if (!Cmdline) return;
	char** arrtmp = (char**)Cmdline;
	size_t i = 0;
	while (arrtmp[i] != nullptr) delete[] arrtmp[i];
	delete[] arrtmp;
}

const wchar_t** ShellSplitCmdlineW(const wchar_t* Cmdline)
{
	if (!Cmdline) return nullptr;
	wchar_t** arrtmp = new wchar_t* [MAX_ARRAY_ELEM];
	wchar_t* strtmp = new wchar_t[MAX_STRING_ELEM];
	wchar_t** result = nullptr;
	size_t i = 0, j = 0, k = 0;
	bool dq = false, sq = false, bs = false;
	memset(arrtmp, 0, sizeof(wchar_t*) * MAX_ARRAY_ELEM);
	while (Cmdline[i] != 0) {
		if (isspace(Cmdline[i])) {
			if (dq || sq) {
				if (k < MAX_STRING_ELEM - 1) {
					strtmp[k] = Cmdline[i];
					k++;
				}
				else goto fail;
			}
			else if (k != 0 && j < MAX_ARRAY_ELEM - 1) {
				arrtmp[j] = new wchar_t[k + 1];
				wcsncpy_s(arrtmp[j], k + 1, strtmp, k);
				arrtmp[j][k] = 0;
				k = 0;
				j++;
			}
			else if (j >= MAX_ARRAY_ELEM - 1) goto fail;
		}
		else if (Cmdline[i] == '\\') {
			if (!dq) {
				if (k < MAX_STRING_ELEM - 1) {
					strtmp[k] = Cmdline[i];
					k++;
				}
				else goto fail;
			}
			else if (!bs) bs = true;
			else if (k < MAX_STRING_ELEM - 1) {
				strtmp[k] = Cmdline[i];
				k++;
				bs = false;
			}
			else goto fail;
		}
		else if (Cmdline[i] == '"') {
			if (sq || bs) {
				if (k < MAX_STRING_ELEM - 1) {
					strtmp[k] = Cmdline[i];
					k++;
					bs = false;
				}
				else goto fail;
			}
			else dq = !dq;
		}
		else if (Cmdline[i] == '\'') {
			if (dq) {
				if (k < MAX_STRING_ELEM - 1) {
					strtmp[k] = Cmdline[i];
					k++;
				}
				else goto fail;
			}
			else sq = !sq;
		}
		else if (bs) {
			if (k < MAX_STRING_ELEM - 1) {
				switch (Cmdline[i])
				{
				case 'a':
					strtmp[k] = '\a';
					break;
				case 'b':
					strtmp[k] = '\b';
					break;
				case 'f':
					strtmp[k] = '\f';
					break;
				case 'r':
					strtmp[k] = '\r';
					break;
				case 'n':
					strtmp[k] = '\n';
					break;
				case 't':
					strtmp[k] = '\t';
					break;
				case 'v':
					strtmp[k] = '\v';
					break;
				default:
					goto fail;
				}
				k++;
			}
			else goto fail;
			bs = false;
		}
		else if (k < MAX_STRING_ELEM - 1) {
			strtmp[k] = Cmdline[i];
			k++;
		}
		else goto fail;
		i++;
	}
	if (dq || sq) goto fail;
	else if (k != 0 && j < MAX_ARRAY_ELEM - 1) {
		arrtmp[j] = new wchar_t[k + 1];
		wcsncpy_s(arrtmp[j], k + 1, strtmp, k);
		arrtmp[j][k] = 0;
		k = 0;
		j++;
	}
	else if (j >= MAX_ARRAY_ELEM - 1) goto fail;
	delete[] strtmp;
	result = new wchar_t* [j + 1];
	for (size_t p = 0; p < j; p++) result[p] = arrtmp[p];
	result[j] = nullptr;
	delete[] arrtmp;
	return (const wchar_t**)result;
fail:
	for (size_t p = 0; p < j; p++) delete[] arrtmp[p];
	delete[] arrtmp;
	return nullptr;
}

void ShellReleaseCmdlineW(const wchar_t** Cmdline)
{
	if (!Cmdline) return;
	wchar_t** arrtmp = (wchar_t**)Cmdline;
	size_t i = 0;
	while (arrtmp[i] != nullptr) delete[] arrtmp[i];
	delete[] arrtmp;
}
