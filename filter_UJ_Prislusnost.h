#pragma once
#include "criterion_UJ_Prislusnost.h"
#include "filter_Criterion_Value.h"


namespace filter
{
	template<typename K>
	class FilterUJPrislusnost : public FilterCriterionValue<K, uj::UzemnaJednotka, bool>
	{
	public:
		FilterUJPrislusnost(bool hodnota, std::wstring vyssiCelok);
	};

	template<typename K>
	inline FilterUJPrislusnost<K>::FilterUJPrislusnost(bool hodnota, std::wstring vyssiCelok) :
		FilterCriterionValue<std::wstring, uj::UzemnaJednotka, bool>(new crits::CriterionUJPrislusnost(vyssiCelok), hodnota)
	{
	}
}