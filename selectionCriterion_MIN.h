#pragma once
#include "selectionCriterion.h"

namespace scrits
{
	template<typename K, typename Object, typename Value>
	class SelectionCriterionMIN : public SelectionCriterion<K, Object, Value>
	{
	public:
		SelectionCriterionMIN(crits::Criterion<Object, Value>* criterion);
	protected:
		bool isTestedValueBest(Value bestNow, Value bestTested);
	};

	template<typename K, typename Object, typename Value>
	inline SelectionCriterionMIN<K, Object, Value>::SelectionCriterionMIN(crits::Criterion<Object, Value>* criterion) :
		SelectionCriterion<K, Object, Value>(criterion)
	{
	}

	template<typename K, typename Object, typename Value>
	inline bool SelectionCriterionMIN<K, Object, Value>::isTestedValueBest(Value bestNow, Value bestTested)
	{
		return bestTested < bestNow;
	}
}