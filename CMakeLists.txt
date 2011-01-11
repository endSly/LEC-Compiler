CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(lecc)

INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/ast/
  ${CMAKE_CURRENT_SOURCE_DIR}/parser/
  ${CMAKE_CURRENT_SOURCE_DIR}/execengine/
  )

# Add Bison command
SET(BISON_EXECUTABLE bison)
ADD_CUSTOM_COMMAND (
  SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/parser/parser.y
  COMMAND ${BISON_EXECUTABLE}
  ARGS -d -o ${CMAKE_CURRENT_SOURCE_DIR}/parser/parser.cpp ${CMAKE_CURRENT_SOURCE_DIR}/parser/parser.y
  OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/parser/parser.cpp 
         ${CMAKE_CURRENT_SOURCE_DIR}/parser/parser.hpp
  )

# Add Flex command
SET(FLEX_EXECUTABLE lex)
ADD_CUSTOM_COMMAND(
  SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/parser/scanner.l
  COMMAND ${FLEX_EXECUTABLE} 
  ARGS -o ${CMAKE_CURRENT_SOURCE_DIR}/parser/scanner.cpp
       ${CMAKE_CURRENT_SOURCE_DIR}/parser/scanner.l
  OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/parser/scanner.cpp
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/parser/parser.hpp
  )

ADD_EXECUTABLE(lecc main.cpp ast/AST.cpp parser/scanner.cpp parser/parser.cpp execengine/ExecEngine.cpp execengine/KernelObjects.cpp)