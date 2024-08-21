#pragma once


namespace simstudio {

	class UiApp;

	class AvailableEntitiesList {

	public:

		void Draw();

		UiApp* _app;


	private:

		void _AddAndDrawEntityIfValid(const String& lang, const String& type);
		void _AddEntityOfType(const String& type);



	};



};



