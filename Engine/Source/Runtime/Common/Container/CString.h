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

	// operator
	CString operator +(const CString& string)
	{
		CString ret(this);
		ret.m_data.Append(string.m_data);

		return ret;
	}

private:
	CArray<char>	m_data;
};

#endif
