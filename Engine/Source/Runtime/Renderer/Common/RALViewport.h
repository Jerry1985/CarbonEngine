#ifndef CARBON_RALVIEWPORT
#define CARBON_RALVIEWPORT

struct RALViewport
{
	float	x, y;			// top left corner of the viewport
	float	w, h;			// size for the viewport
	float	minZ, maxZ;		// depth range for the viewport

	RALViewport() :x(0.0f), y(0.0f), w(0.0f), h(0.0f), minZ(0.0f), maxZ(1.0f)
	{
	}
	RALViewport(float _w, float _h) :x(0.0f), y(0.0f), w(_w), h(_h), minZ(0.0f), maxZ(1.0f)
	{
	}
};
#endif