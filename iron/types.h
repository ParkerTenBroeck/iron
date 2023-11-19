#pragma once
//Parker TenBroeck 2023

#ifndef EXCLUDE_CPP_LIB
#include <cstdint>
#include <string>
#include <stdexcept>
#include <cstring>
#else
// #include <cstdint>
// #include <string>
// #include <stdexcept>
// #include <cstring>
#endif

#define UNUSED(x) (void)x;

struct Empty{};
enum class Infaliable{};

typedef std::string String;

// typedef std::int64_t isize;

typedef std::int64_t i64;
typedef std::int32_t i32;
typedef std::int16_t i16;
typedef std::int8_t  i8;

typedef std::size_t   usize;
typedef u_int64_t u64;
typedef u_int32_t u32;
typedef u_int16_t u16;
typedef u_int8_t  u8;

template<typename T>
using ref = std::reference_wrapper<T>;

// /// @brief  A wrapper around a reference
// /// @tparam T the type which we hold a reference to
// template<typename T>
// struct ref{
// private:
//     T* _ref;
// public:
//     /// @brief      constructs a wrapper around a reference of type T
//     /// @param val  the reference this value should hold 
//     ref(T& val) : _ref(&val){} 

//     /// @brief allows us to transparently use this type
//     operator T&(){
//         return this->get();
//     }
//     /// @brief  gets the reference of this type
//     /// @return a reference to a constant value of type T  
//     const T& get() const{
//         return *this->_ref;
//     }

//     /// @brief  gets the reference of this type
//     /// @return a reference to a value of type T  
//     T& get(){
//         return *this->_ref;
//     }
// };
