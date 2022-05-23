#pragma once

#include "priority_queue_sorted_array_list.h"
#include <stdexcept>

namespace structures
{
    static const size_t MIN_CAPACITY = 3;

    /// <summary> Prioritny front implementovany utriednym ArrayList-om s obmedzenou kapacitou. </summary>
    /// <typeparam name = "T"> Typ dat ukladanych v prioritnom fronte. </typepram>
    template<typename T>
    class PriorityQueueLimitedSortedArrayList : public PriorityQueueSortedArrayList<T>
    {
    public:
        /// <summary> Konstruktor. </summary>
        PriorityQueueLimitedSortedArrayList();

        PriorityQueueLimitedSortedArrayList(size_t capacity);

        /// <summary> Kopirovaci konstruktor. </summary>
        /// <param name = "other"> Prioritny front implementovany utriednym ArrayList-om s obmedzenou kapacitou, z ktoreho sa prevezmu vlastnosti. </param>
        PriorityQueueLimitedSortedArrayList(PriorityQueueLimitedSortedArrayList<T>& other);

        /// <summary> Priradenie struktury. </summary>
        /// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
        /// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
        Structure& assign(Structure& other) override;

        /// <summary> Vlozi prvok s danou prioritou do prioritneho frontu implementovaneho utriednym ArrayList-om s obmedzenou kapacitou. </summary>
        /// <param name = "priority"> Priorita vkladaneho prvku. </param>
        /// <param name = "data"> Vkladany prvok. </param>
        /// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front plny. </exception>
        void push(int priority, const T& data) override;

        /// <summary>
        ///  Vlozi prvok s danou prioritou do prioritneho frontu implementovaneho utriednym ArrayList-om s obmedzenou kapacitou.
        ///  V pripade, ze je prioritny front plny, odstrani polozku s najmensou prioritou z prioritneho frontu a vrati smernik na nu.
        ///  V opacnom pripade vrati nullptr.
        /// </summary>
        /// <param name = "priority"> Priorita vkladaneho prvku. </param>
        /// <param name = "data"> Vkladany prvok. </param>
        /// <returns> Smernik na odstranenu polozku alebo nullptr. </returns>
        PriorityQueueItem<T>* pushAndRemove(int priority, T data);

        /// <summary> Vrati najmensiu prioritu nachadzajucu sa v prioritnom fronte. </summary>
        /// <returns> Najmensiu priorita nachadzajuca sa v prioritnom fronte. </returns>
        int minPriority();

        /// <summary>
        ///  Pokusi sa zmenit kapacitu prioritneho frontu.
        ///  Kapacitu je mozne zmensit len ak nova kapacita nie je mensia ako aktualny pocet poloziek v prioritnom fronte.
        ///  V opacnom pripade nedojde k zmene kapacity.
        /// </summary>
        /// <param name = "capacity"> Nova kapacita. </param>
        /// <returns> true, ak sa kapacitu podarilo zmenit, false inak. </returns>
        bool trySetCapacity(size_t capacity);

        /// <summary>
        /// Getter pre maximalnu kapacitu utriedeneho prioritneho frontu. 
        /// </summary>
        /// <returns> Maximalnu kapacitu prioritneho frontu. </returns>
        size_t getCapacity();
    private:
        /// <summary> Kapacita prioritneho frontu. </summary>
        size_t capacity_;
    };

    template<typename T>
    PriorityQueueLimitedSortedArrayList<T>::PriorityQueueLimitedSortedArrayList() :
        PriorityQueueSortedArrayList<T>(),
        capacity_(MIN_CAPACITY)
    {
    }

    template<typename T>
    inline PriorityQueueLimitedSortedArrayList<T>::PriorityQueueLimitedSortedArrayList(size_t capacity) :
        PriorityQueueSortedArrayList<T>(),
        capacity_(capacity)
    {
    }

    template<typename T>
    PriorityQueueLimitedSortedArrayList<T>::PriorityQueueLimitedSortedArrayList(PriorityQueueLimitedSortedArrayList<T>& other) :
        PriorityQueueSortedArrayList<T>(other),
        capacity_(other.capacity_)
    {
    }

    template<typename T>
    inline Structure& PriorityQueueLimitedSortedArrayList<T>::assign(Structure& other)
    {
        auto otherQueue = dynamic_cast<PriorityQueueLimitedSortedArrayList<T>&>(other);
        capacity_ = otherQueue.capacity_;
        return PriorityQueueList<T>::assignPrioQueueList(otherQueue);
    }

    template<typename T>
    void PriorityQueueLimitedSortedArrayList<T>::push(int priority, const T& data)
    {
        if (list_->size() < capacity_) {
            PriorityQueueSortedArrayList<T>::push(priority, data);
        }
        else {
            throw std::logic_error("Limited queue is out of capacity !");
        }
    }

    template<typename T>
    inline PriorityQueueItem<T>* PriorityQueueLimitedSortedArrayList<T>::pushAndRemove(int priority, T data)
    {
        try {
            push(priority, data);
            return nullptr;
        }
        catch (const std::logic_error&) {
            auto popingItem = list_->removeAt(0);
            push(priority, data);
            return popingItem;
        }
    }

    template<typename T>
    inline int PriorityQueueLimitedSortedArrayList<T>::minPriority()
    {
        if (list_->isEmpty()) {
            throw std::logic_error("Limited queue is empty !");
        }
        return list_->at(0)->getPriority();
    }

    template<typename T>
    inline bool PriorityQueueLimitedSortedArrayList<T>::trySetCapacity(size_t capacity)
    {
        if (list_->size() < capacity && capacity > MIN_CAPACITY) {
            capacity_ = capacity;
            return true;
        }
        return false;
    }

    template<typename T>
    inline size_t PriorityQueueLimitedSortedArrayList<T>::getCapacity()
    {
        return capacity_;
    }
}