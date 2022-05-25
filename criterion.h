#pragma once

namespace crits
{
	template<typename Object, typename Result>
	class Criterion
	{
		virtual Result evaluate(Object& o) = 0;
	};
}