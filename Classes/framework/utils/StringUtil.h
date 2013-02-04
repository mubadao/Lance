#ifndef _StringUtil_H_
#define _StringUtil_H_

#include "CommonHeader.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#include "iconv/iconv.h"
#endif

static string gString = "";

class StringUtil
{
public:
    static vector<string> split(const string& str, const string& delims, unsigned int maxSplits = 0)
	{
		vector<string> ret;
		// Pre-allocate some space for performance
		ret.reserve(maxSplits ? maxSplits + 1 : 10);    // 10 is guessed capacity for most case
        
		unsigned int numSplits = 0;
        
		// Use STL methods 
		size_t start, pos;
		start = 0;
		do 
		{
			pos = str.find_first_of(delims, start);
			if (pos == start)
			{
				// Do nothing
				start = pos + 1;
			}
			else if (pos == string::npos || (maxSplits && numSplits == maxSplits))
			{
				// Copy the rest of the string
				ret.push_back( str.substr(start) );
				break;
			}
			else
			{
				// Copy up to delimiter
				ret.push_back( str.substr(start, pos - start) );
				start = pos + 1;
			}
			// parse up to next real data
			start = str.find_first_not_of(delims, start);
			++numSplits;
            
		} while (pos != string::npos);
        
		return ret;
	}
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	static int GBKToUTF8(const string& gbkStr, const char* toCode, const char* fromCode)
	{
		iconv_t iconvH;
		iconvH = iconv_open(fromCode, toCode);

		if (iconvH == 0)
		{
			return -1;
		}
        
		const char* strChar = gbkStr.c_str();
		const char** pin = &strChar;
		size_t strLength = gbkStr.length();
		char* outbuf = (char*) malloc(strLength*4);

		char* pBuff = outbuf;

		memset( outbuf, 0, strLength*4);
		size_t outLength = strLength*4;
		if (-1 == iconv(iconvH, pin, &strLength, &outbuf, &outLength))
		{
			libiconv_close(iconvH);
			return -1;
		}

		gbkStr = pBuff;
		libiconv_close(iconvH);
		return 0;
	}

	static const char* gtou(const char* str)
	{
		gString = string(str);
		GBKToUTF8(gString, "gb2312", "utf-8");
		return gString.c_str();
	}
    
	static float parseReal(const string& val, float defaultValue = 0)
	{
		basic_stringstream<char, char_traits<char>, allocator<char>> str =
			basic_stringstream<char, char_traits<char>, allocator<char>>(val);
		float ret = defaultValue;
		str >> ret;

		return ret;
	}

	static int parseInt(const string& val, int defaultValue = 0)
	{
		basic_stringstream<char, char_traits<char>, allocator<char>> str =
            basic_stringstream<char, char_traits<char>, allocator<char>>(val);
		int ret = defaultValue;
		str >> ret;

		return ret;
	}

	static int parseCharToInt(const char* val, int defaultValue = 0)
	{
		string str = val;
		return parseInt(str, defaultValue);
	}

#else
    static float parseReal(const string& val, float defaultValue = 0)
	{
		return (float)atof(val.c_str());
	}
    
	static int parseInt(const string& val, int defaultValue = 0)
	{
		return atoi(val.c_str());
	}
    
	static int parseCharToInt(const char* val, int defaultValue = 0)
	{
		string str = val;
		return parseInt(str);
	}
#endif
    
	static float parseCharToFloat(const char* val, float defaultValue = 0)
	{
		string str = val;
		return parseReal(str, defaultValue);
	}
};

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#define g2u(str) StringUtil::gtou(str)
#else
#define g2u(str) str
#endif

#define fcs(format,...) CCString::createWithFormat(format,## __VA_ARGS__)->getCString()
#define itos(val) CCString::createWithFormat("%d",val)->getCString()
#define ftos(val) CCString::createWithFormat("%f",val)->getCString()
#define charToInt(val) StringUtil::parseCharToInt(val)
#define charToFloat(val) StringUtil::parseCharToFloat(val)
#define strToInt(val) StringUtil::parseInt(val)

#endif