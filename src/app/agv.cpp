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

	}

	void Agv::FromXml(SafeXmlNode& node)
	{
		Entity::FromXml(node);
	}

	void Agv::PrintFinalStatistics(long statistics_delay, long simulation_duration)
	{
		LogD << "======================";
		LogD << F("Final statistics for Agv [{}]", _uid);
		LogI << "Agv valked:" << _statistics.walked << " m";
	}



}