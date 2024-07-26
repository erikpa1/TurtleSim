#pragma once


namespace simstudio {


	class UiApp {

	public:
		void StartDrawing();

	private:

		bool _leftBarActive = true;

		void _DrawLeftBar();
		void _DrawMiddleBar();
		void _DrawRightBar();

	};




};

