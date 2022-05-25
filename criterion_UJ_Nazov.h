#pragma once
#include "criterion_UJ.h"

namespace crits
{
	class CriterionUJNazov : public CriterionUj<std::wstring>
	{
	public:
		std::wstring evaluate(uj::UzemnaJednotka& o);
	};

	inline std::wstring CriterionUJNazov::evaluate(uj::UzemnaJednotka& o)
	{
		return o.getNazov();
	}
}