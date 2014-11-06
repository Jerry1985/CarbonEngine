#ifndef CARBON_CSTRING
#define	CARBON_CSTRING

#include "CArray.h"

class CString
{
public:
	CString()
	{
	}
	CString(char* text)
	{
		int index = 0;
		do
		{
			m_data.Add(text[index]);
		} while (text[index++]);
	}
	CString(const CString& str)
	{
		m_data = str.m_data;
	}
	CString(int data)
	{
		FromInt(data);
	}
	CString(const CString* const pStr)
	{
		CASSERT(pStr);

		m_data = pStr->m_data;
	}
	~CString()
	{
	}

	// cast the data
	operator const char* const() const
	{
		return (const char* const)m_data.GetData();
	}

	// operator +
	CString operator +(const CString& string)
	{
		CString ret(this);

		int len = ret.m_data.GetCount();
		len = (len > 0) ? len - 1 : len;
		ret.m_data.Replace(len, string.m_data.GetCount(), string.m_data.GetData());

		return ret;
	}
	CString operator +(const char* str)
	{
		CASSERT(str);

		CString ret(this);
		if (str && *str)
		{
			int len = (int)strlen(str) + 1;
			m_data.Add(str, len);
		}

		return ret;
	}

	// operator
	bool operator ==(const CString& string) const
	{
		return m_data == string.m_data;
	}

	// isequal
	bool IsEqual(char* str) const
	{
		if (str == 0)
			return false;

		int len = m_data.GetCount();
		const char* data = m_data.GetData();

		int i = 0;
		do
		{
			if (str[i] != data[i])
				return false;

			if (str[i] == 0 && data[i] == 0)
				return true;

			if ((str[i] == 0 && data[i] != 0) ||
				(str[i] != 0 && data[i] == 0))
				return false;

			i++;
		} while (true);
	}

	// from int
	void FromInt(int data)
	{
		const int str_len = 1024;
		char	str[str_len];
		_itoa_s<str_len>(data, str, 10);
		m_data.Release();
		m_data.Add(str, (int)strlen(str)+1);
	}
	// to int
	int	ToInt() const
	{
		return atoi(m_data.GetData());
	}

	// from bool
	void FromBool(bool data)
	{
		m_data.Release();
		m_data.Add(data ? "true" : "false", data ? 5 : 6);
	}
	// to bool
	bool ToBool() const
	{
		if (IsEqual( "true" ))
			return true;
		return false;
	}

private:
	CArray<char>	m_data;
};

#endif
