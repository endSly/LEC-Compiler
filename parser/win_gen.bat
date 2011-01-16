
del win_parser.hpp
del win_parser.cpp
del win_scanner.cpp

bison -d -o win_parser.cpp parser.y

flex -owin_scanner.cpp scanner.l
