#pragma once
#include <SDL.h>
namespace mns
{
	class initializer
	{
	public:
		initializer();
		initializer(uint32_t flags);
		~initializer();
	};
}

