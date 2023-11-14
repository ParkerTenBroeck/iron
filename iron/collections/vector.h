#pragma once
//Parker TenBroeck 2023


#include "iron/collections/optional.h"
#include "iron/iter.h"

/// @brief A contiguous collection of items that is growable
/// @tparam T the type we want to store
template<typename T>
class Vec{
private:
    usize _len;
    usize _capacity;
    T* _data;

public:
    /// @brief default constructor
    Vec() : _len(0), _capacity(0), _data(nullptr){}

    /// @brief move constructor
    /// @param other the vector being moved out of
    Vec(Vec<T>&& other) : _len(other._len), _capacity(other._capacity), _data(other._data){
        other._data = nullptr;
        other._capacity = 0;
        other._len = 0;
    }

    /// @brief copy constructor
    /// @param other the vec we want to copy from
    Vec(const Vec<T>& other) : _len(0), _capacity(0), _data(nullptr){
        *this = Vec<T>::with_capacity(other.len());
        for(auto& val : other){
            this.push(val);
        }
    }

    /// @brief the point at which our vector starts
    /// @return the pointer to the first element in our vec
    T* begin() {
        return this->_data;
    }

    /// @brief the point past where our vector ends
    /// @return a pointer one past the last element of our vec
    T* end() {
        return this->_data + this->_len;
    }

    /// @brief the point at which our vector starts
    /// @return the pointer to the first element in our vec
    const T* begin() const {
        return this->_data;
    }

    /// @brief the point past where our vector ends
    /// @return a pointer one past the last element of our vec
    const T* end() const {
        return this->_data + this->_len;
    }

    /// @brief creates a vec with a pre allocated buffer (will round up size to nearest power of two)
    /// @param len the desired capacity of the vec
    /// @return a newly created vec
    static Vec<T> with_capacity(usize _capacity){
        Vec<T> vec;
        // calculate round up of nearest power of two
        usize i = 0;
        while(_capacity > 0){
            i ++;
            _capacity >>= 1;
        }
        // if the power is < 5 round up (32 elements)
        if (i < 5) i = 5;
        // calculate the actual number of elements
        _capacity = 1 << i;
        
        // set our capacity and allocate memory 
        vec._capacity = _capacity;
        vec._data = (T*)malloc(sizeof(T)*vec._capacity);
        return vec;
    }

    /// @brief creates a vec prefilled with `len` elements of value `with`
    /// @param len  the desired length of our vec 
    /// @param with the default value to fill our vec with
    /// @return the newly created vector
    static Vec<T> len_with(usize len, T with){
        Vec<T> vec = Vec<T>::with_capacity(len);
        for(vec._len = 0; vec._len < len; vec._len++){
            new (&vec._data[vec._len]) T(with);
        }
        return vec;
    }

    /// @brief gets a reference to a value at position `index`, if index is out of bounds a none is returned
    /// @param index the index desired
    /// @return Some if the index is in bounds, None if it was out of bounds 
    Option<const T&> get(usize index) const{
        if (index >= this->_len){
            return Option<const T&>();
        }else{
            return Option<const T&>(this->_data[index]);
        }
    }

    /// @brief gets a value at index and unwraps it
    /// @param index the desired index
    const T& operator[](usize index) const {
        return this->get(index).unwrap();
    }

    /// @brief gets a reference to a value at position `index`, if index is out of bounds a none is returned
    /// @param index the index desired
    /// @return Some if the index is in bounds, None if it was out of bounds 
    Option<T&> get(usize index) {
        if (index >= this->_len){
            return Option<T&>();
        }else{
            return Option<T&>(this->_data[index]);
        }
    }

    /// @brief gets a value at index and unwraps it
    /// @param index the desired index
    T& operator[](usize index) {
        return this->get(index).unwrap();
    }

    /// @brief determines if the vec is empty, has length zero
    /// @return true if the vec has no elements, false otherwise 
    bool is_empty(){
        return this->len() == 0;
    }

    /// @brief  pop an element from the last position in a vec
    /// @return None if the value doesn't exist and Some if there was some value to pop
    Option<T> pop(){
        if (this->is_empty()){
            return Option<T>();
        }else{
            // decrement out length and move out of our backing array
            return Option<T>(std::move(this->_data[--this->_len]));
        }
    }

    /// @brief pushes a new piece of data to the back of our vec 
    /// @param data the desiered value to push
    void push(T data){
        // if we have no more capacity in our backing array
        if (this->_len == this->_capacity){
            // if our backing array doesn't actually exist make a new backing array with 32 elements
            if (this->_capacity == 0){
                this->_capacity = 32;
                this->_data = (T*)malloc(sizeof(T)*this->_capacity);
            }else{
                // otherwise double our capacity and move all our old values into our new array
                this->_capacity *= 2;
                auto new_data = (T*)malloc(sizeof(T)*this->_capacity);
                for(usize i = 0; i < this->_len; i ++){
                    new (&new_data[i]) T(std::move(this->_data[i]));
                }
                // free the old data and update our pointer
                free(this->_data);
                this->_data = new_data;
            }
        }
        // construct a new value at the given address
        new (&this->_data[this->_len++]) T(std::move(data));
    }

    /// @brief gets the length (number of elements stored) in our vec
    /// @return the number of elements stored in our vec
    usize len() const{
        return this->_len;
    }

    /// @brief gets the capacity (number of elements that can be stored) in our vec at the given moment without re-allocating
    /// @return the number of elements we can have in the current backing array
    usize capacity() const{
        return this->_capacity;
    }

    /// @brief constructs an iterator over the elements of this vec
    /// @return a iterator over the elements of this vec
    SliceIter<T> iter() {
        return SliceIter<T>(this->begin(), this->end());
    }

    /// @brief constructs an iterator over the elements of this vec
    /// @return a iterator over the elements of this vec
    SliceIter<const T> iter() const {
        return SliceIter<const T>(this->begin(), this->end());
    }

    ~Vec(){
        if (!std::is_trivially_destructible<T>{}){
            // run the destructors of our elements that actually exist
            while(!this->is_empty())
                this->_data[--this->_len].~T();
        }
        // make sure we dont free nothing
        if(this->_data != nullptr)
            free(this->_data);
    }
};

