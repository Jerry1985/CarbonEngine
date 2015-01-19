#pragma once

#include "Platform\PlatformString.h"
#include "Container\CArray.h"
#include "Container\CLinkedList.h"
#include "Core\Archive.h"
#include "Container\CString.h"

#define	NAME_ARRAY_COUNT		8192
#define	NAME_ARRAY_COUNT_MASK	NAME_ARRAY_COUNT-1
#define	NAME_MAX_SIZE		128

struct NameItem
{
public:
	TCHAR		m_Name[NAME_MAX_SIZE];	// Name data
	int32		m_HashIndex = -1;

	// Constructor
	NameItem(const TCHAR* name, int32 hashIndex);
	// whether the string is equal to the item
	bool	IsEqual(const TCHAR* name);
};

class Name
{
public:
	// constructor
	Name();
	Name(const TCHAR* name);
	Name(const CString& name);

	// = operator
	const Name& operator = (const Name& name);
	const Name& operator = (const TCHAR* name);

	// to string
	CString ToString() const;

	// TCHAR* operator
	FORCE_INLINE operator const TCHAR* const() const
	{
		return m_NameString;
	}

	// == operator
	FORCE_INLINE bool operator == (const Name& name){
		return name.m_HashIndex == m_HashIndex;
	}
	// != operator
	FORCE_INLINE bool operator != (const Name& name){
		return name.m_HashIndex != m_HashIndex;
	}

	friend FORCE_INLINE
	Archive& operator &(Archive& ar, Name& ba)
	{
		if (ar.IsLoading())
		{
			CString name;
			ar & name;

			if (!name.IsEmpty())
				ba.setup(name);
		}
		else
		{
			ar & ba.ToString();
		}
		return ar;
	}

private:
	// current hash index, -1 means invalid name
	int	m_HashIndex = -1;

	// the pointer to string
	const TCHAR* m_NameString = 0;

	// static array of names
	static CArray<CLinkedList<NameItem*>>	m_HashNames;

	// setup name
	void	setup(const TCHAR* name);
};