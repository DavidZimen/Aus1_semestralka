#pragma once

#include "list.h"
#include "../structure_iterator.h"
#include "../array/array.h"
#include <typeinfo>

namespace structures
{
	/// <summary> Zoznam implementovany polom. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v zozname. </typepram>
	template<typename T>
	class ArrayList : public List<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		ArrayList();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> ArrayList, z ktoreho sa prevezmu vlastnosti. </param>
		ArrayList(ArrayList<T>& other);

		/// <summary> Destruktor. </summary>
		~ArrayList();

		/// <summary> Vrati pocet prvkov v zozname. </summary>
		/// <returns> Pocet prvkov v zozname. </returns>
		size_t size() override;

		/// <summary> Priradenie struktury. </summary>
		/// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary> Porovnanie struktur. </summary>
        /// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
        /// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
		bool equals(Structure& other);

		/// <summary> Vrati adresou prvok na indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Adresa prvku na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
		T& at(int index) override;

		/// <summary> Prida prvok do zoznamu. </summary>
		/// <param name = "data"> Pridavany prvok. </param>
		void add(const T& data) override;

		/// <summary> Vlozi prvok do zoznamu na dany index. </summary>
		/// <param name = "data"> Pridavany prvok. </param>
		/// <param name = "index"> Index prvku. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
		/// <remarks> Ak je ako index zadana hodnota poctu prvkov (teda prvy neplatny index), metoda insert sa sprava ako metoda add. </remarks>
		void insert(const T& data, int index) override;

		/// <summary> Odstrani prvy vyskyt prvku zo zoznamu. </summary>
		/// <param name = "data"> Odstranovany prvok. </param>
		/// <returns> true, ak sa podarilo prvok zo zoznamu odobrat, false inak. </returns>
		bool tryRemove(const T& data) override;

		/// <summary> Odstrani zo zoznamu prvok na danom indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Odstraneny prvok. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
		T removeAt(int index) override;

		/// <summary> Vrati index prveho vyskytu prvku v zozname. </summary>
		/// <param name = "data"> Prvok, ktoreho index sa hlada. </param>
		/// <returns> Index prveho vyskytu prvku v zozname, ak sa prvok v zozname nenachadza, vrati -1. </returns>
		int getIndexOf(const T& data) override;

		/// <summary> Vymaze zoznam. </summary>
		void clear() override;

		/// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
		/// <returns> Iterator na zaciatok struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<T>* getBeginIterator() override;

		/// <summary> Vrati skutocny iterator na koniec struktury </summary>
		/// <returns> Iterator na koniec struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<T>* getEndIterator() override;

	private:
		/// <summary> Pole s datami. </summary>
		Array<T>* array_;
		/// <summary> Pocet prvkov v zozname. </summary>
		size_t size_;

	private:
		/// <summary> Rozsiri kapacitu zoznamu. </summary>
		void enlarge();

		/// <summary> Iterator pre ArrayList. </summary>
		class ArrayListIterator : public Iterator<T>
		{
		public:
			/// <summary> Konstruktor. </summary>
			/// <param name = "arrayList"> Zoznam, cez ktory iteruje. </param>
			/// <param name = "position"> Pozicia, na ktorej zacina. </param>
			ArrayListIterator(ArrayList<T>* arrayList, int position);

			/// <summary> Destruktor. </summary>
			~ArrayListIterator();

			/// <summary> Operator priradenia. Priradi do seba hodnotu druheho iteratora. </summary>
			/// <param name = "other"> Druhy iterator. </param>
			/// <returns> Vrati seba po priradeni. </returns>
			Iterator<T>& operator= (Iterator<T>& other) override;

			/// <summary> Porovna sa s druhym iteratorom na nerovnost. </summary>
			/// <param name = "other"> Druhy iterator. </param>
			/// <returns> True, ak sa iteratory nerovnaju, false inak. </returns>
			bool operator!=(Iterator<T>& other) override;

			/// <summary> Vrati data, na ktore aktualne ukazuje iterator. </summary>
			/// <returns> Data, na ktore aktualne ukazuje iterator. </returns>
			T operator*() override;

			/// <summary> Posunie iterator na dalsi prvok v strukture. </summary>
			/// <returns> Iterator na dalsi prvok v strukture. </returns>
			/// <remarks> Zvycajne vrati seba. Ak vrati iny iterator, povodny bude automaticky zruseny. </remarks>
			Iterator<T>& operator++() override;

		private:
			/// <summary> Zoznam, cez ktory iteruje. </summary>
			ArrayList<T>* arrayList_;
			/// <summary> Aktualna pozicia v zozname. </summary>
			int position_;
		};
	};

	template<typename T>
	inline ArrayList<T>::ArrayList() :
		List<T>(),
		array_(new Array<T>(4)),
		size_(0)
	{
	}

	template<typename T>
	inline ArrayList<T>::ArrayList(ArrayList<T>& other) :
		List<T>(),											//implicitne konstruktori predkov sa nemusia pisat 
		array_(new Array<T>(*other.array_)),
		size_(other.size_)
	{
	}

	template<typename T>
	inline ArrayList<T>::~ArrayList()
	{
		delete array_;
		array_ = nullptr;
		size_ = 0;
	}

	template<typename T>
	inline size_t ArrayList<T>::size()
	{
		return size_;
	}

	template<typename T>
	inline Structure& ArrayList<T>::assign(Structure& other)
	{
		//nesmiem pouzit assign z Array, lebo on kontroluje aj velkost a na tom nam pri ArrayListe nezalezi
		if (this != &other) {
			ArrayList<T>& otherArrayList = dynamic_cast<ArrayList<T>&>(other);
			delete array_;
			array_ = new Array<T>(*otherArrayList.array_);
			size_ = otherArrayList.size_;
		}
		return *this;
	}

	template<typename T>
	inline bool ArrayList<T>::equals(Structure& other)
	{
		// su typovo zhodne
		// ak su typovo rovnake, tak su rovnaku
		// skontrolovat velkost, 
		// nakoniec, treba porovnat prvky
		
		if (this != &other) {
			if (size_ == other.size()) {
				ArrayList<T>& otherArray = dynamic_cast<ArrayList<T>&>(other);
				for (int i = 0; i < size_; i++) {
					if (at(i) != otherArray.at(i)) {
						return false;
					}
				}
				return true;
			}
		}
		return false;
	}

	template<typename T>
	inline T& ArrayList<T>::at(int index)
	{
		// s pohladu zoznamu, nemozeme sahat na prvku pola, ktore su prazdne
		Utils::rangeCheckExcept(index, size_, "Invalid index.");
		return array_->at(index);
	}

	template<typename T>
	inline void ArrayList<T>::add(const T& data)
	{
		if (size_ == array_->size()) {
			enlarge();
		}
		array_->at(size_) = data;
		size_++;
	}

	template<typename T>
	inline void ArrayList<T>::insert(const T& data, int index)
	{
		//index = size_ ? add(data)
		//ak nie -> RangeCheckExcept
		//zabezpecenie kapacity -> Array::copy() vlozit na index+1, potrebujem vlozit size_- index pocet prvkov
		//zapisem potom na index

		if (index == size_) {
			add(data);
		}
		else {
			Utils::rangeCheckExcept(index, size_, "End of ArrayList");
			if (size_ == array_->size()) {
				enlarge();
			}
			Array<T>::copy(*array_, index, *array_, index + 1, size_ - index);
			array_->at(index) = data;
			size_++;
		}
	}

	template<typename T>
	inline bool ArrayList<T>::tryRemove(const T& data)
	{
		//chceme mat boolean, lebo skusame ci sa nieco podatilo 
		
		int index = getIndexOf(data);
		if (index != -1) {
			removeAt(index);				//tato metoda sa postara uz o vymazanie a zmensenie zoznamu
			return true;
		}
		return false;
	}

	template<typename T>
	inline T ArrayList<T>::removeAt(int index)
	{
		//pri arrayListe nevymazavame prvky, ktore v poli ostali, ale uz su za platnym indexom
		//keby sme potrebovali pouzit dany prvok, tak pri vkladani sa jednoducho vymaze

		T result = at(index);										//ma v sebe kontrolu platnosti indexu
		if (index != size_ - 1) {
			Array<T>::copy(*array_, index + 1, *array_, index, size_ - index - 1);
		}
		size_--;
		return result;
	}

	template<typename T>
	inline int ArrayList<T>::getIndexOf(const T& data)
	{
		for (int i = 0; i < size_; i++) {
			if (array_->at(i) == data) {
				return i;
			}
		}
		return -1;
	}

	template<typename T>
	inline void ArrayList<T>::clear()
	{
		size_ = 0;
	}

	template<typename T>
	inline Iterator<T>* ArrayList<T>::getBeginIterator()
	{
		return new ArrayListIterator(this, 0);
	}

	template<typename T>
	inline Iterator<T>* ArrayList<T>::getEndIterator()
	{
		return new ArrayListIterator(this, static_cast<int>(size_));		//nemoze byt posledny platny prvok, lebo potom by sa vo while nespracuje posledny platny prvok
	}

	template<typename T>
	inline void ArrayList<T>::enlarge()
	{
		//vytvor nove pole s velkostou (size_ * 2)
		//prekopirovat pole pomocou Array::copy(....)

		Array<T>* newArray = new Array<T>(array_->size() * 2);				//keby som to dal bez *, tak sa alokuje v Stacku
		Array<T>::copy(*array_, 0, *newArray, 0, size_);					//treba zdereferovat, aby sme sa dostli ku objektu
		delete array_;
		array_ = newArray;
	}

	template<typename T>
	inline ArrayList<T>::ArrayListIterator::ArrayListIterator(ArrayList<T>* arrayList, int position) :
		arrayList_(arrayList),
		position_(position)
	{
	}

	template<typename T>
	inline ArrayList<T>::ArrayListIterator::~ArrayListIterator()
	{
		arrayList_ = nullptr;
		position_ = 0;
	}

	template<typename T>
	inline Iterator<T>& ArrayList<T>::ArrayListIterator::operator=(Iterator<T>& other)
	{
		position_ = dynamic_cast<const ArrayListIterator&>(other).position_;
		return *this;
	}

	template<typename T>
	inline bool ArrayList<T>::ArrayListIterator::operator!=(Iterator<T>& other)
	{
		return position_ != dynamic_cast<const ArrayListIterator&>(other).position_;
	}

	template<typename T>
	inline T ArrayList<T>::ArrayListIterator::operator*()
	{
		return (*arrayList_)[position_];
	}

	template<typename T>
	inline Iterator<T>& ArrayList<T>::ArrayListIterator::operator++()
	{
		position_++;
		return *this;
	}

}