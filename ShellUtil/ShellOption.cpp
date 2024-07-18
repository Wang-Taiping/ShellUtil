#include "ShellOption.h"
#include <regex>
#include <string>
#include <vector>

typedef std::vector<std::string> strlist, * pstrlist;
typedef std::vector<std::wstring> wstrlist, * pwstrlist;

static int delim_space[] = { ' ', '\t', '\r', '\n' };
static std::regex normal(R"(^-{1,2}\w+(\w|-)+\w$)");
static std::wregex wnormal(LR"(^-{1,2}\w+(\w|-)+\w$)");
static std::regex optional(R"(^-{1,2}\w+(\w|=|-|\s)+\w$)");
static std::wregex woptional(LR"(^-{1,2}\w+(\w|=|-|\s)+\w$)");

typedef struct native_manager {
	strlist args;
	strlist result;
	uint32_t optid;
	std::string key;
} *pnative_manager;

typedef struct native_wmanager {
	wstrlist args;
	wstrlist result;
	uint32_t optid;
	std::wstring key;
} *pnative_wmanager;

static std::string keyname(std::string str)
{
	for (size_t i = 0; i < 2; i++) if (str.front() == '-') str.erase(str.begin());
	size_t pos = str.find('=');
	if (pos != std::string::npos) return str.substr(0, pos);
	return str;
}

static std::string keyval(std::string str)
{
	size_t pos = str.find('=');
	if (pos == str.size()) return std::string();
	if (pos != std::string::npos) return str.substr(pos + 1);
	return std::string();
}

static std::wstring wkeyname(std::wstring str)
{
	for (size_t i = 0; i < 2; i++) if (str.front() == '-') str.erase(str.begin());
	size_t pos = str.find('=');
	if (pos != std::wstring::npos) return str.substr(0, pos);
	return str;
}

static std::wstring wkeyval(std::wstring str)
{
	size_t pos = str.find('=');
	if (pos == str.size()) return std::wstring();
	if (pos != std::wstring::npos) return str.substr(pos + 1);
	return std::wstring();
}

static bool is_char_in_result(int val, const int* result, size_t len) {
	for (size_t i = 0; i < len; i++) {
		if (val == result[i]) return true;
	}
	return false;
}

ShellOptionStoreA ShellCreateOptionStoreA(int argc, const char** argv)
{
	size_t real_argc = 0;
	for (size_t i = 0; i < uint32_t(argc); i++) {
		if (argv[i]) real_argc++;
		else break;
	}
	if (real_argc < 2 || !argv) return nullptr;
	pnative_manager result = new native_manager;
	result->optid = 1;
	for (size_t i = 0; i < real_argc; i++) result->args.push_back(argv[i]);
	return ShellOptionStoreA(result);
}

ShellOptionStoreW ShellCreateOptionStoreW(int argc, const wchar_t** argv)
{
	size_t real_argc = 0;
	for (size_t i = 0; i < uint32_t(argc); i++) {
		if (argv[i]) real_argc++;
		else break;
	}
	if (real_argc < 2 || !argv) return nullptr;
	pnative_wmanager result = new native_wmanager;
	result->optid = 1;
	for (size_t i = 0; i < real_argc; i++) result->args.push_back(argv[i]);
	return ShellOptionStoreW(result);
}

uint32_t ShellAnalyzeOptionStoreA(ShellOptionStoreA OptionStore, ShellOptionRuleA* Rules)
{
	if (!OptionStore || !Rules) return SHELL_OPTFINISH;
	pnative_manager handle = pnative_manager(OptionStore);
	if (handle->optid >= handle->args.size()) return SHELL_OPTFINISH;
	std::string temp;
	uint32_t i = 0, j = 0;
	bool finded = false;
	handle->result.clear();
	handle->key.clear();
	if (std::regex_match(handle->args.at(handle->optid), normal)) {
		temp = keyname(handle->args.at(handle->optid));
		handle->key = temp;
		while (Rules[i].Name != nullptr) {
			if (temp != Rules[i].Name) {
				i++;
				continue;
			}
			if (Rules[i].Args == SHELL_ARGOPTIONAL) {
				temp = keyval(handle->args.at(handle->optid));
				if (!temp.empty()) handle->result.push_back(temp);
				return Rules[i].Identifier;
			}
			handle->optid++;
			if (Rules[i].Args > 0 && Rules[i].Args != SHELL_ARGOPTIONAL) {
				while (handle->optid < handle->args.size() && j < Rules[i].Args && !std::regex_match(handle->args.at(handle->optid), optional)) {
					handle->result.push_back(handle->args.at(handle->optid));
					j++;
					handle->optid++;
				}
				if (handle->result.size() < Rules[i].Args) {
					handle->result.clear();
					return SHELL_OPTIGNORE;
				}
			}
			return Rules[i].Identifier;
		}
		if (!finded) {
			handle->optid++;
			return SHELL_OPTUNKNOWN;
		}
	}
	else if (std::regex_match(handle->args.at(handle->optid), optional)) {
		temp = keyname(handle->args.at(handle->optid));
		handle->key = temp;
		while (Rules[i].Name != nullptr) {
			if (Rules[i].Args != SHELL_ARGOPTIONAL || temp != Rules[i].Name) {
				i++;
				continue;
			}
			temp = keyval(handle->args.at(handle->optid));
			if (!temp.empty()) handle->result.push_back(temp);
			handle->optid++;
			return Rules[i].Identifier;
		}
		handle->optid++;
		if (!finded) return SHELL_OPTUNKNOWN;
	}
	else {
		handle->result.push_back(handle->args.at(handle->optid));
		handle->optid++;
		return SHELL_OPTNORMAL;
	}
	return SHELL_OPTFINISH;
	return 0;
}

uint32_t ShellAnalyzeOptionStoreW(ShellOptionStoreW OptionStore, ShellOptionRuleW* Rules)
{
	if (!OptionStore || !Rules) return SHELL_OPTFINISH;
	pnative_wmanager handle = pnative_wmanager(OptionStore);
	if (handle->optid >= handle->args.size()) return SHELL_OPTFINISH;
	std::wstring temp;
	uint32_t i = 0, j = 0;
	bool finded = false;
	handle->result.clear();
	handle->key.clear();
	if (std::regex_match(handle->args.at(handle->optid), wnormal)) {
		temp = wkeyname(handle->args.at(handle->optid));
		handle->key = temp;
		while (Rules[i].Name != nullptr) {
			if (temp != Rules[i].Name) {
				i++;
				continue;
			}
			if (Rules[i].Args == SHELL_ARGOPTIONAL) {
				temp = wkeyval(handle->args.at(handle->optid));
				if (!temp.empty()) handle->result.push_back(temp);
				return Rules[i].Identifier;
			}
			handle->optid++;
			if (Rules[i].Args > 0 && Rules[i].Args != SHELL_ARGOPTIONAL) {
				while (handle->optid < handle->args.size() && j < Rules[i].Args && !std::regex_match(handle->args.at(handle->optid), woptional)) {
					handle->result.push_back(handle->args.at(handle->optid));
					j++;
					handle->optid++;
				}
				if (handle->result.size() < Rules[i].Args) {
					handle->result.clear();
					return SHELL_OPTIGNORE;
				}
			}
			return Rules[i].Identifier;
		}
		if (!finded) {
			handle->optid++;
			return SHELL_OPTUNKNOWN;
		}
	}
	else if (std::regex_match(handle->args.at(handle->optid), woptional)) {
		temp = wkeyname(handle->args.at(handle->optid));
		handle->key = temp;
		while (Rules[i].Name != nullptr) {
			if (Rules[i].Args != SHELL_ARGOPTIONAL || temp != Rules[i].Name) {
				i++;
				continue;
			}
			temp = wkeyval(handle->args.at(handle->optid));
			if (!temp.empty()) handle->result.push_back(temp);
			handle->optid++;
			return Rules[i].Identifier;
		}
		handle->optid++;
		if (!finded) return SHELL_OPTUNKNOWN;
	}
	else {
		handle->result.push_back(handle->args.at(handle->optid));
		handle->optid++;
		return SHELL_OPTNORMAL;
	}
	return SHELL_OPTFINISH;
	return 0;
}

const char* ShellGetKeyNameA(ShellOptionStoreA OptionStore)
{
	if (!OptionStore) return nullptr;
	pnative_manager handle = pnative_manager(OptionStore);
	if (handle->key.empty()) return nullptr;
	return handle->key.c_str();
}

const wchar_t* ShellGetKeyNameW(ShellOptionStoreW OptionStore)
{
	if (!OptionStore) return nullptr;
	pnative_wmanager handle = pnative_wmanager(OptionStore);
	if (handle->key.empty()) return nullptr;
	return handle->key.c_str();
}

const char* ShellGetResultA(ShellOptionStoreA OptionStore, uint32_t Index)
{
	if (!OptionStore) return nullptr;
	pnative_manager handle = pnative_manager(OptionStore);
	if (Index < handle->result.size()) return handle->result[Index].c_str();
	return nullptr;
}

const wchar_t* ShellGetResultW(ShellOptionStoreW OptionStore, uint32_t Index)
{
	if (!OptionStore) return nullptr;
	pnative_wmanager handle = pnative_wmanager(OptionStore);
	if (Index < handle->result.size()) return handle->result[Index].c_str();
	return nullptr;
}

void ShellReleaseOptionStoreA(ShellOptionStoreA OptionStore)
{
	if (!OptionStore) return;
	pnative_manager handle = pnative_manager(OptionStore);
	delete handle;
}

void ShellReleaseOptionStoreW(ShellOptionStoreW OptionStore)
{
	if (!OptionStore) return;
	pnative_wmanager handle = pnative_wmanager(OptionStore);
	delete handle;
}
