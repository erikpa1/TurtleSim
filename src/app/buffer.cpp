#include "buffer.h"

#include "app.h"
#include "../serialization/prelude.h"
#include "../utils/time_expr.h"

namespace simstudio {
	Shared<Buffer> Buffer::New()
	{
		return Share<Buffer>();
	}
	void Buffer::Init()
	{

	}

	void Buffer::Step(App& app, Stepper& stepper)
	{
		if (_buffer.size() > 0) {
			auto connections = app.GetConnectedEntities(_uid);
			for (const auto& connection : connections) {
				Shared<Entity> poped_entity = _buffer.back();

				if (connection->TakeEntity(poped_entity)) {
					_buffer.pop_back();
				}
				else {
					LogE << connection->_uid << " can't take entity from buffer";
				}
			}
		}

		if (_buffer.size() == _limit) {
			_statistics._blocked_time += 1;
		}
		else if (_buffer.size() == 0) {
			_statistics._empty_time += 1;
		}
	}

	void Buffer::FromXml(SafeXmlNode& node)
	{
		Entity::FromXml(node);
		_limit = node.GetIntAttrib("limit", 8);

	}

	bool Buffer::TakeEntity(Shared<Entity>& entity)
	{
		if (CanTakeEntity()) {
			_buffer.push_back(entity);
			_statistics.SetPeak(GetSimSecond(), _buffer.size());
			return true;
		}

		return false;
	}

	bool Buffer::CanTakeEntity()
	{
		return _buffer.size() <= _limit;
	}

	Shared<Entity> Buffer::PopEntity()
	{
		if (_buffer.size() > 0) {

			Shared<Entity> _poped_entity = _buffer.back();
			_buffer.pop_back();
			return _poped_entity;

		}

		return {};
	}

	void Buffer::PrintFinalStatistics(long statistics_delay, long simulation_duration)
	{
		LogD << "======================";
		LogD << F("Final statistics for Buffer [{}]", _uid);
		LogI << "Peak: " << _statistics._peak;

		double blocked_percentage = (static_cast<double>(_statistics._blocked_time) / static_cast<double>(simulation_duration));
		double empty_percentage = (static_cast<double>(_statistics._empty_time) / static_cast<double>(simulation_duration));

		LogI << "Blocked: " << blocked_percentage * 100 << "%";
		LogI << "Empty: " << empty_percentage * 100 << "%";
		LogI << "Peak: " << _statistics._peak;

		//LogI << "Peaks:";
		//for (const auto& [at, peak] : _statistics._peaks) {
		//	LogI << "--Peak at: [" << TimeExpr::MakeFromSeconds(at) << "] capacity required: [" << peak << "]";
		//}
	}

}

