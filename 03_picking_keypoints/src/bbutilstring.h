#ifndef __BBUTILSTRING__
#define __BBUTILSTRING__

#include <stdarg.h>  // For va_start, etc.
#include <memory>    // For std::unique_ptr
#include <string>

inline static
std::string StringFormat(const std::string fmt_str, ...)
{
	int final_n, n = ((int)fmt_str.size()) * 2; /* Reserve two times as much as the length of the fmt_str */
	std::string str;
	std::unique_ptr<char[]> formatted;
	va_list ap;
	while (1)
	{
		formatted.reset(new char[n]); /* Wrap the plain char array into the unique_ptr */
		strcpy(&formatted[0], fmt_str.c_str());
		va_start(ap, fmt_str);
		final_n = vsnprintf(&formatted[0], n, fmt_str.c_str(), ap);
		va_end(ap);
		if (final_n < 0 || final_n >= n)
			n += abs(final_n - n + 1);
		else
			break;
	}
	return std::string(formatted.get());
}

#ifdef WIN32 //WINDOWS
#include <time.h>
#include "mytime.h"
#else
#include <sys/time.h>
#endif

inline static
std::string GetTimeString()
{
	time_t t = time(0);
	struct tm* now = localtime(&t);
	struct timeval ts;
	gettimeofday(&ts, 0);
	double tu = ts.tv_usec;

	std::string ret = StringFormat("%d%02d%02d_%02d%02d%02d_%.f", now->tm_year + 1900,
		now->tm_mon + 1,
		now->tm_mday,
		now->tm_hour,
		now->tm_min,
		now->tm_sec,
		tu);
	return ret;
}

inline static
std::string MakeFileNameWithTime(const std::string &ext)
{
	std::string ret = GetTimeString() + "." + ext;
	return ret;
}


// case insensitive equal
inline static
bool IsEqualStrings(const std::string& a, const std::string& b)
{
	size_t sz = a.size();
	if (b.size() != sz)
		return false;
	for (unsigned int i = 0; i < sz; ++i)
		if (tolower(a[i]) != tolower(b[i]))
			return false;
	return true;
}

// https://wiki.kldp.org/HOWTO/html/C++Programming-HOWTO/standard-string.html
inline static
void Tokenize(const string& str,
	std::vector<std::string>& tokens,
	const string& delimiters)
{
	string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	string::size_type pos = str.find_first_of(delimiters, lastPos);

	while (string::npos != pos || string::npos != lastPos)
	{
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		lastPos = str.find_first_not_of(delimiters, pos);
		pos = str.find_first_of(delimiters, lastPos);
	}
}

#endif
