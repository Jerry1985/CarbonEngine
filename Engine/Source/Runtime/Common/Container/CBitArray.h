#pragma once

#include "Platform\Platform.h"
#include "Misc\Assertion.h"
#include "Utility\UtilityMacro.h"
#include "Core\Archive.h"

class CBitArray
{
public:
	CBitArray(){}
	~CBitArray(){ Release(); }

	// allocate bit array
	FORCE_INLINE void Allocate(uint32 size)
	{
		CASSERT(size != 0);

		Release();

		m_Size = size;
		m_Data = (uint8*)operator new(size);
	}

	// copy bit array
	FORCE_INLINE void Copy(uint8* data, uint32 size, uint32 offset = 0)
	{
		memcpy_s(m_Data+offset, m_Size, (void*)data, size);
	}

	FORCE_INLINE uint32 GetSize() const
	{
		return m_Size;
	}

	FORCE_INLINE const uint8*	GetData() const
	{
		return m_Data;
	}

	FORCE_INLINE bool IsEmpty() const
	{
		return m_Size == 0;
	}

	// Release data
	FORCE_INLINE void Release()
	{
		::operator delete(m_Data);
		m_Data = 0;
	}

	friend FORCE_INLINE
	Archive& operator &(Archive& ar, CBitArray& ba)
	{
		if (ar.IsLoading())
		{
			ar & ba.m_Size;

			// release the data
			ba.Release();

			// allocate new data
			if (ba.m_Size)
			{
				ba.m_Data = (uint8*)operator new(ba.m_Size);
				ar.Serialize(ba.m_Data, ba.m_Size);
			}
			else
			{
				ba.m_Data = 0;
			}
		}
		else
		{
			ar & ba.m_Size;
			ar.Serialize(ba.m_Data, ba.m_Size);
		}
		return ar;
	}

private:
	uint8*	m_Data = 0;
	uint32	m_Size = 0;
};