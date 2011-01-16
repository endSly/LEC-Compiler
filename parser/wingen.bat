
del parser.hpp
del parser.cpp
del scanner.cpp

bison -d -o parser.cpp parser.y

flex -oscanner.cpp scanner.l
