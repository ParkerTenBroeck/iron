
#include "iron/types.h"
//Parker TenBroeck 2023

// A slice of continuous memory
template<typename T>
struct Slice{
private:
    T& _data;
    usize _len;
public:
};


