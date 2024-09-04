#pragma once




namespace simstudio {

	class UiApp;

	class AppControls {

	public:

		void Draw();


		UiApp* _app;


	private:

		void _StartNewProject();
		void _OpenProjectJSON();
		void _OpenProjectXML();
		void _SaveProject();


	};

}