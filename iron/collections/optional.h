#pragma once
//Parker TenBroeck 2023

/// @brief A value which either holds another value or does not
/// @tparam T the value which this type might hold
template<typename T>
struct Option{
private:
    union{
        char _cloest_to_zst; 
        T _val;
    };
    /// @brief true if the the value in the union exists, false otherwise
    bool _state;
public:

    Option() : _cloest_to_zst(0), _state(false){}
    Option(T&& val) : _val(std::move(val)), _state(true){}
    Option(Option<T>&& val): _val(val._val), _state(val._state){
        val._state = false;
    }
    Option(const Option<T>& val): _val(val._val), _state(val._state){}

    /// @brief overload the boolean cast to return true if the option is So,e
    explicit operator bool() const {
        return this->is_some();
    }

    /// @brief  gets a reference to the value stored in here, if no value exists an exception is thrown
    /// @return a reference to the value stored in here (always value) 
    T& operator*(){
        if(!*this)
            throw std::runtime_error("Tried to unwrap a None");
        return _val;
    }

    /// @brief  gets a reference to the value stored in here, if no value exists an exception is thrown
    /// @return a reference to the value stored in here (always value) 
    const T& operator*() const {
        if(!*this)
            throw std::runtime_error("Tried to unwrap a None");
        return _val;
    }

    /// @brief  gets a reference to the value stored in here, if no value exists an exception is thrown
    /// @return a reference to the value stored in here (always value) 
    T& operator->(){
        if(!*this)
            throw std::runtime_error("Tried to unwrap a None");
        return _val;
    }

    /// @brief  gets a reference to the value stored in here, if no value exists an exception is thrown
    /// @return a reference to the value stored in here (always value) 
    const T& operator->() const{
        if(!*this)
            throw std::runtime_error("Tried to unwrap a None");
        return _val;
    }


    /// @return an optional containing a reference to the data stored in this optional. None if this optional is None
    [[nodiscard]] Option<T&> as_ref() {
        if (this->is_some()){
            return {this->_val};
        }else{
            return {};
        }
    }

    /// @return an optional containing a reference to the data stored in this optional. None if this optional is None
    [[nodiscard]] Option<const T&> as_ref() const {
        if (this->is_some()){
            return {this->_val};
        }else{
            return {};
        }
    }

    /// @return true if this option is Some, false otherwise
    [[nodiscard]] bool is_some() const{
        return this->_state;
    }

    /// @return true if this option is None, false otherwise
    [[nodiscard]] bool is_none() const{
        return !this->_state;
    }

    /// @return unwrap the Some varient of our Option moving it out. throwing an exception otherwise
    [[nodiscard]] T unwrap() {
        if(!this->_state)
            throw std::runtime_error("Unwrapped a None");
        return std::move(this->_val);
    }

    /// @return unwrap the Some varient of our Option moving it out.
    /// @warning if the varient is not Some it is UB
    [[nodiscard]] T unwrap_unchecked() {
        return std::move(this->_val);
    }

    ~Option() {
        if (!std::is_trivially_destructible<T>{}){
            // if the we are some run the destructor on our value
            if (this->is_some()){
                this->_val.~T();
            }
        }
    }
};

/// @brief A value which either holds another value or does not
/// @tparam T the value which this type might hold
template<typename T>
struct Option<T&>{
private:
    /// @brief null if the reference doesn't exist a valid pointer if the reference does
    T* raw;

public:
    Option() : raw(nullptr){}
    Option(T& val) : raw(&val){}
    Option(Option<T&>&& val): raw(val.raw){
        val.raw = nullptr;
    }
    Option(const Option<T>& val): raw(val.raw){}
    
    /// @brief overload the boolean cast to return true if the option is So,e
    operator bool() const {
        return this->is_some();
    }

    /// @brief  gets a reference to the value stored in here, if no value exists an exception is thrown
    /// @return a reference to the value stored in here (always value) 
    T& operator*(){
        if(!*this)
            throw std::runtime_error("Tried to unwrap a None");
        return *this->raw;
    }

    /// @brief  gets a reference to the value stored in here, if no value exists an exception is thrown
    /// @return a reference to the value stored in here (always value) 
    const T& operator*() const {
        if(!*this)
            throw std::runtime_error("Tried to unwrap a None");
        return *this->raw;
    }

    /// @brief  gets a reference to the value stored in here, if no value exists an exception is thrown
    /// @return a reference to the value stored in here (always value) 
    T& operator->(){
        if(!*this)
            throw std::runtime_error("Tried to unwrap a None");
        return *this->raw;
    }

    /// @brief  gets a reference to the value stored in here, if no value exists an exception is thrown
    /// @return a reference to the value stored in here (always value) 
    const T& operator->() const{
        if(!*this)
            throw std::runtime_error("Tried to unwrap a None");
        return *this->raw;
    }
    
    /// @return true if this option is Some, false otherwise
    [[nodiscard]] bool is_some() const{
        return this->raw != nullptr;
    }

    /// @return true if this option is None, false otherwise
    [[nodiscard]] bool is_none() const{
        return this->raw == nullptr;
    }

    /// @return unwrap the Some varient of our Option moving it out. throwing an exception otherwise
    [[nodiscard]] const T& unwrap() const{
        if (this->is_none())
            throw std::runtime_error("Unwrapped a None");
        return *this->raw;
    }

    /// @return unwrap the Some varient of our Option moving it out. throwing an exception otherwise
    [[nodiscard]] T& unwrap() {
        if (this->is_none())
            throw std::runtime_error("Unwrapped a None");
        return *this->raw;
    }

    /// @return unwrap the Some varient of our Option moving it out.
    /// @warning if the varient is not Some it is UB
    [[nodiscard]] const T& unwrap_unchecked() const{
        return *this->raw;
    }

    /// @return unwrap the Some varient of our Option moving it out.
    /// @warning if the varient is not Some it is UB
    [[nodiscard]] T& unwrap_unchecked() {
        return *this->raw;
    }
};