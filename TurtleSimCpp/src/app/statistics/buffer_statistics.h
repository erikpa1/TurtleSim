#pragma once

#include "SimCore/Prelude.h"

namespace simstudio {

	class BufferStatistics
	{

	public:
		long _peak = 0;
		long _itemsHandled = 0;
		long _blocked_time = 0;
		long _empty_time = 0;

		Array<Pair<long, long>> _peaks;

		void SetPeak(long second, long newPeak);




	};



}