#pragma once

#include "Utility\UtilityMacro.h"

template<typename T>
class	Singleton
{
public:
	Singleton()
	{
		m_pSingleton = static_cast<T*>(this);
	}
	virtual ~Singleton()
	{
		m_pSingleton = 0;
	}

	static T& GetSingleton()
	{
		if (m_pSingleton == 0)
			new T();
		return *m_pSingleton;
	}

	static T* GetSingletonPtr()
	{
		return m_pSingleton;
	}

	static void DeleteSingleton()
	{
		SAFE_DELETE(m_pSingleton);
	}

	static void CreateInstance()
	{
		if (m_pSingleton == 0)
			new T();
	}

protected:
	static T* m_pSingleton;
};

#define	DEFINE_SINGLETON(T)	template<> T* Singleton<T>::m_pSingleton = 0;

