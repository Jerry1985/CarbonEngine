#pragma once

template<class T>
class CLinkedListNode
{
	T	m_Data;

	CLinkedListNode*	m_Next = 0;
};

template< class T >
class CLinkedList
{
public:

private:
	CLinkedListNode<T>*	m_First = 0;
};