#pragma once
#include "criterion_UJ_VekovaSkupinaPodiel.h"
#include "filter_Criterion_Interval.h"

namespace filter
{
	class FilterUJVekovaSkupinaPodiel : public FilterCriterionInterval<std::wstring, uj::UzemnaJednotka, double>
	{
	public:
		FilterUJVekovaSkupinaPodiel(std::wstring vekSkupina, double vFrom, double vTo);
	};

	inline FilterUJVekovaSkupinaPodiel::FilterUJVekovaSkupinaPodiel(std::wstring vekSkupina, double vFrom, double vTo) :
		FilterCriterionInterval<std::wstring, uj::UzemnaJednotka, int>(new crits::CriterionUJVekovaSkupinaPodiel(vekSkupina), vFrom, vTo)
	{
	}
}