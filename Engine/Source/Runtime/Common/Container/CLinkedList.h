#pragma once

#include "Platform\Platform.h"
#include "Misc\Assertion.h"

template<class T>
class CLinkedList;

template<class T>
struct CLinkedListNode
{
public:
	T	m_Data;

	CLinkedListNode<T>*	m_Previous = 0;
	CLinkedListNode<T>*	m_Next = 0;

	CLinkedList<T>*		m_List = 0;

	CLinkedListNode()
	{
	}
	CLinkedListNode(const T& data) :m_Data(data)
	{
	}
	~CLinkedListNode()
	{
	}

	// Unlink the node
	void UnLink()
	{
		if (m_Previous)
			m_Previous->m_Next = m_Next;
		else if (m_List->m_First == this)
			m_List->m_First = m_Next;

		if (m_Next)
			m_Next->m_Previous = m_Previous;
		else if (m_List->m_Last == this)
			m_List->m_Last = m_Previous;

		m_Previous = 0;
		m_Next = 0;
		m_List = 0;
	}
};

template<class T>
class CLinkedListIterator
{
public:
	CLinkedListIterator(const CLinkedList<T>& list) 
		: m_Current(list.m_First)
	{
	}
	CLinkedListIterator(const CLinkedList<T>* list)
	{
		CASSERT(list);
		m_Current = list->m_First;
	}
	CLinkedListIterator(const CLinkedListIterator<T>& it)
	{
		m_Current = it.m_Current;
	}
	~CLinkedListIterator()
	{
		m_Current = 0;
	}

	FORCE_INLINE const T& operator*() const
	{
		CASSERT(m_Current);
		return m_Current->m_Data;
	}

	FORCE_INLINE T& operator*()
	{
		CASSERT(m_Current);
		return m_Current->m_Data;
	}

	FORCE_INLINE T* operator ->()
	{
		return &m_Current->m_Data;
	}

	FORCE_INLINE const T* operator ->() const
	{
		return &m_Current->m_Data;
	}

	FORCE_INLINE const CLinkedListIterator& operator++()
	{
		if (!m_Current)
			return *this;
		m_Current = m_Current->m_Next;
		return *this;
	}

	FORCE_INLINE CLinkedListIterator operator++(int)
	{
		if (!m_Current)
			return *this;

		CLinkedListIterator<T> it(*this);
		m_Current = m_Current->m_Next;
		return it;
	}

	FORCE_INLINE const CLinkedListIterator& operator--()
	{
		if (!m_Current)
			return *this;
		m_Current = m_Current->m_Previous;
		return *this;
	}

	FORCE_INLINE CLinkedListIterator operator--(int)
	{
		if (!m_Current)
			return *this;

		CLinkedListIterator<T> it(*this);
		m_Current = m_Current->m_Previous;
		return it;
	}

	FORCE_INLINE bool IsEnd() const
	{
		return !m_Current;
	}

private:
	CLinkedListNode<T>*	m_Current;
};

template< class T >
class CLinkedList
{
public:
	CLinkedList(){}
	~CLinkedList(){}

	// first node
	FORCE_INLINE CLinkedListNode<T>*	First() const
	{
		return m_First;
	}

	// add a new linked list node
	FORCE_INLINE CLinkedListNode<T>*	Link(CLinkedListNode<T>* node)
	{
		CASSERT(node && !node->m_List);

		node->m_List = this;

		if (m_First == 0 && m_Last == 0)
		{
			m_First = node;
			m_Last = node;
		}else
		{
			node->m_Previous = m_Last;
			m_Last->m_Next = node;

			m_Last = node;
		}

		return node;
	}
	
	// add a new linked list node
	FORCE_INLINE CLinkedListNode<T>*	Link(T nodeData)
	{
		CLinkedListNode<T>* node = new CLinkedListNode<T>();
		node->m_Data = nodeData;

		node->m_List = this;

		if (m_First == 0 && m_Last == 0)
		{
			m_First = node;
			m_Last = node;
		}
		else
		{
			node->m_Previous = m_Last;
			m_Last->m_Next = node;

			m_Last = node;
		}

		return node;
	}

	// Clear is not responsible for releasing allocated memory
	void Clear()
	{
		m_First = 0;
		m_Last = 0;
	}

private:
	CLinkedListNode<T>*	m_First = 0;
	CLinkedListNode<T>*	m_Last = 0;

	template<class T>
	friend struct CLinkedListNode;

	template<class T>
	friend class CLinkedListIterator;
};