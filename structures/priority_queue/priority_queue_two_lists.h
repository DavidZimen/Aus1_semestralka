#pragma once

#include "priority_queue.h"
#include "priority_queue_limited_sorted_array_list.h"
#include "../list/linked_list.h"
#include <cmath>
#include <functional>
#include <iostream>

namespace structures
{
	/// <summary> Prioritny front implementovany dvojzoznamom. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prioritnom fronte. </typepram>
	/// <remarks> Implementacia efektivne vyuziva prioritny front implementovany utriednym ArrayList-om s obmedzenou kapacitou a LinkedList. </remarks>
	template<typename T>
	class PriorityQueueTwoLists : public PriorityQueue<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		PriorityQueueTwoLists();

		PriorityQueueTwoLists(PriorityQueueTwoLists<T>& other);

		PriorityQueueTwoLists(int typeOfStrategy);

		~PriorityQueueTwoLists();

		/// <summary> Priradenie struktury. </summary>
		/// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary> Vrati pocet prvkov v prioritnom fronte implementovanom dvojzoznamom. </summary>
		/// <returns> Pocet prvkov v prioritnom fronte implementovanom dvojzoznamom. </returns>
		size_t size() override;

		/// <summary> Vymaze obsah prioritneho frontu implementovaneho dvojzoznamom. </summary>
		void clear() override;

		/// <summary> Vlozi prvok s danou prioritou do prioritneho frontu. </summary>
		/// <param name = "priority"> Priorita vkladaneho prvku. </param>
		/// <param name = "data"> Vkladany prvok. </param>
		void push(int priority, const T& data) override;

		/// <summary> Odstrani prvok s najvacsou prioritou z prioritneho frontu implementovaneho dvojzoznamom. </summary>
		/// <returns> Odstraneny prvok. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>
		T pop() override;

		/// <summary> Vrati adresou prvok s najvacsou prioritou. </summary>
		/// <returns> Adresa, na ktorej sa nachadza prvok s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>
		T& peek() override;

		/// <summary> Vrati prioritu prvku s najvacsou prioritou. </summary>
		/// <returns> Priorita prvku s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>
		int peekPriority() override;

		/// <summary>
		/// Pomocna metoda, ktora re3trukturalizuje shortList_.
		/// IBA pre potreby testovania èasových zložitostí.
		/// </summary>
		/// <param name="capacity"> Nova capacita pre shortList_ </param>
		void restructureForTesting(size_t capacity);

	private:
		/// <summary>
		/// Pomocna, metoda na vycistenie longList_ od dat.
		/// Zabranuje sa nou duplicite kodu v metode assign.
		/// </summary>
		void clearLongList();

		/// <summary>
		/// Privatna metoda, ktora ma za ulohu restrukturalizovat listy.
		/// Iba ak je nova kapacita pripustna hodnota.
		/// </summary>
		/// <param name="capacity"> Nova kapacita pre shortList_ </param>
		void restructureShortList(size_t capacity);

	private:
		/// <summary> Smernik na prioritny front ako implementovany utriednym ArrayList-om s obmedzenou kapacitou . </summary>
		/// <remarks> Z pohladu dvojzoznamu sa jedna o kratsi utriedeny zoznam. </remarks>
		PriorityQueueLimitedSortedArrayList<T>* shortList_;

		/// <summary> Smernik na dlhsi neutriedeny zoznam. </summary>
		LinkedList<PriorityQueueItem<T>*>* longList_;

		/// <summary>
		/// Funkcia, ktora zabezpecuje expanznu strategiu.
		/// </summary>
		std::function<size_t(size_t)> expandStrategy_;

		/// <summary>
		/// Typ expanznej strategie pre testovanie 4 ulohy
		/// 1 - sqrt(N)
		/// 2 - N/2
		/// 3 - popCounter_ / 1000
		/// </summary>
		int typeOfStrategy_;

		/// <summary>
		/// Pocita kolko krat sa vykonala operacia pop()
		/// </summary>
		size_t pushCounter_;
	};

	template<typename T>
	PriorityQueueTwoLists<T>::PriorityQueueTwoLists() :
		shortList_(new PriorityQueueLimitedSortedArrayList<T>()),
		longList_(new LinkedList<PriorityQueueItem<T>*>()),
		typeOfStrategy_(1),
		pushCounter_(0)
	{
		expandStrategy_ = [](size_t queueSize) -> size_t {
			return std::round(std::sqrt(queueSize));
		};
	}

	template<typename T>
	PriorityQueueTwoLists<T>::PriorityQueueTwoLists(int typeOfStrategy) :
		shortList_(new PriorityQueueLimitedSortedArrayList<T>()),
		longList_(new LinkedList<PriorityQueueItem<T>*>()),
		typeOfStrategy_(typeOfStrategy),
		pushCounter_(0)
	{
		switch (typeOfStrategy) {
			case 2:
				expandStrategy_ = [](size_t queueSize) -> size_t {
					return std::round(queueSize / 2);
				};
				break;
			case 3:
				expandStrategy_ = [](size_t queueSize) -> size_t {
					return std::round(queueSize / 1000);
				};
				break;
			default:
				expandStrategy_ = [](size_t queueSize) -> size_t {
					return std::round(std::sqrt(queueSize));
				};
				break;
		}
	}

	template<typename T>
	PriorityQueueTwoLists<T>::PriorityQueueTwoLists(PriorityQueueTwoLists<T>& other) :
		PriorityQueueTwoLists<T>()
	{
		assign(other);
	}

	template<typename T>
	PriorityQueueTwoLists<T>::~PriorityQueueTwoLists()
	{
		clear();
		delete longList_;
		delete shortList_;
		shortList_ = nullptr;
		longList_ = nullptr;
		pushCounter_ = 0;
		expandStrategy_ = nullptr;
	}

	template<typename T>
	Structure& PriorityQueueTwoLists<T>::assign(Structure& other)
	{
		if (this != &other) {
			auto otherQueue = dynamic_cast<PriorityQueueTwoLists<T>*>(&other);

			// staci vycistit longList_, lebo shortList_ sa vycisti v metode assign()
			clearLongList();

			shortList_->assign(*otherQueue->shortList_);
			for (auto item : *otherQueue->longList_) {
				longList_->add(new PriorityQueueItem<T>(*item));
			}
		}

		return *this;
	}

	template<typename T>
	size_t PriorityQueueTwoLists<T>::size()
	{
		return shortList_->size() + longList_->size();
	}

	template<typename T>
	void PriorityQueueTwoLists<T>::clear()
	{
		shortList_->clear();
		clearLongList();
	}

	template<typename T>
	void PriorityQueueTwoLists<T>::push(int priority, const T& data)
	{
		if (shortList_->size() == 0 || priority < shortList_->minPriority()) {
			auto poppedItem = shortList_->pushAndRemove(priority, data);
			if (poppedItem != nullptr) {
				longList_->add(poppedItem);
			}
			pushCounter_++;
			return;
		}

		longList_->add(new PriorityQueueItem<T>(priority, data));
		pushCounter_++;
	}

	template<typename T>
	T PriorityQueueTwoLists<T>::pop()
	{
		T popData = shortList_->pop();

		if (shortList_->size() == 0 && longList_->size() != 0) {
			if (typeOfStrategy_ == 3) {
				restructureShortList(expandStrategy_(pushCounter_));
			}
			else {
				restructureShortList(expandStrategy_(longList_->size()));
			}

		}

		return popData;
	}

	template<typename T>
	T& PriorityQueueTwoLists<T>::peek()
	{
		return shortList_->peek();
	}

	template<typename T>
	int PriorityQueueTwoLists<T>::peekPriority()
	{
		return shortList_->peekPriority();
	}

	template<typename T>
	inline void PriorityQueueTwoLists<T>::restructureForTesting(size_t sizeOfQueue)
	{
		size_t capacity = expandStrategy_(sizeOfQueue);

		if (capacity != shortList_->getCapacity()) {
			restructureShortList(capacity);
		}
	}

	template<typename T>
	inline void PriorityQueueTwoLists<T>::restructureShortList(size_t capacity)
	{
		shortList_->trySetCapacity(capacity);

		auto helpList = new LinkedList<PriorityQueueItem<T>*>();

		while (longList_->size() != 0) {
			auto delItem = longList_->removeAt(0);
			PriorityQueueItem<T>* pushItem;
			if (shortList_->size() < shortList_->getCapacity()) {
				pushItem = shortList_->pushAndRemove(delItem->getPriority(), delItem->accessData());
				delete delItem;
			}
			else {
				if (delItem->getPriority() < shortList_->minPriority()) {
					pushItem = shortList_->pushAndRemove(delItem->getPriority(), delItem->accessData());
					delete delItem;
				}
				else {
					pushItem = delItem;
				}
			}

			if (pushItem != nullptr) {
				helpList->add(pushItem);
			}
		}
		delete longList_;
		longList_ = helpList;
	}

	template<typename T>
	inline void PriorityQueueTwoLists<T>::clearLongList()
	{
		for (PriorityQueueItem<T>* item : *longList_) {
			delete item;
		}
		longList_->clear();
	}
}