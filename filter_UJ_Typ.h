#pragma once
#include "criterion_UJ_Typ.h"
#include "typ_uj.h"
#include "filter_Criterion_Value.h"

namespace filter
{
	class FilterUJTyp : public FilterCriterionValue<std::wstring, uj::UzemnaJednotka, uj::TypUzemJednotka>
	{
	public:
		FilterUJTyp(uj::TypUzemJednotka typ);
	};

	inline FilterUJTyp::FilterUJTyp(uj::TypUzemJednotka typ) :
		FilterCriterionValue<std::wstring, uj::UzemnaJednotka, uj::TypUzemJednotka>(new crits::CriterionUJTyp(), typ)
	{
	}
}