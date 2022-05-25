#pragma once
#include "criterion_UJ_VzdelaniePodiel.h"
#include "filter_Criterion_Interval.h"

namespace filter
{
	class FilterUJVzdelaniePodiel : public FilterCriterionInterval<std::wstring, uj::UzemnaJednotka, double>
	{
	public:
		FilterUJVzdelaniePodiel(std::wstring vzdelanie, double vFrom, double vTo);
	};

	inline FilterUJVzdelaniePodiel::FilterUJVzdelaniePodiel(std::wstring vzdelanie, double vFrom, double vTo) :
		FilterCriterionInterval<std::wstring, uj::UzemnaJednotka, double>(new crits::CriterionUJVzdelaniePodiel(vzdelanie), vFrom, vTo)
	{
	}
}