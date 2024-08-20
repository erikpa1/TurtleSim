
#include "station.h"
#include "stepper.h"
#include "world.h"

#include <iomanip>  
#include "warehouse.h"


#include "../serialization/prelude.h"
#include "../utils/time_expr.h"

namespace simstudio

{
	Station::~Station()
	{
		LogD << "Station got somehow destructed";
	}

	Shared<Station> Station::New()
	{
		auto station = Shared<Station>();
		return Share<Station>();
	}


	void Station::Init()
	{
	}


	void Station::Step(World& app, Stepper& stepper)
	{
		if (_activeState == StationStates::WORKING)
		{
			if (_manufacturing_end <= stepper.GetStepSecond())
			{
				_FinishManufacturing(app);
			}
		}
		else if (_activeState == StationStates::BLOCKED) {
			_TryToPassNextEntity(app);
		}


	}


	void Station::FromXml(SafeXmlNode& node)
	{
		Entity::FromXml(node);
		_any_operation_time._strValue = node.GetStringAttrib("operation_time", _any_operation_time._strValue);
		_warehouse = node.GetStringAttrib("warehouse", "");

	}

	bool Station::TakeEntity(Shared<Entity>& entity)
	{
		if (CanTakeEntity()) {
			_activeEntity = entity;
			_statistics.entities_in += 1;
			_StartManufacturing();
			return true;

		}
		else {

			if (_activeState == StationStates::BLOCKED) {
				LogE << _uid << " can't take entity because is [blocked].";
			}
			else {
				LogE << _uid << " can't take entity because is [manufacturing].";
			}

			return false;
		}
	}

	bool Station::CanTakeEntity()
	{
		return _activeEntity == nullptr;
	}

	void Station::_FinishManufacturing(World& app)
	{
		_statistics.manufactured += 1;
		_activeState = StationStates::NON_OPERATIVE;
		_AddMaterialConsumption();

		_TryToPassNextEntity(app);
	}

	void Station::_TryToPassNextEntity(World& app)
	{

		bool isBlocked = true;

		auto connections = app.GetConnectedEntities(_uid);


		for (const auto& connection : connections) {
			if (connection->TakeEntity(_activeEntity)) {
				_activeEntity.reset();
				_statistics.entities_out += 1;

				if (_activeState == StationStates::BLOCKED) {
					LogE << F("[{}] is now free from block", _uid);
				}

				isBlocked = false;
				_activeState = StationStates::NON_OPERATIVE;

				return;
			}

		}



		if (isBlocked) {
			_activeState = StationStates::BLOCKED;
			_statistics.blocked_time += 1;
		}
	}

	bool Station::_AddMaterialConsumption()
	{

		if (_warehouse != "") {

			auto entity = GetEntity(_warehouse);

			if (auto warehouse = StaticCast<Warehouse>(entity)) {

				Array<WarehouseMaterialRequest> request;

				String mat = "Material_1";
				request.push_back(WarehouseMaterialRequest::New(mat, 2));

				mat = "Material_2";
				request.push_back(WarehouseMaterialRequest::New(mat, 3));


				return warehouse->TryPickMaterial(request);
			}
			else {
				LogE << StringThis() << "warehouse was invalid";
			}
		}

		return true;

	}

	void Station::_StartManufacturing()
	{
		if (_activeEntity) {
			auto manufacturing_time = _any_operation_time.CompileSecondsLong();
			_activeState = StationStates::WORKING;
			_manufacturing_end = _activeTime + manufacturing_time;
			_statistics.manufactured_time += manufacturing_time;
			LogI << "Started manufacturing, will be finished at: " << _manufacturing_end;
		}
		else {
			LogE << "Station didn't started manufacturing because entity was null";
		}
	}

	void Station::PrintFinalStatistics(long statistics_delay, long simulation_duration)
	{
		LogD << "======================";
		LogD << F("Final statistics for Station [{}]", _uid);

		double manufacturing_percentage = (static_cast<double>(_statistics.manufactured_time) / static_cast<double>(simulation_duration));
		double blocked_percentage = (static_cast<double>(_statistics.blocked_time) / static_cast<double>(simulation_duration));

		LogI << "Entities in:" << _statistics.entities_in;
		LogI << "Entities out:" << _statistics.entities_out;
		LogI << "Manufactures count: " << _statistics.manufactured;
		LogI << "Manufacturing percentage: " << manufacturing_percentage * 100 << "%";
		LogI << "Blocked: " << blocked_percentage * 100 << "%";
		LogI << "Idle: " << (1 - manufacturing_percentage - blocked_percentage) * 100 << "%";


		if (_statistics.manufactured != 0) {

			long time = _statistics.manufactured_time / _statistics.manufactured;

			String time_str = TimeExpr::MakeFromSeconds(time);

			LogI << "Avg manufacturing time: " << time_str;
		}
		else {
			LogI << "Avg manufacturing time: " << 0;
		}




	}


}