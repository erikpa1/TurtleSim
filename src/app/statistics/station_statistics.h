#pragma once

#include "SimCore/Prelude.h"

namespace simstudio {
	class StationStatistics
	{
	public:
		long manufactured = 0;
		long entities_in = 0;
		long entities_out = 0;
		long manufactured_time = 0;
		long blocked_time = 0;
	};



}