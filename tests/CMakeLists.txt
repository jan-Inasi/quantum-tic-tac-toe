add_executable(testone testone.cpp)
target_link_libraries(testone PRIVATE Catch2::Catch2)
add_test(NAME test COMMAND testone)

add_executable(test-quantum-tictactoe test-quantum-tictactoe.cpp)
target_include_directories(test-quantum-tictactoe PRIVATE ../include)
target_link_libraries(test-quantum-tictactoe PRIVATE Catch2::Catch2)
target_link_libraries(test-quantum-tictactoe PRIVATE qttt_lib_cov)
target_compile_features(test-quantum-tictactoe PRIVATE cxx_std_20)
if (UNIX)
    target_compile_options(test-quantum-tictactoe PRIVATE ${GENERAL_FLAGS} --coverage -g3 -O0)
    target_link_options(test-quantum-tictactoe PRIVATE --coverage)
endif (UNIX)

add_test(NAME test-qttt COMMAND test-quantum-tictactoe)
    
