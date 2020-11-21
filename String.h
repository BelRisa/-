#include <iostream>
#include <cassert>

int strLen(const char* str)
{
	int i = 0;
	while (true)
	{
		if (str[i] == '\0')
			return i;
		i++;
	}
}


struct String
{
	String(const char* strc)
	{
		strSize = strLen(strc) + 1;
		memorySize = 2 * strSize;
		str = new char[memorySize];
		for (int i = 0; i < strSize; ++i)
			str[i] = strc[i];
	}

	String()
	{
		delete[] str;
	}

	String(const char* strc, const int memorySize1)
	{
		strSize = strLen(strc) + 1;
		assert(strSize < memorySize1);
		memorySize = memorySize1;
		str = new char[memorySize];
		for (int i = 0; i < strSize; ++i)
			str[i] = strc[i];
	}

	String(const String& string)
	{
		strSize = string.strSize;
		memorySize = 2 * strSize;
		str = new char[memorySize];
		for (int i = 0; i < strSize; ++i)
			str[i] = string.str[i];
	}

	String(const String& string, const int memorySize1)
	{
		memorySize = memorySize1;
		strSize = string.strSize;
		assert(strSize < memorySize);
		str = new char[memorySize];
		for (int i = 0; i < strSize; ++i)
			str[i] = string.str[i];
	}

	const char operator [] (const int index) 
	{
		return str[index];
	}

	String(const int len)
	{
		strSize = len + 1;
		memorySize = 2 * strSize;
		str = new char[memorySize];
	}


	String& operator = (const String& string)
	{
		int size = string.strSize;
		if (size > memorySize)
		{
			delete[] str;
			str = new char[2 * size];
			memorySize = 2 * size;
		}
		strSize = size;
		for (int i = 0; i < size; i++)
		{
			str[i] = string.str[i];
		}
		return *this;
	}

	int len() const
	{
		return strSize - 1;
	}

	int countChar(char c) const
	{
		int i = 0;
		int count = 0;
		for (int i = 0; i < strSize; ++i)
			if (str[i] == c)
				count++;
		return count;
	}

	int find1of(char c) const
	{
		int i = 0;
		while (str[i] != c)
			i++;
		return i;
	}

	String& split(int index)
	{
		String string = String(strSize - index - 2);
		int n = index;
		for (int i = 0; i < strSize - n; ++i)
		{
			string.str[i] = str[i + n];
		}
		strSize = index + 1;
		str[index] = '\0';
		return string;
	}


	String operator + (const String& string) const
	{
		int size = strSize + string.len();
		String retStr (size);
		for (int i = 0; i < strSize - 1; ++i)
			retStr.str[i] = str[i];
		int n = strSize - 1;
		for (int i = 0; i < string.strSize; ++i)
			retStr.str[i + n] = string.str[i];
		return retStr;
	}

	char* c_str()
	{
		return str;
	}

	bool foundStr(const char* strc)
	{
		int len_strc = strLen(strc);
		int* arr = new int[strSize];
		if (str[0] == strc[0])
			arr[0] = 1;
		else
			arr[0] = 0;
		for (int i = 1; i < strSize; ++i)
		{
			if (arr[i - 1] != len_strc)
			{
				if (str[i] == strc[arr[i - 1]])
				{
					arr[i] = arr[i - 1] + 1;

					continue;
				}

				if (str[i] == strc[0])
				{
					arr[i] = 1;

					continue;
				}

				else
				{
					arr[i] = 0;

					continue;
				}
			}

			delete[] arr;
			return true; 
		}

		for (int i = 0; i < strSize; ++i)
		{
			std::cout << str[i] << ' ' << arr[i] << std::endl;
		}

		if (arr[strSize - 2] == len_strc)
		{
			delete[] arr;
			return true;
		}

		delete[] arr;
		return false;
	}

	char* str;
	int memorySize;
	int strSize;
};

int strCount(char* str, char n)
{
	int i = 0;
	int count = 0;
	while (true)
	{
		if (str[i] == '\0')
			return count;
		i++;

		if (str[i] == n)
		{
			count++;
		}
	}

}

String arrCharMerge(char* str1, char* str2)
{
	int len = strLen(str1) + strLen(str2) + 1;
	String string(len);
	for (int i = 0; i < strLen(str1); ++i)
	{
		string.str[i] = str1[i];
	}
	for (int i = 0; i < strLen(str2) + 1; ++i)
	{
		string.str[i + strLen(str1)] = str2[i];
	}
	return string;
}