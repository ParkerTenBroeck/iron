#pragma once
//Parker TenBroeck 2023

#include "iron/types.h"
#include "iron/collections/queue.h"
#include "iron/collections/optional.h"

/// @brief A contiguous collection of items that is growable and can be pushed and pop from either side
/// @tparam T the type we want to store
template<typename T>
class Dqueue{
    
private:
    /// @brief the index of one past the front of our queue
    usize _head;
    /// @brief the index of the back of our queue
    usize _tail;
    /// @brief the number of elements in our queue
    usize _size;
    /// @brief the capacity of our backing array (always 2^n)
    usize _capacity;
    /// @brief a pointer to the backing array
    T* _data;

private:
    /// @brief check if we need to resize the backing array, doing so if needed
    /// @param reserve_front if we should leave a slot at the front of our backing array for an immediate pushback
    void check_resize(bool reserve_front){
        if (this->_size == this->_capacity){
            // if our capacity is 0 (no backing array)
            // allocate a new block of memory with 32 elements
            if (this->_capacity == 0){
                this->_capacity = 32;
                this->_data = (T*)malloc(sizeof(T)*this->_capacity);
            }else{
                auto old_capacity = this->_capacity;
                // double our backing array in size
                this->_capacity *= 2;
                auto tmp_arr = (T*)malloc(sizeof(T)*this->_capacity);

                // if we want to reserve an element in the first index of our array 
                // start at index 1 otherwise 0
                usize i = reserve_front?1:0;
                // the end is i + our current 
                usize end = i + this->_size;
                // for each element in our old backing array
                // move them into our our new array
                while(i <= end){
                    new (&tmp_arr[i])  T(std::move(this->_data[(this->_tail++) & (old_capacity - 1)]));
                    i++;
                }
                // free our old array
                free(this->_data);
                // update our pointer
                this->_data = tmp_arr;
                // the tail is the starting index 
                this->_tail = reserve_front?1:0;
                // make sure to add 1 to our head if we reserved a spot in the front
                this->_head = this->_size + reserve_front?1:0;
            }
        }
    }

    public:
    Dqueue(): _head(0), _tail(0), _size(0), _capacity(0), _data(nullptr) {}

    /// @return the number of elements currently stored in this queue
    usize len() const {
        return this->_size;
    }

    /// @brief determines of there are no elements in this queue
    /// @return true if there are no elements (size == 0) in the queue
    bool is_empty() const {
        return this->_size == 0;
    }

    /// @brief gets the total number of elements the backing array in this queue can hold
    /// @return  the number of elements this queue can hold before the backing array needs to be re-allocated
    usize capacity() const {
        return this->_capacity;
    }

    /// @brief push an new element to the front of the queue
    /// @param val the value to add to the collection
    void push_front(T val) {
        this->check_resize(false);
        // construct our data in its new location
        new (&this->_data[this->_head]) T(std::move(val));
        // increment our size and head index
        // making sure to wrap our head index if needed
        this->_size += 1;
        this->_head = (this->_head + 1) & (this->_capacity - 1);
    }
    
    /// @brief push an new element to the back of the queue 
    /// @param val the value to add to the collection
    void push_back(T val) {
        this->check_resize(true);
        // increment our size and decrement our tail index
        // making sure to wrap our tail if needed
        this->_size += 1;
        this->_tail = (this->_tail - 1) & (this->_capacity - 1);
        // construct our data in its new location
        new (&this->_data[this->_tail]) T(std::move(val));
    }

    /// @return return an optional of the back of the queue, moving it out of the collection if it exists. returning None if no elements exist
    Option<T> pop_back() {
        if (this->is_empty()){
            return Option<T>();
        }else{
            auto cur_tail = this->_tail;
            // decrement our size and increment our tail index
            // making sure to wrap our tail if needed
            this->_size -= 1;
            this->_tail = (cur_tail + 1) & (this->_capacity - 1);
            // move out of the most back element
            return Option<T>(std::move(this->_data[cur_tail]));
        }
    }

    /// @return get an optional reference to the back of the queue if no elements exist none is returned
    Option<const T&> peek_back() const {
         if (this->is_empty()){
            return Option<const T&>();
        }else{
            return Option<const T&>(this->_data[this->_tail]);
        }
    }
    
    /// @return return an optional of the front of the queue, moving it out of the collection if it exists. returning None if no elements exist
    Option<T> pop_front() {
        if (this->is_empty()){
            return Option<T>();
        }else{
            // decrement out size and head index
            // making sure to wrap our head
            this->_size -= 1;
            this->_head = (this->_head - 1) & (this->_capacity - 1);
            // move out of the most front element
            return Option<T>(std::move(this->_data[this->_head]));
        }
    }

    /// @return get an optional reference to the front of the queue if no elements exist none is returned
    Option<const T&> peek_front() const {
         if (this->is_empty()){
            return Option<const T&>();
        }else{
            return Option<const T&>(this->_data[(this->_head - 1) & (this->_capacity - 1)]);
        }
    }

    ~Dqueue(){
        if (!std::is_trivially_destructible<T>{}){
            // run the destructors on the remaining elements in our queue
            while(!this->is_empty()){
                this->_size -= 1;
                this->_head = (_head - 1) & (this->_capacity - 1);
                this->_data[this->_head].~T();
            }
        }
        free(this->_data);
    }
};