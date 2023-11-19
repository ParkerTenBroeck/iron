#include <iostream>
#include "iron/prelude.h"
#include "test.h"

void test_option();
void test_result();
void test_range_iterator();
void test_vec();
void test_queue();    
void test_slice_iter();
    
void test_iter_rev();
void test_iter_enumerate();


void print_enumerated_vec(Result<Result<char*, int>, usize> result){
  if (auto sorted = result.as_ref().ok()){
    black_box(*sorted);
  }else if(auto error = result.as_ref().err()){
    black_box(*error);
  }
}



int main(){
    test_option();
    test_result();
    // test_range_iterator();
    test_vec();
    test_queue();    
    // test_slice_iter();
    
    // test_iter_rev();
    // test_iter_enumerate();

    std::cout << "Finished tests\n";
}