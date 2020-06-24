#pragma once
#include "window.h"

namespace mns
{
	class drawable
	{
	public:
		virtual void draw(mns::window& window) = 0;
		virtual ~drawable() {}
	};
}

