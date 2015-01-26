#pragma once

class Resource
{
public:
	Resource(){}
	virtual ~Resource(){}

	virtual void Init(){}
	virtual void Release(){}

	bool	IsInitialized() const{
		return m_Initialized; 
	}

protected:
	bool	m_Initialized = false;
};