#ifndef CARBON_COLOR
#define	CARBON_COLOR

struct Color
{
public:
	Color();
	Color(float r, float g, float b, float a = 1.0f);
	Color(float c[4]);

	~Color();

	union
	{
		struct{ 
			float r;
			float g;
			float b;
			float a; 
		};
		float c[4];
	};

	static const Color BLACK;
	static const Color WHITE;
	static const Color RED;
	static const Color GREEN;
	static const Color BLUE;
	static const Color YELLOW;
};

#endif