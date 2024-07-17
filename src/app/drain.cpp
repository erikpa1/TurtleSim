#include "drain.h"

#include "app.h"


namespace simstudio {
	Shared<Drain> Drain::New()
	{
		return Share<Drain>();
	}

	bool Drain::TakeEntity(Shared<Entity>& entity)
	{
		_statistics.received += 1;
		_app->UnlinkEntity(entity->_uid);
		return true;
	}

	bool Drain::CanTakeEntity()
	{
		return true;
	}

	void Drain::PrintFinalStatistics(long start, long end)
	{
		LogD << "======================";
		LogD << F("Final statistics for Drain [{}]", _uid);

		LogI << "Entities left: " << _statistics.received;
	}

}
