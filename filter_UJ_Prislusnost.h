#pragma once
#include "criterion_UJ_Prislusnost.h"
#include "filter_Criterion_Value.h"

namespace filter
{
	class FilterUJPrislusnost : public FilterCriterionValue<std::wstring, uj::UzemnaJednotka, bool>
	{
	public:
		FilterUJPrislusnost(bool hodnota, std::wstring vyssiCelok);
	};

	inline FilterUJPrislusnost::FilterUJPrislusnost(bool hodnota, std::wstring vyssiCelok) :
		FilterCriterionValue<std::wstring, uj::UzemnaJednotka, bool>(new crits::CriterionUJPrislusnost(vyssiCelok), hodnota)
	{
	}
}