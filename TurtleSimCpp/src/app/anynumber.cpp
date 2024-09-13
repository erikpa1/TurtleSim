
#include "anynumber.h"

#include <cmath>

#include "../utils/math_expr.h"
#include "../utils/time_expr.h"

namespace simstudio
{

	double AnyNumber::CompileMathExpr(double notFound = 0)
	{
		return MathExpr::Execute(_strValue).value_or(notFound);
	}

	uint64_t AnyNumber::CompileMilis()
	{
		return TimeExpr::MilisFromTimeString(_strValue);
	}


	double AnyNumber::CompileSeconds()
	{

		auto result = MathExpr::Execute(_strValue);

		if (result.has_value())
		{
			return result.value();
		}
		else
		{
			return TimeExpr::SecondsFromTimeString(_strValue);
		}
	}

	long AnyNumber::CompileSecondsLong()
	{
		auto tmp = CompileSeconds();
		return static_cast<long>(std::ceil(tmp));
	}






}