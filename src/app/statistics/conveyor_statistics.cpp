#include "conveyor_statistics.h"


namespace simstudio {
	void ConveyorStatistics::SetPeak(long newPeak)
	{
		if (newPeak > _peak) {
			_peak = newPeak;
		}
	}
}