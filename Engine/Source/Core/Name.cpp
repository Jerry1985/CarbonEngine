#include "Name.h"
#include "Common\Container\CString.h"

CArray<CLinkedList<NameItem*>> Name::m_HashNames(NAME_ARRAY_COUNT, true);

// Constructor
NameItem::NameItem(const TCHAR* name, int32 hashIndex) :m_HashIndex(hashIndex)
{
	PlatformString::Strcpy(m_Name, NAME_MAX_SIZE, name);
}

// whether the string is equal to the item
bool NameItem::IsEqual(const TCHAR* name)
{
	return 0 == PlatformString::Strcmp(m_Name, name);
}

// constructor
Name::Name()
{
}
Name::Name(TCHAR* name)
{
	setup(name);
}
Name::Name(const CString& name)
{
	setup(name);
}

// = operator
const Name& Name::operator = (const Name& name)
{
	m_HashIndex = name.m_HashIndex;
	return *this;
}

const Name& Name::operator = (const TCHAR* name)
{
	setup(name);
	return *this;
}

// to string
CString Name::ToString() const
{
	return CString(m_NameString);
}

// setup name
void Name::setup(const TCHAR* name)
{
	CASSERT(PlatformString::Strlen(name) < NAME_MAX_SIZE);

	m_HashIndex = PlatformString::StrHash(name) & NAME_ARRAY_COUNT_MASK;

	// find the name first
	CLinkedListIterator<NameItem*> it(m_HashNames[m_HashIndex]);
	while (!it.IsEnd())
	{
		if ((*it)->IsEqual(name))
		{
			m_NameString = (*it)->m_Name;
			return;
		}
		++it;
	}

	// allocate one if there isn't
	NameItem* item = new NameItem(name, m_HashIndex);
	m_HashNames[m_HashIndex].Link(item);
	m_NameString = item->m_Name;
}