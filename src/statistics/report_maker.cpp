
#include "report_maker.h"

namespace simstudio {

	ReportMaker::ReportMaker()
	{

	}
	void ReportMaker::StartTable()
	{
		_stringBuffer.push_back("<table>");
	}

	void ReportMaker::EndTable()
	{
		_stringBuffer.push_back("</table>");
	}

	void ReportMaker::AddHeading(const String& text)
	{
		_stringBuffer.push_back(F("<h1>{}<h1>", text));
	}

	void ReportMaker::AddPercentageValue(const String& key, double value)
	{
		_stringBuffer.push_back(F("<div>{}: {}<div>", key, value));
	}

}