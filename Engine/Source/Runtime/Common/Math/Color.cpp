#include "Color.h"

const Color Color::BLACK(0.0f, 0.0f, 0.0f);
const Color Color::WHITE(1.0f, 1.0f, 1.0f);
const Color Color::RED(1.0f, 0.0f, 0.0f);
const Color Color::GREEN(0.0f, 1.0f, 0.0f);
const Color Color::BLUE(0.0f, 0.0f, 1.0f);
const Color Color::YELLOW(1.0f, 1.0f, 0.0f);

Color::Color()
{
	r = 0.0f;
	g = 0.0f;
	b = 0.0f;
	a = 0.0f;
}

Color::Color(float _r, float _g, float _b, float _a)
{
	r = _r;
	g = _g;
	b = _b;
	a = _a;
}

Color::Color(float _c[4])
{
	c[0] = _c[0];
	c[1] = _c[1];
	c[2] = _c[2];
	c[3] = _c[3];
}

Color::~Color()
{
}