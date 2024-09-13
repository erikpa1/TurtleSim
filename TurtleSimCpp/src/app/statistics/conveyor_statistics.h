#pragma once

#include "SimCore/Prelude.h"

namespace simstudio {

	class ConveyorStatistics
	{

	public:
		long _peak = 0;
		long _items_entered = 0;
		long _items_left = 0;
		long _blocked_time = 0;
		long _empty_time = 0;

		void SetPeak(long newPeak);

	};



}