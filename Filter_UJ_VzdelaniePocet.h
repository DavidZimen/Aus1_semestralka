#pragma once
#include "criterion_UJ_VzdelaniePocet.h"
#include "filter_Criterion_Interval.h"

namespace filter
{
	template<typename K>
	class FilterUJVzdelaniePocet : public FilterCriterionInterval<K, uj::UzemnaJednotka, int>
	{
	public:
		FilterUJVzdelaniePocet(std::wstring vzdelanie, int vFrom, int vTo);
	};

	template<typename K>
	inline FilterUJVzdelaniePocet<K>::FilterUJVzdelaniePocet(std::wstring vzdelanie, int vFrom, int vTo) :
		FilterCriterionInterval<std::wstring, uj::UzemnaJednotka, int>(new crits::CriterionUJVzdelaniePocet(vzdelanie), vFrom, vTo)
	{
	}
}