#include "buffer_statistics.h"


namespace simstudio {
	void BufferStatistics::SetPeak(long second, long newPeak)
	{
		if (newPeak > _peak) {
			_peak = newPeak;
			_peaks.push_back({ second, newPeak });
		}
	}

}

