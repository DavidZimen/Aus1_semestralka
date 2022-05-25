#pragma once
#include "criterion_UJ_VzdelaniePocet.h"
#include "filter_Criterion_Interval.h"

namespace filter
{
	class FilterUJVzdelaniePocet : public FilterCriterionInterval<std::wstring, uj::UzemnaJednotka, int>
	{
	public:
		FilterUJVzdelaniePocet(std::wstring vzdelanie, int vFrom, int vTo);
	};

	inline FilterUJVzdelaniePocet::FilterUJVzdelaniePocet(std::wstring vzdelanie, int vFrom, int vTo) :
		FilterCriterionInterval<std::wstring, uj::UzemnaJednotka, int>(new crits::CriterionUJVzdelaniePocet(vzdelanie), vFrom, vTo)
	{
	}
}