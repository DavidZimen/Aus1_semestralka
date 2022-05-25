#pragma once
#include "criterion_UJ_VekPocet.h"
#include "filter_Criterion_Interval.h"

namespace filter
{
	template<typename K>
	class FilterUJVekPocet : public FilterCriterionInterval<K, uj::UzemnaJednotka, int>
	{
	public:
		FilterUJVekPocet(int vek, std::wstring pohlavie, int vFrom, int vTo);
	};

	template<typename K>
	inline FilterUJVekPocet<K>::FilterUJVekPocet(int vek, std::wstring pohlavie, int vFrom, int vTo) :
		FilterCriterionInterval<std::wstring, uj::UzemnaJednotka, int>(new crits::CriterionUJVekPocet(vek, pohlavie), vFrom, vTo)
	{
	}
}