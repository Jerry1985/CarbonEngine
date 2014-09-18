#include "RALInterface.h"

RALInterface::RALInterface()
{
	for (int i = 0; i < MAX_RT_COUNT; ++i)
	{
		m_PendingRT[i] = 0;
		m_CurrentRT[i] = 0;
	}
	m_RTChanged = 0;
}

// check if the RT is changed
void RALInterface::_checkRTChanged()
{
	for (int i = 0; i < MAX_RT_COUNT; ++i)
	{
		if (m_PendingRT[i] != m_CurrentRT[i])
		{
			m_RTChanged = true;
			return;
		}
	}
	m_RTChanged = false;
}