#include "warehouse.h"


namespace simstudio {



	bool Warehouse::TryPickMaterial(Array<WarehouseMaterialRequest>& requests)
	{
		LogW << "Pick material requested";

		if (_mode == WarehouseMode::INFINITE_STORAGE) {

			for (const auto& req : requests) {
				if (this->_requests.contains(req._uid)) {
					this->_requests[req._uid] += req._quantity;
				}
				else {
					this->_requests[req._uid] = req._quantity;
				}
			}

			return true;
		}
		else {

			bool can_take_all = true;



			return can_take_all;
		}

	}

	void Warehouse::PrintFinalStatistics(long statistics_delay, long simulation_duration)
	{
		LogD << "======================";
		LogD << F("Final statistics for Warehouse [{}]", _uid);

		for (const auto& pair : this->_requests) {
			LogI << "Required: " << pair.first << " in count: " << pair.second;
		}


	}

}