#include "MyUtils.h"

#include <windows.h>

namespace MyUtils
{

	#define TMP_MAX_PATH 512

	void charTowchar(const char *chr, wchar_t *wchar, int size)
	{
		MultiByteToWideChar(CP_ACP, 0, chr,
			strlen(chr) + 1, wchar, size / sizeof(wchar[0]));
	}

	void wcharTochar(const wchar_t *wchar, char *chr, int size)
	{
		WideCharToMultiByte(CP_ACP, 0, wchar, -1,
			chr, size, NULL, NULL);
	}

	// D:\aaa\bbb\ccc\ddd\abc.txt --> D:/aaa/bbb/ccc/ddd/abc.txt
	std::string convertPathFormatToUnixStyle(const std::string& path)
	{
		std::string ret = path;
		int len = ret.length();
		for (int i = 0; i < len; ++i)
		{
			if (ret[i] == '\\')
			{
				ret[i] = '/';
			}
		}
		return ret;
	}


	std::wstring StringUtf8ToWideChar(const std::string& strUtf8)
	{
		std::wstring ret;
		if (!strUtf8.empty())
		{
			int nNum = MultiByteToWideChar(CP_UTF8, 0, strUtf8.c_str(), -1, nullptr, 0);
			if (nNum)
			{
				WCHAR* wideCharString = new WCHAR[nNum + 1];
				wideCharString[0] = 0;

				nNum = MultiByteToWideChar(CP_UTF8, 0, strUtf8.c_str(), -1, wideCharString, nNum + 1);

				ret = wideCharString;
				delete[] wideCharString;
			}
			else
			{
				//CCLOG("Wrong convert to WideChar code:0x%x", GetLastError());
			}
		}
		return ret;
	}

	std::string StringWideCharToUtf8(const std::wstring& strWideChar)
	{
		std::string ret;
		if (!strWideChar.empty())
		{
			int nNum = WideCharToMultiByte(CP_UTF8, 0, strWideChar.c_str(), -1, nullptr, 0, nullptr, FALSE);
			if (nNum)
			{
				char* utf8String = new char[nNum + 1];
				utf8String[0] = 0;

				nNum = WideCharToMultiByte(CP_UTF8, 0, strWideChar.c_str(), -1, utf8String, nNum + 1, nullptr, FALSE);

				ret = utf8String;
				delete[] utf8String;
			}
			else
			{
				//CCLOG("Wrong convert to Utf8 code:0x%x", GetLastError());
			}
		}

		return ret;
	}

	std::string UTF8StringToMultiByte(const std::string& strUtf8)
	{
		std::string ret;
		if (!strUtf8.empty())
		{
			std::wstring strWideChar = StringUtf8ToWideChar(strUtf8);
			int nNum = WideCharToMultiByte(CP_ACP, 0, strWideChar.c_str(), -1, nullptr, 0, nullptr, FALSE);
			if (nNum)
			{
				char* ansiString = new char[nNum + 1];
				ansiString[0] = 0;

				nNum = WideCharToMultiByte(CP_ACP, 0, strWideChar.c_str(), -1, ansiString, nNum + 1, nullptr, FALSE);

				ret = ansiString;
				delete[] ansiString;
			}
			else
			{
				//CCLOG("Wrong convert to Ansi code:0x%x", GetLastError());
			}
		}

		return ret;
	}

	std::string getCheckPath()
	{
		char pathBuffer[MAX_PATH] = { 0 };
		WCHAR  wszPath[MAX_PATH] = { 0 };
		int nNum = WideCharToMultiByte(CP_ACP, 0, wszPath,
			GetCurrentDirectory(sizeof(wszPath), wszPath),
			pathBuffer, MAX_PATH, NULL, NULL);
		pathBuffer[nNum] = '\\';

		std::string str(pathBuffer);
		return str;
	}

}