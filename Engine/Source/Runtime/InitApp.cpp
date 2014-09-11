#include <iostream>
using namespace std;

#include "Math\Vector4.h"

int main(int argc, char** argv)
{
	Vector4f v0( 1.0f , 2.0f , 4.0f , 2.0f );
	Vector4f v1( 3.0f , 1.0f , 5.0f, 5.0f );
	
	float t = Dot3( v0 , v1 );

	return 0;
}