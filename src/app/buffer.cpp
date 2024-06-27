#include "buffer.h"

#include "app.h"
#include "../serialization/prelude.h"

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

				if (connection->CanTakeEntity()) {

					Shared<Entity> _poped_entity = _buffer.back();
					_buffer.pop_back();
					connection->TakeEntity(_poped_entity);
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
			_statistics.SetPeak(_buffer.size());
			return true;
		}

		return false;
	}

	bool Buffer::CanTakeEntity()
	{
		return _buffer.size() < _limit;
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


	}

}

