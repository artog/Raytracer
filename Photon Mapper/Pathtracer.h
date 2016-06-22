#pragma once
#include "int2.h"


class Pathtracer
{
public:
	Pathtracer();
	~Pathtracer();

	chag::float3 *frameBuffer;
	chag::int2	  frameBufferSize;
	int			  frameBufferSamples;

};

