#pragma once

#include "Utility\UtilityMacro.h"

template< class T >
class PtrProxy
{
public:
	PtrProxy( T* p );
	~PtrProxy();

	operator T* ()
	{
		return m_Ptr;
	}

	T* operator ->()
	{
		return m_Ptr;
	}

private:
	T* m_Ptr;
};

template< class T >
PtrProxy<T>::PtrProxy(T* p) :m_Ptr(p)
{
}

template< class T >
PtrProxy<T>::~PtrProxy()
{
	SAFE_DELETE(m_Ptr);
}
