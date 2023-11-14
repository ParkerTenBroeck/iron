#include "iron/prelude.h"
#include "iron/collections/vector.h"
#include <assert.h>
#include <iostream>


void test_vec_primitive(){
    Vec<usize> vec;
    assert(vec.len() == 0);
    assert(vec.capacity() == 0);

    usize upper = (usize)random() % 256 + 256;
    usize* regular = new usize[upper];

    for(usize i = 0; i < upper; i ++){
        usize bruh = i + (usize)random() % 512;
        vec.push(bruh);
        regular[i] = bruh;
    }

    assert(vec.len() == upper);
    assert(vec.capacity() == 512);

    for(usize i = 0; i < upper; i ++){
        assert(vec[i] == regular[i]);
    }

    for(auto val : vec.iter().enumerate()){
        assert(val.val == regular[val.index]);
    }

    for(auto val : vec.iter().enumerate().rev()){
        assert(val.val == regular[val.index]);
    }

    auto index = upper - 1;
    while(auto next = vec.pop()){
        assert(regular[index] == *next);
        index -= 1;
    }

    assert(vec.len() == 0);

    delete[] regular;
}

void test_vec_complex(){
    Vec<String> vec;
    assert(vec.len() == 0);
    assert(vec.capacity() == 0);

    usize upper = (usize)random() % 256 + 256;
    std::string* regular = new std::string[upper];

    for(usize i = 0; i < upper; i ++){
        usize bruh = i + random();
        std::string string = std::to_string(bruh);
        vec.push(string);
        regular[i] = string;
    }

    assert(vec.len() == upper);
    assert(vec.capacity() == 512);

    for(usize i = 0; i < upper; i ++){
        assert(vec[i] == regular[i]);
    }

    for(auto val : vec.iter().enumerate()){
        assert(val.val == regular[val.index]);
    }

    for(auto val : vec.iter().enumerate().rev()){
        assert(val.val == regular[val.index]);
    }

    auto index = upper - 1;
    while(auto next = vec.pop()){
        assert(regular[index] == *next);
        index -= 1;
    }

    assert(vec.len() == 0);

    delete[] regular;
}

void test_vec(){
    std::cout << "Testing primitive vec\n";
    test_vec_primitive();
    std::cout << "Testing complex vec\n";
    test_vec_complex();
    std::cout << "Completed vec tests\n";
}