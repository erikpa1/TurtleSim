#include "drain.h"

namespace simstudio {
	Shared<Drain> Drain::New()
	{
		return Share<Drain>();
	}

	bool Drain::TakeEntity(Shared<Entity>& entity)
	{
		_statistics.received += 1;
		return true;
	}

	void Drain::PrintFinalStatistics(long start, long end)
	{
		LogD << "======================";
		LogD << F("Final statistics for Drain [{}]", _uid);

		LogI << "Manufactures count: " << _statistics.received;
	}

}
