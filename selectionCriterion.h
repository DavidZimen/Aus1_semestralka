#pragma once
#include "criterion.h"
#include "../SemestralnaPraca_Zimen/structures/table/table.h"

namespace scrits
{
	template<typename K, typename Object, typename Value>
	class SelectionCriterion
	{
	private:
		crits::Criterion<Object, Value>* criterion_;
	public:
		SelectionCriterion(crits::Criterion<Object, Value>* criterion);
		~SelectionCriterion();
		virtual Object& selectBest(structures::Table<K, Object*>* tab);
	protected:
		virtual bool isTestedValueBest(Value bestNow, Value bestTested) = 0;
	};

	template<typename K, typename Object, typename Value>
	inline SelectionCriterion<K, Object, Value>::SelectionCriterion(crits::Criterion<Object, Value>* criterion)
	{
	}

	template<typename K, typename Object, typename Value>
	inline SelectionCriterion<K, Object, Value>::~SelectionCriterion()
	{
		delete criterion_;
		criterion_ = nullptr;
	}

	template<typename K, typename Object, typename Value>
	inline Object& SelectionCriterion<K, Object, Value>::selectBest(structures::Table<K, Object*>* tab)
	{
		Object& testedO;
		Object& bestO;
		Value testedV;
		Value bestV;

		for (auto item : *tab) {
			testedO = *item->accessData();
			testedV = criterion_->evaluate(testedO);
			if (isTestedValueBest(bestV, testedV)) {
				bestV = testedV;
				bestO = testedO;
			}
		}

		return bestO;
	}
}