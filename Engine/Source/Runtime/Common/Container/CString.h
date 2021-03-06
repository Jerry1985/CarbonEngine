#pragma once

#include "Platform\PlatformString.h"
#include "Container\CArray.h"
#include "Math\Math.h"
#include "Core\Archive.h"

class CString
{
public:
	CString()
	{
		_addStringEnd();
	}
	CString(TCHAR text[])
	{
		FromString(text);
	}
	CString(const TCHAR* text)
	{
		FromString(text);
	}
	CString(const CString& str)
	{
		m_data = str.m_data;
	}
	CString(int data)
	{
		FromInt(data);
	}
	CString(float data)
	{
		FromFloat(data);
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
	FORCE_INLINE operator const TCHAR* const() const
	{
		return (const TCHAR* const)m_data.GetData();
	}

	// operator +
	FORCE_INLINE CString operator +(const CString& string)
	{
		CString ret(this);

		int len = ret.m_data.GetCount();
		ret.m_data.Replace(Math::Max(0, len - 1), string.m_data.GetCount(), string.m_data.GetData());

		return ret;
	}
	FORCE_INLINE CString operator +(const TCHAR* str)
	{
		CASSERT(str);

		CString ret(this);
		if (str && *str)
		{
			int len = PlatformString::Strlen(str);
			ret.m_data.Replace(ret.Strlen(), len, str);
		}
		ret._addStringEnd();

		return ret;
	}

	FORCE_INLINE const CString& operator +=(const TCHAR* str)
	{
		if (str && *str)
		{
			int len = PlatformString::Strlen(str);
			m_data.Replace(Strlen(), len, str);
		}

		_addStringEnd();

		return *this;
	}

	// operator
	FORCE_INLINE bool operator ==(const CString& string) const
	{
		return m_data == string.m_data;
	}

	// isequal
	FORCE_INLINE bool IsEqual(TCHAR* str) const
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

	// from bytes
	FORCE_INLINE void FromBytes(uint8* data, int32 size)
	{
		CASSERT(data && size != 0);

		m_data.Release();
		m_data.Allocate(size / sizeof(TCHAR)+1);
		m_data.Add((const TCHAR*)data, size / sizeof(TCHAR));
		_addStringEnd();
	}

	// from int
	FORCE_INLINE void FromInt(int data)
	{
		const int str_len = 1024;
		TCHAR	str[str_len];
		PlatformString::ItoS(data, str, 10);
		m_data.Release();
		m_data.Add(str, PlatformString::Strlen(str));
		_addStringEnd();
	}
	// to int
	FORCE_INLINE int	ToInt() const
	{
		return PlatformString::StoI(m_data.GetData());
	}

	// from bool
	FORCE_INLINE void FromBool(bool data)
	{
		m_data.Release();
		m_data.Add(data ? S("true") : S("false"), data ? 5 : 6);
	}
	// to bool
	FORCE_INLINE bool ToBool() const
	{
		if (IsEqual(S("true")))
			return true;
		return false;
	}

	// from float
	FORCE_INLINE void FromFloat(float data)
	{
		const int str_len = 1024;
		TCHAR	str[str_len];
		PlatformString::FtoS(data, str, str_len);
		m_data.Release();

		m_data.Add(str, PlatformString::Strlen(str));
		_addStringEnd();
	}
	FORCE_INLINE float ToFloat() const
	{
		return PlatformString::StoF(m_data.GetData());
	}

	FORCE_INLINE void FromString(const TCHAR* str)
	{
		m_data.Release();

		int index = 0;
		while (str[index])
			m_data.Add(str[index++]);
		_addStringEnd();
	}

	FORCE_INLINE bool IsEmpty() const
	{
		return m_data.IsEmpty();
	}

	FORCE_INLINE uint32	Strlen() const
	{
		// the last character doesn't count here
		return m_data.GetCount() - 1;
	}

	FORCE_INLINE uint32	StrSizeInBytes() const
	{
		return m_data.GetSize();
	}

	FORCE_INLINE void Format(const TCHAR* format, ...)
	{
		m_data.Release();

		va_list args;

		va_start(args, format);
		TCHAR buffer[4096];
		//vsprintf_s(buffer, 4096, format, args);
		PlatformString::Format(buffer, 4096, format, args);
		va_end(args);

		FromString(buffer);
	}

	friend FORCE_INLINE
	CString operator + (const TCHAR* str0, const CString& str1)
	{
			CASSERT(str0);

			CString ret(str0);
			ret.m_data.Replace(ret.Strlen(), str1.Strlen(), str1);

			ret._addStringEnd();

			return ret;
	}
	friend CString STR(const TCHAR* format, ...);

	friend FORCE_INLINE 
	Archive& operator &(Archive& ar, CString& str)
	{
		return ar & str.m_data;
	}

private:
	CArray<TCHAR>	m_data;

	// add end
	FORCE_INLINE void	_addStringEnd()
	{
		if (m_data.GetCount() == 0)
			m_data.Add(0);
		else if(m_data.GetData()[m_data.GetCount() - 1] != 0)
			m_data.Add(0);
	}
};

FORCE_INLINE CString STR(const TCHAR* format, ...)
{
	va_list args;

	va_start(args, format);
	TCHAR buffer[4096];
	PlatformString::Format(buffer, 4096, format, args);
	va_end(args);

	return CString(buffer);
}