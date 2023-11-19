#if defined(__GNUC__) || defined(__llvm__)
    #define BLT_ATTRIB_NO_INLINE __attribute__ ((noinline))
#else
    #if defined(_MSC_VER) && !defined(__INTEL_COMPILER)
        #define BLT_ATTRIB_NO_INLINE __declspec(noinline)
    #else
        #define BLT_ATTRIB_NO_INLINE
    #endif
#endif

template<typename T>
void BLT_ATTRIB_NO_INLINE black_box_ref(const T& val){
    volatile void* hell;
    hell = (void*)&val;
    (void)hell;
}

template<typename T>
void BLT_ATTRIB_NO_INLINE black_box_ref(T& val){
    volatile void* hell;
    hell = (void*)&val;
    (void)hell;
}

template<typename T>
void BLT_ATTRIB_NO_INLINE black_box(T val){
    volatile void* hell2;
    hell2 = (void*)&val;
    (void)hell2;
}

template<typename T>
T& BLT_ATTRIB_NO_INLINE black_box_ref_ret(T& val){
    volatile void* hell;
    hell = (void*)&val;
    (void)hell;
    return val;
}

template<typename T>
const T& BLT_ATTRIB_NO_INLINE black_box_ref_ret(const T& val){
    volatile void* hell;
    hell = (void*)&val;
    (void)hell;
    return val;
}

template<typename T>
T BLT_ATTRIB_NO_INLINE black_box_ret(T val){
    volatile void* hell2;
    hell2 = (void*)&val;
    (void)hell2;
    return val;
}