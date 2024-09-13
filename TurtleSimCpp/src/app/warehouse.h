#pragma once
#include "entity.h"

#include "statistics/warehouse_statistics.h"

namespace simstudio {


	class WarehouseMaterialRequest {
	public:
		String _uid = "";
		long _quantity = 0;

		static WarehouseMaterialRequest New(String& uid, long quantity) {
			WarehouseMaterialRequest tmp;
			tmp._uid = uid;
			tmp._quantity = quantity;
			return tmp;
		}

	};


	class WarehouseMaterial {
	public:
		String _uid = "";
		long _quantity = 0;

	};

	enum class WarehouseMode {
		LIMITED_STORAGE = 0,
		INFINITE_STORAGE = 1,

	};

	class Warehouse : public Entity {

	public:
		FactoryType("warehouse");
		FactoryNew(Warehouse);

		HashMap<Shared< WarehouseMaterial>> _stocks;

		HashMap<long> _requests;

		WarehouseMode _mode = WarehouseMode::INFINITE_STORAGE;

		WarehouseStatistics _statistics;


		bool TryPickMaterial(Array<WarehouseMaterialRequest>& _requests);

		virtual void PrintFinalStatistics(long statistics_delay, long simulation_duration);




	};
}