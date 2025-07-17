set (INCLUDE_DIR ../include)
include_directories(${INCLUDE_DIR} ../concepts ../models ../integrators ../wrappers ../archetypes)

add_executable(basic basic.cpp)
target_link_libraries(basic)

add_executable(synapsis synapsis.cpp)
target_link_libraries(synapsis)

add_executable(chemical_synapsis chemical_synapsis.cpp)
target_link_libraries(chemical_synapsis)
