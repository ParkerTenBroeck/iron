#pragma once
//Parker TenBroeck 2023

#include "iron/types.h"
#include "iron/iter.h"

template<typename T>
struct RangeRev;

/// @brief A type representing a range of values (exclusive) from [start, end)
/// @tparam T  the type of value stored in the range
template<typename T>
struct Range{
private:
    T _start;
    T _end;

public:
    /// @brief constructs a new range with start and end [start, end)
    /// @param start the starting value
    /// @param end  the ending value
    Range(T start, T end) : _start(start), _end(end) {}

    /// @return A range representing this range but reversed
    RangeRev<T> rev() const {
        return RangeRev<T>{this->_end - 1, this->_start - 1};
    }

    /// @brief wraps this range in an enumerate iterator
    /// @return the enumerated iterator over this iterator
    EnumeratedIter<Range<T>> enumerate() const {
        return {{*this}};
    }

    /// @return the begining range where this iterator will start
    Range<T> begin() const {
        return {this->_start, this->_end};
    }

    /// @return the ending range where this iterator will end
    Range<T> end() const {
        return {this->_end, this->_end};
    }

    /// @return the calculated size of this iterator (how large the range is)
    T size() const {
        return this->_start - this->_end;
    }

    /// @return the current value of this iterator
    T operator*() const { 
        return this->_start; 
    }
    
    /// @return the current value of this iterator
    T operator->() { 
        return this->_start; 
    }
    
    /// @brief  increment out iterator (move to the next value in our range)
    /// @return a reference to this 
    Range<T>& operator++() {
        this->_start++;
        return *this;
    }
    
    /// @brief decremet our iterator (move to the previous value in our range)
    /// @return a reference to this
    Range<T>& operator--() {
        this->_start--;
        return *this;
    }
    
    /// @brief increment out iterator (move to the next value in our iterator) but return an iterator representing our current state
    /// @return the state of the iterator before this operation
    Range<T> operator++(int) {
        auto tmp = *this;
        ++(*this);
        return tmp;
    }
    
    /// @brief get an iterator that is decremented by one value
    /// @return a iterator decremented by one value to ourself
    Range<T> operator--(int) {
        auto tmp = *this;
        --(*this);
        return tmp;
    }    

    /// @brief determine if two iterators are equal 
    /// @return true if they are equal false otherwise
    friend bool operator==(const Range<T>& a, const Range<T>& b) {
        return a._start == b._start;
    }

    /// @brief determine if two iterators are not equal 
    /// @return false if they are equal true otherwise
    friend bool operator!=(const Range<T>& a, const Range<T>& b) {
        return a._start != b._start;
    }
};


/// @brief A type representing a range of values (exclusive) from [start, end) but whos iterator counts down
/// @tparam T  the type of value stored in the range
template<typename T>
struct RangeRev{
private:
    T _start;
    T _end;

public:
    /// @brief constructs a new range with start and end [start, end)
    /// @param start the starting value
    /// @param end  the ending value
    RangeRev(T start, T end) : _start(start), _end(end) {}

    /// @return A range representing this range but reversed
    Range<T> rev() const {
        return Range<T>{this->_end + 1, this->_start + 1};
    }

    /// @brief wraps this range in an enumerate iterator
    /// @return the enumerated iterator over this iterator
    EnumeratedIter<RangeRev<T>> enumerate() const {
        return {{*this}};
    }

    /// @return the begining range where this iterator will start
    RangeRev<T> begin() const {
        return {this->_start, this->_end};
    }

    /// @return the ending range where this iterator will end
    RangeRev<T> end() const {
        return {this->_end, this->_end};
    }

    /// @return the calculated size of this iterator (how large the range is)
    T size() const {
        return this->_start - this->_end;
    }

    /// @return the current value of this iterator
    T operator*() const {  
        return this->_start; 
    }
    
    /// @return the current value of this iterator
    T operator->() { 
        return this->_start; 
    }

    /// @brief  increment our iterator (move to the next value in our range)
    /// @return a reference to this 
    RangeRev<T>& operator++() {
        this->_start--;
        return *this;
    }
    
    /// @brief decremet our iterator (move to the previous value in our range)
    /// @return a reference to this
    RangeRev<T>& operator--() {
        this->_start++;
        return *this;
    }
    
    /// @brief increment out iterator (move to the next value in our iterator) but return an iterator representing our current state
    /// @return the state of the iterator before this operation
    RangeRev<T> operator++(int) {
        auto tmp = *this;
        --(*this);
        return tmp;
    }

    /// @brief get an iterator that is decremented by one value
    /// @return a iterator decremented by one value to ourself
    RangeRev<T> operator--(int) {
        auto tmp = *this;
        ++(*this);
        return tmp;
    }    

    /// @brief determine if two iterators are equal 
    /// @return true if they are equal false otherwise
    friend bool operator==(const RangeRev<T>& a, const RangeRev<T>& b) {
        return a._start == b._start;
    }

    /// @brief determine if two iterators are not equal 
    /// @return false if they are equal true otherwise
    friend bool operator!=(const RangeRev<T>& a, const RangeRev<T>& b) {
        return a._start != b._start;
    }
};