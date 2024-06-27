#pragma once

#include "../../prelude.h"

namespace simstudio {

	class BufferStatistics
	{

	public:
		long _peak = 0;
		long _itemsHandled = 0;
		long _blocked_time = 0;
		long _empty_time = 0;

		void SetPeak(long newPeak);

	};



}