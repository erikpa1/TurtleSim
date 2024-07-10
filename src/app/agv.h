#pragma once
#include "entity.h"



namespace simstudio {


	class Track;

	enum class AgvPowerType {
		ELECTRIC = 0,
		PETROL = 1,
	};


	class Agv : public Entity {

	public:
		FactoryType("agv");

		double _speed = 1;
		double _energy_consumption = 1;
		double _energy_storage = 100;


		Weak<Track> _activeTrack;

	public:
		static Shared<Agv>New();

		virtual String Type() override;

		virtual void Init() override;
		virtual void Step(App& app, Stepper& stepper) override;
		virtual void FromXml(SafeXmlNode& node) override;


		void StartRideOn(Weak<Track>& track);




	};

}