#pragma once
#include "criterion_UJ_VzdelaniePodiel.h"
#include "filter_Criterion_Interval.h"

namespace filter
{
	template<typename K>
	class FilterUJVzdelaniePodiel : public FilterCriterionInterval<K, uj::UzemnaJednotka, double>
	{
	public:
		FilterUJVzdelaniePodiel(std::wstring vzdelanie, double vFrom, double vTo);
	};

	template<typename K>
	inline FilterUJVzdelaniePodiel<K>::FilterUJVzdelaniePodiel(std::wstring vzdelanie, double vFrom, double vTo) :
		FilterCriterionInterval<std::wstring, uj::UzemnaJednotka, double>(new crits::CriterionUJVzdelaniePodiel(vzdelanie), vFrom, vTo)
	{
	}
}