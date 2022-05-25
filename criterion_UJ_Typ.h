#pragma once
#include "criterion_UJ.h"

namespace crits
{
	class CriterionUJTyp : public CriterionUj<uj::TypUzemJednotka>
	{
	public:
		uj::TypUzemJednotka evaluate(uj::UzemnaJednotka& o);
	};

	inline uj::TypUzemJednotka CriterionUJTyp::evaluate(uj::UzemnaJednotka& o)
	{
		return o.getTyp();
	}
}