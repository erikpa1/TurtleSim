#include "buffer_statistics.h"


namespace simstudio {
	void BufferStatistics::SetPeak(long newPeak)
	{
		if (newPeak > _peak) {
			_peak = newPeak;
		}
	}
}

