#ifndef __MY_UTILS_H__
#define __MY_UTILS_H__

#include <string>

namespace MyUtils
{
	void charTowchar(const char *chr, wchar_t *wchar, int size);

	void wcharTochar(const wchar_t *wchar, char *chr, int size);

	// D:\aaa\bbb\ccc\ddd\abc.txt --> D:/aaa/bbb/ccc/ddd/abc.txt
	std::string convertPathFormatToUnixStyle(const std::string& path);

	std::wstring StringUtf8ToWideChar(const std::string& strUtf8);

	std::string StringWideCharToUtf8(const std::wstring& strWideChar);

	std::string UTF8StringToMultiByte(const std::string& strUtf8);

	std::string getCheckPath();

}
#endif