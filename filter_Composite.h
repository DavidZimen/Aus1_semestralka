#pragma once
#include "filter.h"
#include "../SemestralnaPraca_Zimen/structures/list/linked_list.h"

namespace filter
{
	template<typename K, typename Object>
	class FilterComposite : public virtual Filter<K, Object>
	{
	public:
		FilterComposite();
		~FilterComposite();
		void registerFilter(Filter<K, Object>* filter);
	protected:
		structures::LinkedList<Filter<K, Object>*>* filters_;
	};

	template<typename K, typename Object>
	inline FilterComposite<K, Object>::FilterComposite()
	{
		filters_ = new structures::LinkedList<Filter<K, Object>*>();
	}

	template<typename K, typename Object>
	inline FilterComposite<K, Object>::~FilterComposite()
	{
		for (auto item : *filters_) {
			delete item;
		}
		delete filters_;
		filters_ = nullptr;
	}

	template<typename K, typename Object>
	inline void FilterComposite<K, Object>::registerFilter(Filter<K, Object>* filter)
	{
		filters_->add(filter);
	}
}