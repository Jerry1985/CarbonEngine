#include "RALInterface.h"

RALInterface::RALInterface()
{
	for (int i = 0; i < MAX_RT_COUNT; ++i)
	{
		m_pendingRT[i] = 0;
		m_currentRT[i] = 0;
	}
	m_rtChanged = 0;
	m_validRTNum = 0;
}

// check if the RT is changed
void RALInterface::_checkRTChanged()
{
	for (int i = 0; i < MAX_RT_COUNT; ++i)
	{
		if (m_pendingRT[i] != m_currentRT[i])
		{
			m_rtChanged = true;
			return;
		}
	}
	m_rtChanged = false;
}