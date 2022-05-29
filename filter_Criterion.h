#pragma once
#include "filter.h"
#include "criterion.h"

namespace filter
{
	template<typename K, typename Object, typename Value>
	class FilterCriterion : public virtual Filter<K, Object>
	{
	private:
		crits::Criterion<Object, Value>* criterion_;
	public:
		FilterCriterion(crits::Criterion<Object, Value>* criterion);
		~FilterCriterion();
		bool pass(Object& o) override;
		crits::Criterion<Object, Value>* getCriterion();
	protected:
		virtual bool passFilter(Value v) = 0;
	};

	template<typename K, typename Object, typename Value>
	inline FilterCriterion<K, Object, Value>::FilterCriterion(crits::Criterion<Object, Value>* criterion) :
		criterion_(criterion)
	{
	}

	template<typename K, typename Object, typename Value>
	inline FilterCriterion<K, Object, Value>::~FilterCriterion()
	{
		delete criterion_;
		criterion_ = nullptr;
	}

	template<typename K, typename Object, typename Value>
	inline bool FilterCriterion<K, Object, Value>::pass(Object& o)
	{
		if (criterion_ != nullptr) {
			return passFilter(criterion_->evaluate(o));
		}
	}

	template<typename K, typename Object, typename Value>
	inline crits::Criterion<Object, Value>* FilterCriterion<K, Object, Value>::getCriterion()
	{
		return criterion_;
	}
}