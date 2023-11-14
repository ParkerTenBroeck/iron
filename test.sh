# g++ --std=c++20 -Wall -Wpedantic -Werror -fsanitize=address -g -I ./ -I ./tests ./tests/*.cpp 
# ./a.out
# g++ --std=c++17 -Wall -Wpedantic -Werror -fsanitize=address -g -I .. -I ./tests ./tests/*.cpp 
# ./a.out
g++ --std=c++11 -Wall -Wpedantic -Werror -fsanitize=address -g -I ./ -I ./tests ./tests/*.cpp 
./a.out


# g++ --std=c++20 -Wall -Wpedantic -Werror -I ./ -I ./tests ./tests/*.cpp 
# ./a.out
# g++ --std=c++17 -Wall -Wpedantic -Werror -I ./ -I ./tests ./tests/*.cpp 
# ./a.out
# g++ --std=c++11 -Wall -Wpedantic -Werror -I ./ -I ./tests ./tests/*.cpp 
# ./a.out
rm a.out