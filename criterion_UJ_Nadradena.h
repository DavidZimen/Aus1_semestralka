#pragma once
#include "criterion_UJ.h"

namespace crits
{
	class CriterionUJNadradena : CriterionUj<uj::UzemnaJednotka*>
	{
	public:
		uj::UzemnaJednotka* evaluate(uj::UzemnaJednotka& o);
	};

	inline uj::UzemnaJednotka* CriterionUJNadradena::evaluate(uj::UzemnaJednotka& o)
	{
		return o.getNadradena();
	}
}