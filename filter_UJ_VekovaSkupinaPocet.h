#pragma once
#include "criterion_UJ_VekovaSkupinaPocet.h"
#include "filter_Criterion_Interval.h"

namespace filter
{
	class FilterUJVekovaSkupinaPocet : public FilterCriterionInterval<std::wstring, uj::UzemnaJednotka, int>
	{
	public:
		FilterUJVekovaSkupinaPocet(std::wstring vekSkupina, int vFrom, int vTo);
	};

	inline FilterUJVekovaSkupinaPocet::FilterUJVekovaSkupinaPocet(std::wstring vekSkupina, int vFrom, int vTo) :
		FilterCriterionInterval<std::wstring, uj::UzemnaJednotka, int>(new crits::CriterionUJVekovaSkupinaPocet(vekSkupina), vFrom, vTo)
	{
	}
}