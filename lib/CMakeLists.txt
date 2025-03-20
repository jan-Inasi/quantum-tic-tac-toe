file(GLOB LIB_FILES CONFIGURE_DEPENDS "*.cpp")

add_library(qttt_lib STATIC ${LIB_FILES})
target_include_directories(qttt_lib PUBLIC ../include)
target_link_libraries(qttt_lib PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(qttt_lib PRIVATE restinio::restinio)

add_library(qttt_lib_cov STATIC ${LIB_FILES})
target_include_directories(qttt_lib_cov PUBLIC ../include)
target_link_libraries(qttt_lib_cov PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(qttt_lib_cov PRIVATE restinio::restinio)

if (UNIX)
    target_compile_options(qttt_lib_cov PRIVATE ${GENERAL_FLAGS} --coverage -g3 -O0)
    target_link_options(qttt_lib_cov PRIVATE --coverage)
endif (UNIX)