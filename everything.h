# 0 "./iron/prelude.h"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/nix/store/linb70pgp53f0kygxm5wk163dx22d681-glibc-2.37-45-dev/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "./iron/prelude.h"
# 1 "./iron/types.h" 1
       
# 18 "./iron/types.h"
struct Empty{};
enum class Infaliable{};

typedef std::string String;



typedef std::int64_t i64;
typedef std::int32_t i32;
typedef std::int16_t i16;
typedef std::int8_t i8;

typedef std::size_t usize;
typedef u_int64_t u64;
typedef u_int32_t u32;
typedef u_int16_t u16;
typedef u_int8_t u8;

template<typename T>
using ref = std::reference_wrapper<T>;
# 2 "./iron/prelude.h" 2
# 1 "./iron/ranges.h" 1
       



# 1 "./iron/iter.h" 1
       
# 10 "./iron/iter.h"
template<typename Iter>
using iter_arrow = typename std::result_of<decltype(&Iter::operator->)(Iter*)>::type;




template<typename Iter>
using iter_deref = typename std::result_of<decltype(&Iter::operator*)(Iter*)>::type;




template<typename Iter>
using iter_rev = typename std::result_of<decltype(&Iter::rev)(Iter*)>::type;





template<typename T>
struct Enumerated{
public:
    T val;
    usize index;
    Enumerated(T _val, usize _index) : val(_val), index(_index){}
};


template<typename T>
struct EnumeratedIterRev;



template<typename T>
struct EnumeratedIter{
private:

    T m_iter;

    usize m_index;

    EnumeratedIter(T _iter, usize _index) : m_iter(_iter), m_index(_index){}
public:
    EnumeratedIter(T _iter) : m_iter(_iter), m_index(0){}


    EnumeratedIterRev<iter_rev<T>> rev() {
        return {this->m_iter.rev()};
    }


    EnumeratedIter<T> begin() const {
        return this->m_iter.begin();
    }


    EnumeratedIter<T> end() const {
        return this->m_iter.end();
    }


    usize size() const {
        return this->m_iter.size();
    }


    Enumerated<iter_deref<T>> operator*() const {
        return Enumerated<iter_deref<T>>(*this->m_iter, this->m_index);
    }


    Enumerated<iter_arrow<T>> operator->() {
        return Enumerated<iter_arrow<T>>(*this->m_iter, this->m_index);
    }



    EnumeratedIter<T>& operator++() {
        ++this->m_iter;
        ++this->m_index;
        return *this;
    }



    EnumeratedIter<T>& operator--() {
        --this->m_iter;
        --this->m_index;
        return *this;
    }



    EnumeratedIter<T> operator++(int) {
        return {this->m_iter++, this->m_index++};
    }



    EnumeratedIter<T> operator--(int) {
        return {this->m_iter--, this->m_index--};
    }


    friend bool operator==(const EnumeratedIter<T>& a, const EnumeratedIter<T>& b) {
        return a.m_iter == b.m_iter;
    }


    friend bool operator!=(const EnumeratedIter<T>& a, const EnumeratedIter<T>& b) {
        return a.m_iter != b.m_iter;
    }
};




template<typename T>
struct EnumeratedIterRev{
private:

    T m_iter;

    usize m_index;

public:
    EnumeratedIterRev(T _iter) : m_iter(_iter), m_index(_iter.size() - 1){}


    EnumeratedIter<iter_rev<T>> rev() {
        return {this->m_iter.rev()};
    }


    EnumeratedIterRev<T> begin() const {
        return this->m_iter.begin();
    }


    EnumeratedIterRev<T> end() const {
        return this->m_iter.end();
    }


    usize size() const {
        return this->m_iter.size();
    }


    Enumerated<iter_deref<T>> operator*() const {
        return Enumerated<iter_deref<T>>(*this->m_iter, this->m_index);
    }


    Enumerated<iter_arrow<T>> operator->() {
        return Enumerated<iter_arrow<T>>(*this->m_iter, this->m_index);
    }



    EnumeratedIterRev<T>& operator++() {
        ++this->m_iter;
        --this->m_index;
        return *this;
    }



    EnumeratedIterRev<T>& operator--() {
        --this->m_iter;
        ++this->m_index;
        return *this;
    }



    EnumeratedIterRev<T> operator++(int) {
        return {this->m_iter++, this->m_index--};
    }



    EnumeratedIterRev<T> operator--(int) {
        return {this->m_iter--, this->m_index++};
    }


    friend bool operator==(const EnumeratedIterRev<T>& a, const EnumeratedIterRev<T>& b) {
        return a.m_iter == b.m_iter;
    }


    friend bool operator!=(const EnumeratedIterRev<T>& a, const EnumeratedIterRev<T>& b) {
        return a.m_iter != b.m_iter;
    }
};

template<typename T>
struct SliceIterRev;



template<typename T>
struct SliceIter{
private:
    T* _start;
    T* _end;
public:
    SliceIter(const SliceIter<T>& _other) : _start(_other._start), _end(_other._end){}
    SliceIter(T* start, T* end) : _start(start), _end(end){}


    SliceIterRev<T> rev() const{
        return SliceIterRev<T>{this->_end - 1, this->_start - 1};
    }


    EnumeratedIter<SliceIter<T>> enumerate() const {
        return {{*this}};
    }


    EnumeratedIter<SliceIter<T>> enumerate() {
        return {{*this}};
    }


    SliceIter<T> begin() const {
        return {this->_start, this->_end};
    }


    SliceIter<T> end() const {
        return {this->_end, this->_end};
    }


    usize size() const {
        return (((usize)this->_end) - ((usize)this->_start)) / sizeof(T);
    }


    const T& operator*() const {
        return *this->_start;
    }


    T& operator->() {
        return *this->_start;
    }



    SliceIter<T>& operator++() {
        this->_start++;
        return *this;
    }



    SliceIter<T>& operator--() {
        this->_start--;
        return *this;
    }



    SliceIter<T> operator++(int) {
        auto tmp = *this;
        ++(*this);
        return tmp;
    }



    SliceIter<T> operator--(int) {
        auto tmp = *this;
        --(*this);
        return tmp;
    }


    friend bool operator==(const SliceIter<T>& a, const SliceIter<T>& b) {
        return a._start == b._start;
    }


    friend bool operator!=(const SliceIter<T>& a, const SliceIter<T>& b) {
        return a._start != b._start;
    }
};




template<typename T>
struct SliceIterRev{
private:
    T* _start;
    T* _end;
public:
    SliceIterRev(T* start, T* end) : _start(start), _end(end){}


    SliceIter<T> rev() const{
        return SliceIter<T>{this->_end + 1, this->_start + 1};
    }


    EnumeratedIter<SliceIterRev<T>> enumerate() const {
        return {{this->_start, this->_end}};
    }


    EnumeratedIter<SliceIterRev<T>> enumerate() {
        return {{this->_start, this->_end}};
    }


    SliceIterRev<T> begin() const {
        return {this->_start, this->_end};
    }


    SliceIterRev<T> end() const {
        return {this->_end, this->_end};
    }


    usize size() const {
        return (((usize)this->_start) - ((usize)this->_end)) / sizeof(T);
    }


    const T& operator*() const{
        return *this->_start;
    }


    T& operator->(){
        return this->_start;
    }



    SliceIterRev<T>& operator++() {
        this->_start--;
        return *this;
    }



    SliceIterRev<T>& operator--() {
        this->_start++;
        return *this;
    }



    SliceIterRev<T> operator++(int) {
        auto tmp = *this;
        --(*this);
        return tmp;
    }



    SliceIterRev<T> operator--(int) {
        auto tmp = *this;
        ++(*this);
        return tmp;
    }


    friend bool operator==(const SliceIterRev<T>& a, const SliceIterRev<T>& b) {
        return a._start == b._start;
    }


    friend bool operator!=(const SliceIterRev<T>& a, const SliceIterRev<T>& b) {
        return a._start != b._start;
    }
};
# 6 "./iron/ranges.h" 2

template<typename T>
struct RangeRev;



template<typename T>
struct Range{
private:
    T _start;
    T _end;

public:



    Range(T start, T end) : _start(start), _end(end) {}


    RangeRev<T> rev() const {
        return RangeRev<T>{this->_end - 1, this->_start - 1};
    }



    EnumeratedIter<Range<T>> enumerate() const {
        return {{*this}};
    }


    Range<T> begin() const {
        return {this->_start, this->_end};
    }


    Range<T> end() const {
        return {this->_end, this->_end};
    }


    T size() const {
        return this->_start - this->_end;
    }


    T operator*() const {
        return this->_start;
    }


    T operator->() {
        return this->_start;
    }



    Range<T>& operator++() {
        this->_start++;
        return *this;
    }



    Range<T>& operator--() {
        this->_start--;
        return *this;
    }



    Range<T> operator++(int) {
        auto tmp = *this;
        ++(*this);
        return tmp;
    }



    Range<T> operator--(int) {
        auto tmp = *this;
        --(*this);
        return tmp;
    }



    friend bool operator==(const Range<T>& a, const Range<T>& b) {
        return a._start == b._start;
    }



    friend bool operator!=(const Range<T>& a, const Range<T>& b) {
        return a._start != b._start;
    }
};




template<typename T>
struct RangeRev{
private:
    T _start;
    T _end;

public:



    RangeRev(T start, T end) : _start(start), _end(end) {}


    Range<T> rev() const {
        return Range<T>{this->_end + 1, this->_start + 1};
    }



    EnumeratedIter<RangeRev<T>> enumerate() const {
        return {{*this}};
    }


    RangeRev<T> begin() const {
        return {this->_start, this->_end};
    }


    RangeRev<T> end() const {
        return {this->_end, this->_end};
    }


    T size() const {
        return this->_start - this->_end;
    }


    T operator*() const {
        return this->_start;
    }


    T operator->() {
        return this->_start;
    }



    RangeRev<T>& operator++() {
        this->_start--;
        return *this;
    }



    RangeRev<T>& operator--() {
        this->_start++;
        return *this;
    }



    RangeRev<T> operator++(int) {
        auto tmp = *this;
        --(*this);
        return tmp;
    }



    RangeRev<T> operator--(int) {
        auto tmp = *this;
        ++(*this);
        return tmp;
    }



    friend bool operator==(const RangeRev<T>& a, const RangeRev<T>& b) {
        return a._start == b._start;
    }



    friend bool operator!=(const RangeRev<T>& a, const RangeRev<T>& b) {
        return a._start != b._start;
    }
};
# 3 "./iron/prelude.h" 2

# 1 "./iron/collections/optional.h" 1
       




template<typename T>
struct Option{
private:
    union{
        char _cloest_to_zst;
        T _val;
    };

    bool _exists;
public:

    Option() : _cloest_to_zst(0), _exists(false){}
    Option(T&& val) : _val(std::move(val)), _exists(true){}
    Option(Option<T>&& val): _val(val._val), _exists(val._exists){
        val._exists = false;
    }
    Option(const Option<T>& val): _val(val._val), _exists(val._exists){}


    explicit operator bool() const {
        return this->is_some();
    }



    T& operator*(){
        if(!*this)
            throw std::runtime_error("Tried to unwrap a None");
        return _val;
    }



    const T& operator*() const {
        if(!*this)
            throw std::runtime_error("Tried to unwrap a None");
        return _val;
    }



    T& operator->(){
        if(!*this)
            throw std::runtime_error("Tried to unwrap a None");
        return _val;
    }



    const T& operator->() const{
        if(!*this)
            throw std::runtime_error("Tried to unwrap a None");
        return _val;
    }



    [[nodiscard]] Option<T&> as_ref() {
        if (this->is_some()){
            return {this->_val};
        }else{
            return {};
        }
    }


    [[nodiscard]] Option<const T&> as_ref() const {
        if (this->is_some()){
            return {this->_val};
        }else{
            return {};
        }
    }


    [[nodiscard]] bool is_some() const{
        return this->_exists;
    }


    [[nodiscard]] bool is_none() const{
        return !this->_exists;
    }


    [[nodiscard]] T unwrap() {
        if(!this->_exists)
            throw std::runtime_error("Unwrapped a None");
        return std::move(this->_val);
    }



    [[nodiscard]] T unwrap_unchecked() {
        return std::move(this->_val);
    }

    ~Option() {
        if (!std::is_trivially_destructible<T>{}){

            if (this->is_some()){
                this->_val.~T();
            }
        }
        std::optional
    }
};



template<typename T>
struct Option<T&>{
private:

    union{
        T* raw;
        ref<T> _ref;
    };
    bool _exists;

public:
    Option() : raw(nullptr), _exists(false){}
    Option(T& val) : raw(&val), _exists(true){}
    Option(Option<T&>&& val): raw(val.raw), _exists(val._exists){
        val.raw = nullptr;
    }
    Option(const Option<T>& val): raw(val.raw), _exists(val.exists){}


    operator bool() const {
        return this->is_some();
    }



    T& operator*(){
        if(!*this)
            throw std::runtime_error("Tried to unwrap a None");
        return *this->raw;
    }



    const T& operator*() const {
        if(!*this)
            throw std::runtime_error("Tried to unwrap a None");
        return *this->raw;
    }



    T& operator->(){
        if(!*this)
            throw std::runtime_error("Tried to unwrap a None");
        return *this->raw;
    }



    const T& operator->() const{
        if(!*this)
            throw std::runtime_error("Tried to unwrap a None");
        return *this->raw;
    }


    [[nodiscard]] Option<ref<ref<T>>> as_ref() {
        if (this->is_some()){
            return {this->_ref};
        }else{
            return {};
        }
    }


    [[nodiscard]] Option<ref<const ref<T>>> as_ref() const {
        if (this->is_som()()){
            return {this->_ref};
        }else{
            return {};
        }
    }


    [[nodiscard]] bool is_some() const{
        return this->_exists;
    }


    [[nodiscard]] bool is_none() const{
        return !this->_exists;
    }


    [[nodiscard]] const T& unwrap() const{
        if (this->is_none())
            throw std::runtime_error("Unwrapped a None");
        return *this->raw;
    }


    [[nodiscard]] T& unwrap() {
        if (this->is_none())
            throw std::runtime_error("Unwrapped a None");
        return *this->raw;
    }



    [[nodiscard]] const T& unwrap_unchecked() const{
        return *this->raw;
    }



    [[nodiscard]] T& unwrap_unchecked() {
        return *this->raw;
    }
};
# 5 "./iron/prelude.h" 2
# 1 "./iron/collections/result.h" 1
       





# 1 "./iron/collections/_result.h" 1






template<typename Tr, typename Er>
# 24 "./iron/collections/_result.h"
        struct Result{




private:

    union {



        Tr _ok;





        Er _err;

    };

    bool _state;

    const static bool STATE_OK = true;
    const static bool STATE_ERR = false;

public:





    Result(Tr&& val) : _ok(std::move(val)), _state(STATE_OK){}







    Result(Er&& val) : _err(std::move(val)), _state(STATE_ERR){}



    Result(const Result<Tr, Er> &res){
        if (std::is_trivially_copyable<Tr>() && std::is_trivially_copyable<Er>()){

            memcpy((void*)this, (void*)&res, sizeof(Result<Tr, Er>));
        }else{

            this->_state = res._state;
            if (res.is_ok()){



                    new (&this->_ok) Tr(res._ok);

            }else {



                    new (&this->_err) Er(res._err);

            }
        }
    }


    Result(Result<Tr, Er> &&res){
        if (std::is_trivially_copyable<Tr>() && std::is_trivially_copyable<Er>()){

            memcpy((void*)this, (void*)&res, sizeof(Result<Tr, Er>));
        }else{

            this->_state = res._state;
            if (res.is_ok()){



                    new (&this->_ok) Tr(res._ok);

            }else if(res.is_err()){



                    new (&this->_err) Er(res._err);

            }
        }
    }



    [[nodiscard]] Result<ref<Tr>, ref<Er>> as_ref(){
        if (this->is_ok()){
            return {this->_ok};
        }else{
            return {this->_err};
        }
    }



    [[nodiscard]] Result<ref<const Tr>, ref<const Er>> as_ref() const {
        if (this->is_ok()){
            return {this->_ok};
        }else{
            return {this->_err};
        }
    }


    [[nodiscard]] bool is_ok() const{
        return this->_state == STATE_OK;
    }


    [[nodiscard]] bool is_err() const{
        return this->_state == STATE_ERR;
    }


    [[nodiscard]] Option<Tr> ok() {
        if (this->is_ok()){
            return Option<Tr>(std::move(this->_ok));
        }else{
            return Option<Tr>();
        }
    }


    [[nodiscard]] Option<Er> err() {
        if (this->is_err()){
            return Option<Er>(std::move(this->_err));
        }else{
            return Option<Er>();
        }
    }


    [[nodiscard]] Tr unwrap() {
        if (this->is_ok()){
            return std::move(this->_ok);
        }else{
            throw std::runtime_error("Unwraped on Err");
        }
    }



    [[nodiscard]] Tr unwrap_unchecked() {
        return std::move(this->_ok);
    }


    [[nodiscard]] Er unwrap_err() {
        if (this->is_err()){
            return std::move(this->_err);
        }else{
            throw std::runtime_error("Unwraped_err on Ok");
        }
    }


    [[nodiscard]] Er unwrap_err_unchecked() {
        return std::move(this->_err);
    }
# 216 "./iron/collections/_result.h"
~Result() {

    if (this->is_ok()){


        if (!std::is_trivially_destructible<Tr>{}){
            this->_ok.~Tr();
        }

    }else if (!std::is_trivially_destructible<Er>{}){

        this->_err.~Er();

    }
}


};
# 8 "./iron/collections/result.h" 2

# 1 "./iron/collections/_result.h" 1






template<typename Tr, typename Er>






        struct Result<Tr&, Er>{
# 29 "./iron/collections/_result.h"
private:

    union {

        ref<Tr> _ok;







        Er _err;

    };

    bool _state;

    const static bool STATE_OK = true;
    const static bool STATE_ERR = false;

public:


    Result(Tr& val) : _ok(val), _state(STATE_OK){}
# 64 "./iron/collections/_result.h"
    Result(Er&& val) : _err(std::move(val)), _state(STATE_ERR){}



    Result(const Result<Tr&, Er> &res){
        if (std::is_trivially_copyable<Tr&>() && std::is_trivially_copyable<Er>()){

            memcpy((void*)this, (void*)&res, sizeof(Result<Tr&, Er>));
        }else{

            this->_state = res._state;
            if (res.is_ok()){

                    this->_ok = res._ok;



            }else {



                    new (&this->_err) Er(res._err);

            }
        }
    }


    Result(Result<Tr&, Er> &&res){
        if (std::is_trivially_copyable<Tr&>() && std::is_trivially_copyable<Er>()){

            memcpy((void*)this, (void*)&res, sizeof(Result<Tr&, Er>));
        }else{

            this->_state = res._state;
            if (res.is_ok()){

                    this->_ok = res._ok;



            }else if(res.is_err()){



                    new (&this->_err) Er(res._err);

            }
        }
    }



    [[nodiscard]] Result<ref<Tr>, ref<Er>> as_ref(){
        if (this->is_ok()){
            return {this->_ok};
        }else{
            return {this->_err};
        }
    }



    [[nodiscard]] Result<ref<const Tr>, ref<const Er>> as_ref() const {
        if (this->is_ok()){
            return {this->_ok};
        }else{
            return {this->_err};
        }
    }


    [[nodiscard]] bool is_ok() const{
        return this->_state == STATE_OK;
    }


    [[nodiscard]] bool is_err() const{
        return this->_state == STATE_ERR;
    }


    [[nodiscard]] Option<Tr&> ok() {
        if (this->is_ok()){
            return Option<Tr&>(std::move(this->_ok));
        }else{
            return Option<Tr&>();
        }
    }


    [[nodiscard]] Option<Er> err() {
        if (this->is_err()){
            return Option<Er>(std::move(this->_err));
        }else{
            return Option<Er>();
        }
    }


    [[nodiscard]] Tr& unwrap() {
        if (this->is_ok()){
            return std::move(this->_ok);
        }else{
            throw std::runtime_error("Unwraped on Err");
        }
    }



    [[nodiscard]] Tr& unwrap_unchecked() {
        return std::move(this->_ok);
    }


    [[nodiscard]] Er unwrap_err() {
        if (this->is_err()){
            return std::move(this->_err);
        }else{
            throw std::runtime_error("Unwraped_err on Ok");
        }
    }


    [[nodiscard]] Er unwrap_err_unchecked() {
        return std::move(this->_err);
    }






~Result() {
    if (this->is_err()){
        if (!std::is_trivially_destructible<Er>{}){
            this->_err.~Er();
        }
    }
}
# 233 "./iron/collections/_result.h"
};
# 10 "./iron/collections/result.h" 2


# 1 "./iron/collections/_result.h" 1






template<typename Tr, typename Er>
# 20 "./iron/collections/_result.h"
        struct Result<Tr, Er&>{
# 29 "./iron/collections/_result.h"
private:

    union {



        Tr _ok;



        ref<Er> _err;



    };

    bool _state;

    const static bool STATE_OK = true;
    const static bool STATE_ERR = false;

public:





    Result(Tr&& val) : _ok(std::move(val)), _state(STATE_OK){}




    Result(Er& val) : _err(val), _state(STATE_ERR){}






    Result(const Result<Tr, Er&> &res){
        if (std::is_trivially_copyable<Tr>() && std::is_trivially_copyable<Er&>()){

            memcpy((void*)this, (void*)&res, sizeof(Result<Tr, Er&>));
        }else{

            this->_state = res._state;
            if (res.is_ok()){



                    new (&this->_ok) Tr(res._ok);

            }else {

                    this->_err = res._err;



            }
        }
    }


    Result(Result<Tr, Er&> &&res){
        if (std::is_trivially_copyable<Tr>() && std::is_trivially_copyable<Er&>()){

            memcpy((void*)this, (void*)&res, sizeof(Result<Tr, Er&>));
        }else{

            this->_state = res._state;
            if (res.is_ok()){



                    new (&this->_ok) Tr(res._ok);

            }else if(res.is_err()){

                    this->_err = res._err;



            }
        }
    }



    [[nodiscard]] Result<ref<Tr>, ref<Er>> as_ref(){
        if (this->is_ok()){
            return {this->_ok};
        }else{
            return {this->_err};
        }
    }



    [[nodiscard]] Result<ref<const Tr>, ref<const Er>> as_ref() const {
        if (this->is_ok()){
            return {this->_ok};
        }else{
            return {this->_err};
        }
    }


    [[nodiscard]] bool is_ok() const{
        return this->_state == STATE_OK;
    }


    [[nodiscard]] bool is_err() const{
        return this->_state == STATE_ERR;
    }


    [[nodiscard]] Option<Tr> ok() {
        if (this->is_ok()){
            return Option<Tr>(std::move(this->_ok));
        }else{
            return Option<Tr>();
        }
    }


    [[nodiscard]] Option<Er&> err() {
        if (this->is_err()){
            return Option<Er&>(std::move(this->_err));
        }else{
            return Option<Er&>();
        }
    }


    [[nodiscard]] Tr unwrap() {
        if (this->is_ok()){
            return std::move(this->_ok);
        }else{
            throw std::runtime_error("Unwraped on Err");
        }
    }



    [[nodiscard]] Tr unwrap_unchecked() {
        return std::move(this->_ok);
    }


    [[nodiscard]] Er& unwrap_err() {
        if (this->is_err()){
            return std::move(this->_err);
        }else{
            throw std::runtime_error("Unwraped_err on Ok");
        }
    }


    [[nodiscard]] Er& unwrap_err_unchecked() {
        return std::move(this->_err);
    }
# 207 "./iron/collections/_result.h"
~Result() {

    if (this->is_ok()){
        if (!std::is_trivially_destructible<Tr>{}){
            this->_ok.~Tr();
        }
    }
}
# 233 "./iron/collections/_result.h"
};
# 13 "./iron/collections/result.h" 2

# 1 "./iron/collections/_result.h" 1






template<typename Tr, typename Er>


        struct Result<Tr&, Er&>{
# 29 "./iron/collections/_result.h"
private:

    union {

        ref<Tr> _ok;





        ref<Er> _err;



    };

    bool _state;

    const static bool STATE_OK = true;
    const static bool STATE_ERR = false;

public:


    Result(Tr& val) : _ok(val), _state(STATE_OK){}







    Result(Er& val) : _err(val), _state(STATE_ERR){}






    Result(const Result<Tr&, Er&> &res){
        if (std::is_trivially_copyable<Tr&>() && std::is_trivially_copyable<Er&>()){

            memcpy((void*)this, (void*)&res, sizeof(Result<Tr&, Er&>));
        }else{

            this->_state = res._state;
            if (res.is_ok()){

                    this->_ok = res._ok;



            }else {

                    this->_err = res._err;



            }
        }
    }


    Result(Result<Tr&, Er&> &&res){
        if (std::is_trivially_copyable<Tr&>() && std::is_trivially_copyable<Er&>()){

            memcpy((void*)this, (void*)&res, sizeof(Result<Tr&, Er&>));
        }else{

            this->_state = res._state;
            if (res.is_ok()){

                    this->_ok = res._ok;



            }else if(res.is_err()){

                    this->_err = res._err;



            }
        }
    }



    [[nodiscard]] Result<ref<Tr>, ref<Er>> as_ref(){
        if (this->is_ok()){
            return {this->_ok};
        }else{
            return {this->_err};
        }
    }



    [[nodiscard]] Result<ref<const Tr>, ref<const Er>> as_ref() const {
        if (this->is_ok()){
            return {this->_ok};
        }else{
            return {this->_err};
        }
    }


    [[nodiscard]] bool is_ok() const{
        return this->_state == STATE_OK;
    }


    [[nodiscard]] bool is_err() const{
        return this->_state == STATE_ERR;
    }


    [[nodiscard]] Option<Tr&> ok() {
        if (this->is_ok()){
            return Option<Tr&>(std::move(this->_ok));
        }else{
            return Option<Tr&>();
        }
    }


    [[nodiscard]] Option<Er&> err() {
        if (this->is_err()){
            return Option<Er&>(std::move(this->_err));
        }else{
            return Option<Er&>();
        }
    }


    [[nodiscard]] Tr& unwrap() {
        if (this->is_ok()){
            return std::move(this->_ok);
        }else{
            throw std::runtime_error("Unwraped on Err");
        }
    }



    [[nodiscard]] Tr& unwrap_unchecked() {
        return std::move(this->_ok);
    }


    [[nodiscard]] Er& unwrap_err() {
        if (this->is_err()){
            return std::move(this->_err);
        }else{
            throw std::runtime_error("Unwraped_err on Ok");
        }
    }


    [[nodiscard]] Er& unwrap_err_unchecked() {
        return std::move(this->_err);
    }
# 233 "./iron/collections/_result.h"
};
# 15 "./iron/collections/result.h" 2
# 6 "./iron/prelude.h" 2
# 1 "./iron/collections/vector.h" 1
       
# 10 "./iron/collections/vector.h"
template<typename T>
class Vec{
private:
    usize _len;
    usize _capacity;
    T* _data;

public:

    Vec() : _len(0), _capacity(0), _data(nullptr){}



    Vec(Vec<T>&& other) : _len(other._len), _capacity(other._capacity), _data(other._data){
        other._data = nullptr;
        other._capacity = 0;
        other._len = 0;
    }



    Vec(const Vec<T>& other) : _len(0), _capacity(0), _data(nullptr){
        *this = std::move(Vec<T>::with_capacity(other.len()));
        for(auto& val : other){
            this.push(val);
        }
    }



    T* begin() {
        return this->_data;
    }



    T* end() {
        return this->_data + this->_len;
    }



    const T* begin() const {
        return this->_data;
    }



    const T* end() const {
        return this->_data + this->_len;
    }




    static Vec<T> with_capacity(usize _capacity){
        Vec<T> vec;

        usize i = 0;
        while(_capacity > 0){
            i ++;
            _capacity >>= 1;
        }

        if (i < 5) i = 5;

        _capacity = 1 << i;


        vec._capacity = _capacity;
        vec._data = (T*)malloc(sizeof(T)*vec._capacity);
        return vec;
    }





    static Vec<T> len_with(usize len, T with){
        Vec<T> vec = Vec<T>::with_capacity(len);
        for(vec._len = 0; vec._len < len; vec._len++){
            new (&vec._data[vec._len]) T(with);
        }
        return vec;
    }




    Option<const T&> get(usize index) const{
        if (index >= this->_len){
            return Option<const T&>();
        }else{
            return Option<const T&>(this->_data[index]);
        }
    }



    const T& operator[](usize index) const {
        return this->get(index).unwrap();
    }




    Option<T&> get(usize index) {
        if (index >= this->_len){
            return Option<T&>();
        }else{
            return Option<T&>(this->_data[index]);
        }
    }



    T& operator[](usize index) {
        return this->get(index).unwrap();
    }



    bool is_empty(){
        return this->len() == 0;
    }



    Option<T> pop(){
        if (this->is_empty()){
            return Option<T>();
        }else{

            return Option<T>(std::move(this->_data[--this->_len]));
        }
    }



    void push(T data){

        if (this->_len == this->_capacity){

            if (this->_capacity == 0){
                this->_capacity = 32;
                this->_data = (T*)malloc(sizeof(T)*this->_capacity);
            }else{

                this->_capacity *= 2;
                auto new_data = (T*)malloc(sizeof(T)*this->_capacity);
                for(usize i = 0; i < this->_len; i ++){
                    new (&new_data[i]) T(std::move(this->_data[i]));
                }

                free(this->_data);
                this->_data = new_data;
            }
        }

        new (&this->_data[this->_len++]) T(std::move(data));
    }



    usize len() const{
        return this->_len;
    }



    usize capacity() const{
        return this->_capacity;
    }



    SliceIter<T> iter() {
        return SliceIter<T>(this->begin(), this->end());
    }



    SliceIter<const T> iter() const {
        return SliceIter<const T>(this->begin(), this->end());
    }

    ~Vec(){
        if (!std::is_trivially_destructible<T>{}){

            while(!this->is_empty())
                this->_data[--this->_len].~T();
        }

        if(this->_data != nullptr)
            free(this->_data);
    }
};
# 7 "./iron/prelude.h" 2
# 1 "./iron/collections/queue.h" 1
       
# 10 "./iron/collections/queue.h"
template<typename T>
class Dqueue{

private:

    usize _head;

    usize _tail;

    usize _size;

    usize _capacity;

    T* _data;

private:


    void check_resize(bool reserve_front){
        if (this->_size == this->_capacity){


            if (this->_capacity == 0){
                this->_capacity = 32;
                this->_data = (T*)malloc(sizeof(T)*this->_capacity);
            }else{
                auto old_capacity = this->_capacity;

                this->_capacity *= 2;
                auto tmp_arr = (T*)malloc(sizeof(T)*this->_capacity);



                usize i = reserve_front?1:0;

                usize end = i + this->_size;


                while(i <= end){
                    new (&tmp_arr[i]) T(std::move(this->_data[(this->_tail++) & (old_capacity - 1)]));
                    i++;
                }

                free(this->_data);

                this->_data = tmp_arr;

                this->_tail = reserve_front?1:0;

                this->_head = this->_size + (reserve_front?1:0);
            }
        }
    }

    public:
    Dqueue(): _head(0), _tail(0), _size(0), _capacity(0), _data(nullptr) {}


    usize len() const {
        return this->_size;
    }



    bool is_empty() const {
        return this->_size == 0;
    }



    usize capacity() const {
        return this->_capacity;
    }



    void push_front(T val) {
        this->check_resize(false);

        new (&this->_data[this->_head]) T(std::move(val));


        this->_size += 1;
        this->_head = (this->_head + 1) & (this->_capacity - 1);
    }



    void push_back(T val) {
        this->check_resize(true);


        this->_size += 1;
        this->_tail = (this->_tail - 1) & (this->_capacity - 1);

        new (&this->_data[this->_tail]) T(std::move(val));
    }


    Option<T> pop_back() {
        if (this->is_empty()){
            return Option<T>();
        }else{
            auto cur_tail = this->_tail;


            this->_size -= 1;
            this->_tail = (cur_tail + 1) & (this->_capacity - 1);

            return Option<T>(std::move(this->_data[cur_tail]));
        }
    }


    Option<const T&> peek_back() const {
         if (this->is_empty()){
            return Option<const T&>();
        }else{
            return Option<const T&>(this->_data[this->_tail]);
        }
    }


    Option<T> pop_front() {
        if (this->is_empty()){
            return Option<T>();
        }else{


            this->_size -= 1;
            this->_head = (this->_head - 1) & (this->_capacity - 1);

            return Option<T>(std::move(this->_data[this->_head]));
        }
    }


    Option<const T&> peek_front() const {
         if (this->is_empty()){
            return Option<const T&>();
        }else{
            return Option<const T&>(this->_data[(this->_head - 1) & (this->_capacity - 1)]);
        }
    }

    ~Dqueue(){
        if (!std::is_trivially_destructible<T>{}){

            while(!this->is_empty()){
                this->_size -= 1;
                this->_head = (_head - 1) & (this->_capacity - 1);
                this->_data[this->_head].~T();
            }
        }
        free(this->_data);
    }
};
# 8 "./iron/prelude.h" 2
