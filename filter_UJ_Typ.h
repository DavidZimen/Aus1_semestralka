#pragma once
#include "criterion_UJ_Typ.h"
#include "typ_uj.h"
#include "filter_Criterion_Value.h"

namespace filter
{
	template<typename K>
	class FilterUJTyp : public FilterCriterionValue<K, uj::UzemnaJednotka, uj::TypUzemJednotka>
	{
	public:
		FilterUJTyp(uj::TypUzemJednotka typ);
	};

	template<typename K>
	inline FilterUJTyp<K>::FilterUJTyp(uj::TypUzemJednotka typ) :
		FilterCriterionValue<std::wstring, uj::UzemnaJednotka, uj::TypUzemJednotka>(new crits::CriterionUJTyp(), typ)
	{
	}
}