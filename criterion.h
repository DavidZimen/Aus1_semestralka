#pragma once

namespace crits
{
	template<typename Object, typename Result>
	class Criterion
	{
	public:
		virtual Result evaluate(Object& o) = 0;
		virtual ~Criterion() {};
	};
}