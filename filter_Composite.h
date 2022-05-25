#pragma once
#include "filter.h"
#include "../SemestralnaPraca_Zimen/structures/list/array_list.h"

namespace filter
{
	template<typename K, typename Object>
	class FilterComposite : public Filter<K, Object>
	{
	public:
		void registerFilter(Filter<K, Object>* filter);
		virtual bool pass(const Object& o) override = 0;
	protected:
		structures::ArrayList<Filter<K, Object>*> filters_;
	};

	template<typename K, typename Object>
	inline void FilterComposite<K, Object>::registerFilter(Filter<K, Object>* filter)
	{
		filters_.add(filter);
	}
}