
del parser.hpp
del parser.cpp
del scanner.cpp

bison -d -o win_parser.cpp parser.y

flex -owin_scanner.cpp scanner.l
