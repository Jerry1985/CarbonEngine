#pragma once

#include "RALResource.h"

enum RAL_VERTEXELEMENTTYPE;

struct RALVertexElementDesc
{
	unsigned short			streamIndex;
	unsigned short			offset;
	RAL_VERTEXELEMENTTYPE	type;
	unsigned short			attributeIndex;
	bool					useInstanceIndex;
};

class RALVertexLayout : public RALResource
{
public:
	RALVertexLayout();
	~RALVertexLayout();
};