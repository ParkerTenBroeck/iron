#include <iostream>

void test_option();
void test_result();
void test_range_iterator();
void test_vec();
void test_queue();    
void test_slice_iter();
    
void test_iter_rev();
void test_iter_enumerate();


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