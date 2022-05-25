#pragma once
#include "criterion_UJ_VekovaSkupinaPocet.h"
#include "filter_Criterion_Interval.h"

namespace filter
{
	template<typename K>
	class FilterUJVekovaSkupinaPocet : public FilterCriterionInterval<K, uj::UzemnaJednotka, int>
	{
	public:
		FilterUJVekovaSkupinaPocet(std::wstring vekSkupina, int vFrom, int vTo);
	};

	template<typename K>
	inline FilterUJVekovaSkupinaPocet<K>::FilterUJVekovaSkupinaPocet(std::wstring vekSkupina, int vFrom, int vTo) :
		FilterCriterionInterval<std::wstring, uj::UzemnaJednotka, int>(new crits::CriterionUJVekovaSkupinaPocet(vekSkupina), vFrom, vTo)
	{
	}
}