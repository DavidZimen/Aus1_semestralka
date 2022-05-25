#pragma once
#include "filter_Composite.h"

namespace filter
{
	template<typename K, typename Object>
	class FilterCompositeOR : public FilterComposite<K, Object>
	{
	public:
		bool pass(const Object& o) override;
	};

	template<typename K, typename Object>
	inline bool FilterCompositeOR<K, Object>::pass(const Object& o)
	{
		for (auto filter : filters_) {
			if (filter->pass(o)) {
				return true;
			}
		}
		return false;
	}
}