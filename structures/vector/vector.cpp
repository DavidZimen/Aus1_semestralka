#include "vector.h"
#include "../utils.h"
#include "../heap_monitor.h"
#include <cstdlib>
#include <cstring>

using namespace std;

namespace structures
{
	Vector::Vector(size_t size) :
		memory_(std::calloc(size, 1)),
		size_(size)
	{	
	}

	Vector::Vector(Vector& other) :
		Vector(other.size_)
	{
		memcpy(memory_, other.memory_, size_);
	}

	Vector::~Vector()
	{
		free(memory_);
		memory_ = nullptr;
		size_ = 0;														//nemaju vplyv na leakovanie, je to len pre pomoc, ak mame viac pointrov na jedno miesto v pamati
	}

	size_t Vector::size()
	{
		return size_;
	}

	Structure& Vector::assign(Structure& other)
	{
		if (this != &other)
		{
			Vector& otherVector = dynamic_cast<Vector&>(other);
			size_ = otherVector.size_;
			memory_ = realloc(memory_, size_);							//smernik ktory relokujeme si rovno aj aktualizujeme operatorom rovna sa
			memcpy(memory_, otherVector.memory_, size_);
		}
		return *this;
	}

	bool Vector::equals(Structure& other)
	{
		if (this == &other)
		{
			return true;
		}
		else
		{
			Vector* otherVector = dynamic_cast<Vector*>(&other);
			if (otherVector != nullptr)
			{
				return size_ == otherVector->size_ && memcmp(memory_, otherVector->memory_, size_) == 0;
			}
			else
			{
				return false;
			}
		}

	}

	byte& Vector::operator[](int index)
	{
		return at(index);
	}

	byte& Vector::at(int index)
	{
		return *getBytePointer(index);
	}

	void Vector::copy(Vector& src, int srcStartIndex, Vector& dest, int destStartIndex, int length)
	{
		//pomocou Utils::rangeCheckExcept musim skontrolovat tieto podmienky

		//srcStartIndex musi patrit <0; src.size)
		Utils::rangeCheckExcept(srcStartIndex, src.size(), "Invalid srcStartIndex");
		//srcStartIndex + length musi patrit <0; src.size>
		Utils::rangeCheckExcept(srcStartIndex + length, src.size() + 1, "Invalid srcStartIndex");

		//destStartIndex musi patrit <0; dest.size)
		Utils::rangeCheckExcept(destStartIndex, src.size(), "Invalid destStartIndex");
		//destStartIndex + length musi patrit <0; dest.size>
		Utils::rangeCheckExcept(destStartIndex + length, src.size() + 1, "Invalid destStartIndex");

		//ak sa jedna o kopirovanie v identickom vektore A ZAROVEN je vzdialenost medzi srcStartIndex a destStartIndex < length
		// tak: memmove
		// inak: memcopy
		
		if (&src == &dest && abs(srcStartIndex - destStartIndex) < length)			//nemozem ist cez equals, lebo ona neberie pamatove miesto, ale vlastnosti
		{
			memmove(dest.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length);
		}
		else
		{
			memcpy(dest.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length);
		}
	}

	byte* Vector::getBytePointer(int index)
	{
		Utils::rangeCheckExcept(index, size_, "Invalid index!!!");
		return reinterpret_cast<byte*>(memory_) + index;
	}
}