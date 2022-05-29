#pragma once
#include "selectionCriterion_MAX.h"
#include "uzemna_jednotka.h"
#include "criterion_UJ_VekovaSkupinaPocet.h"

namespace scrits
{
	template<typename K>
	class SelectionCriterionNajvacsiaVekovaSkupina : public SelectionCriterionMAX<K, uj::UzemnaJednotka, int>
	{
	public:
		SelectionCriterionNajvacsiaVekovaSkupina(std::wstring vekSkupina);
	};

	template<typename K>
	inline SelectionCriterionNajvacsiaVekovaSkupina<K>::SelectionCriterionNajvacsiaVekovaSkupina(std::wstring vekSkupina) :
		SelectionCriterionMAX<K, uj::UzemnaJednotka, int>(new crits::CriterionUJVekovaSkupinaPocet(vekSkupina), -1)
	{
	}
}