#pragma once
//Parker TenBroeck 2023

#include "iron/collections/optional.h"
#include "iron/types.h"



/// @brief A type representing a sucsess or error type, but not both
/// @tparam T Ok type 
/// @tparam E Error type
template<typename T, typename E>
struct Result{
private:
    // either ok or error
    union { 
        T _ok;
        E _err;
    };
    // the state (ok or err) of our value
    bool _state;

    const static bool STATE_OK = true;
    const static bool STATE_ERR = false;
    
public:
    /// @brief constructs a new ok varient 
    Result(T&& val) : _ok(std::move(val)), _state(STATE_OK){}
    
    /// @brief constructs a new err varient
    Result(E&& err) : _err(std::move(err)), _state(STATE_ERR){}

    /// @brief copy constructor 
    Result(const Result<T, E> &res){
        if (std::is_trivially_copyable<T>() && std::is_trivially_copyable<E>()){
            // bad but eh
            memcpy((void*)this, (void*)&res, sizeof(Result<T, E>));
        }else{  
            // if we cant get away with that do the right thing with placement new and copy
            this->_state = res._state;
            if (res.is_ok()){
                new (&this->_ok) T(res._ok);
            }else {
                new (&this->_err) E(res._err);
            }
        }
    }

    /// @brief move constructor 
    Result(Result<T, E> &&res){
        if (std::is_trivially_copyable<T>() && std::is_trivially_copyable<E>()){
            // bad but eh
            memcpy((void*)this, (void*)&res, sizeof(Result<T, E>));
        }else{
            // if we cant get away with that do the right thing with placement new and move
            this->_state = res._state;
            if (res.is_ok()){
                new (&this->_ok) T(std::move(res._ok));
            }else if(res.is_err()){
                new (&this->_err) E(std::move(res._err));
            }
        }
    }

    /// @brief Takes a reference to to the data in the result and return another result
    /// @return A result that takes reference to this result 
    [[nodiscard]] Result<ref<T>, ref<E>> as_ref(){
        if (this->is_ok()){
            return {this->_ok};
        }else{
            return {this->_err};
        }
    }

    /// @brief Takes a reference to to the data in the result and return another result
    /// @return A result that takes reference to this result 
    [[nodiscard]] Result<ref<const T>, ref<const E>> as_ref() const {
        if (this->is_ok()){
            return {this->_ok};
        }else{
            return {this->_err};
        }
    }
    
    /// @return returns true if this result is ok
    [[nodiscard]] bool is_ok() const{
        return this->_state == STATE_OK;
    }

    /// @return returns true if this result is err
    [[nodiscard]] bool is_err() const{
        return this->_state == STATE_ERR;
    }
    
    /// @return collapse our result into an option some if the result is ok or none if error
    [[nodiscard]] Option<T> ok() {
        if (this->is_ok()){
            return Option<T>(std::move(this->_ok));
        }else{
            return Option<T>();
        }
    }

    /// @return collapse our result into an option some if the result is error or none if ok
    [[nodiscard]] Option<E> err() {
        if (this->is_err()){
            return Option<E>(std::move(this->_err));
        }else{
            return Option<E>();
        }
    }

    /// @return unwrap the ok varient of our result moving it out. throwing an exception if the varient is err
    [[nodiscard]] T unwrap() {
        if (this->is_ok()){
            return std::move(this->_ok);
        }else{
            throw std::runtime_error("Unwraped on Err");
        }
    }

    /// @return unwrap the ok varient of our result moving it out.
    /// @warning if the varient is not ok it is UB
    [[nodiscard]] T unwrap_unchecked() {
        return std::move(this->_ok);
    }

    /// @return unwrap the err varient of our result moving it out. throwing an exception if the varient is ok
    [[nodiscard]] E unwrap_err() {
        if (this->is_err()){
            return std::move(this->_err);
        }else{
            throw std::runtime_error("Unwraped_err on Ok");
        }
    }
    /// @return unwrap the err varient of our result moving it out.
    /// @warning if the varient is not err it is UB
    [[nodiscard]] E unwrap_err_unchecked() {
        return std::move(this->_err);
    }

    ~Result() {
        // run the destructor of the varient that this result is
        if (this->is_ok()){
            if (!std::is_trivially_destructible<T>{}){
                this->_ok.~T();
            }
        }else if (!std::is_trivially_destructible<E>{}){
            this->_err.~E();
        }
    }
};