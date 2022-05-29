#pragma once
#include "selectionCriterion_MIN.h"
#include "uzemna_jednotka.h"
#include "criterion_UJ_VekovaSkupinaPocet.h"

namespace scrits
{
	template<typename K>
	class SelectionCriterionNajmensiaVekovaSkupina : public SelectionCriterionMIN<K, uj::UzemnaJednotka, int>
	{
	public:
		SelectionCriterionNajmensiaVekovaSkupina(std::wstring vekSkupina);
	};

	template<typename K>
	inline SelectionCriterionNajmensiaVekovaSkupina<K>::SelectionCriterionNajmensiaVekovaSkupina(std::wstring vekSkupina) :
		SelectionCriterionMIN<K, uj::UzemnaJednotka, int>(new crits::CriterionUJVekovaSkupinaPocet(vekSkupina), 6000000)
	{
	}
}