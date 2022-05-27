#pragma once
#include "criterion_UJ_VekovaSkupinaPodiel.h"
#include "filter_Criterion_Interval.h"

namespace filter
{
	template<typename K>
	class FilterUJVekovaSkupinaPodiel : public FilterCriterionInterval<K, uj::UzemnaJednotka, double>
	{
	public:
		FilterUJVekovaSkupinaPodiel(std::wstring vekSkupina, double vFrom, double vTo);
	};

	template<typename K>
	inline FilterUJVekovaSkupinaPodiel<K>::FilterUJVekovaSkupinaPodiel(std::wstring vekSkupina, double vFrom, double vTo) :
		FilterCriterionInterval<std::wstring, uj::UzemnaJednotka, double>(new crits::CriterionUJVekovaSkupinaPodiel(vekSkupina), vFrom, vTo)
	{
	}
}