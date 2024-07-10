#include "agv.h"

#include "app.h"
#include "stepper.h"
#include "track.h"

#include "../serialization/prelude.h"

namespace simstudio {


	Shared<Agv> Agv::New()
	{
		return Share<Agv>();
	}

	String Agv::Type()
	{
		return Agv::ClassType();
	}

	void Agv::Init()
	{
	}

	void Agv::Step(App& app, Stepper& stepper)
	{

		if (auto activeTrack = _activeTrack.lock()) {
			if (activeTrack) {
				if (_pos_local._x < activeTrack->_length) {
					_pos_local._x += this->_speed;

					LogE << StringThis() << " moved " << _pos_local._x << " / " << activeTrack->_length;
				}
				else {
					LogE << StringThis() << " hitted the line end";
				}
			}
		}


	}

	void Agv::FromXml(SafeXmlNode& node)
	{
		Entity::FromXml(node);
	}

	void Agv::StartRideOn(Weak<Track>& track)
	{
		LogE << "Agv is riding on";
		_activeTrack = track;
	}


}