#include "app_report_collector.h"

#include "../app/prelude.h"


namespace simstudio {

	void SaveStatisticsRecord(World& app)
	{
		LogI << "==============";
		LogI << "Final statistics:";


		for (const auto& iter : app._entities)
		{
			Shared<Entity> entity = iter.second;
			entity->PrintFinalStatistics(0, app._stepper._stepIndex);
		}

		for (const auto& iter : app._spawnies)
		{
			Shared<Entity> entity = iter.second;
			entity->PrintFinalStatistics(0, app._stepper._stepIndex);
		}

	}

}

