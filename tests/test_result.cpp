#include "iron/prelude.h"


void test_result(){
    Result<usize, bool> res{false};   
    Result<Result<usize, bool>&, bool> res2{res};   
}