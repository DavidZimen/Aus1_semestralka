#pragma once
#include "criterion_UJ_VekPocet.h"
#include "filter_Criterion_Interval.h"

namespace filter
{
	class FilterUJVekPocet : public FilterCriterionInterval<std::wstring, uj::UzemnaJednotka, int>
	{
	public:
		FilterUJVekPocet(int vek, std::wstring pohlavie, int vFrom, int vTo);
	};

	inline FilterUJVekPocet::FilterUJVekPocet(int vek, std::wstring pohlavie, int vFrom, int vTo) :
		FilterCriterionInterval<std::wstring, uj::UzemnaJednotka, int>(new crits::CriterionUJVekPocet(vek, pohlavie), vFrom, vTo)
	{
	}
}