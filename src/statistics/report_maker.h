#pragma once

#include "../prelude.h"

namespace simstudio {


	class ReportMaker {



	private:

		Array<String> _stringBuffer;


	public:


		ReportMaker();

		void StartTable();

		void EndTable();

		void AddHeading(const String& text);

		void AddPercentageValue(const String& key, double value);



	};



}