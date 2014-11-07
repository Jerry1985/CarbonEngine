#ifndef CARBON_CSTRING
#define	CARBON_CSTRING

#include "CArray.h"
#include "Platform\Platform.h"
#include "Windows\WinString.h"

class CString
{
public:
	CString()
	{
	}
	CString(TCHAR* text)
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
	operator const TCHAR* const() const
	{
		return (const TCHAR* const)m_data.GetData();
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
	CString operator +(const TCHAR* str)
	{
		CASSERT(str);

		CString ret(this);
		if (str && *str)
		{
			int len = PlatformString::Strlen(str) + 1;
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
	bool IsEqual(TCHAR* str) const
	{
		if (str == 0)
			return false;

		int len = m_data.GetCount();
		const TCHAR* data = m_data.GetData();

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
		TCHAR	str[str_len];
		PlatformString::ItoS(data, str, 10);
		m_data.Release();
		m_data.Add(str, PlatformString::Strlen(str)+1);
	}
	// to int
	int	ToInt() const
	{
		return PlatformString::StoI(m_data.GetData());
	}

	// from bool
	void FromBool(bool data)
	{
		m_data.Release();
		m_data.Add(data ? S("true") : S("false"), data ? 5 : 6);
	}
	// to bool
	bool ToBool() const
	{
		if (IsEqual( S("true") ))
			return true;
		return false;
	}

	// from float
	void FromFloat(float data)
	{
		const int str_len = 1024;
		TCHAR	str[str_len];
		PlatformString::FtoS(data, str, str_len);
		m_data.Release();

		m_data.Add(str, PlatformString::Strlen(str) + 1);
	}
	float ToFloat() const
	{
		return PlatformString::StoF(m_data.GetData());
	}

private:
	CArray<TCHAR>	m_data;
};

#endif
