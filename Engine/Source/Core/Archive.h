#pragma once

#include "Common\Platform\Platform.h"

class Archive
{
public:
	// Constructor and Destructor
	Archive( bool loading = false );
	virtual ~Archive();

	// Serialize
	virtual void	Serialize(void* V, uint32 length)
	{
	}

	// & operators
#define POD_OPERATOR(Type) \
	FORCE_INLINE Archive& operator &( Type& data)\
	{\
		Serialize(&data, sizeof(Type)); \
		return *this;\
	}

	POD_OPERATOR(uint8)
	POD_OPERATOR(uint16)
	POD_OPERATOR(uint32)
	POD_OPERATOR(uint64)
	POD_OPERATOR(int8)
	POD_OPERATOR(int16)
	POD_OPERATOR(int32)
	POD_OPERATOR(int64)
	POD_OPERATOR(float)
	POD_OPERATOR(CHAR)
	POD_OPERATOR(WCHAR)

	FORCE_INLINE bool IsLoading() const
	{
		return m_Loading;
	}

protected:
	bool	m_Loading = true;
};