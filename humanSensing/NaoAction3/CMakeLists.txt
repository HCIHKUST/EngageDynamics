cmake_minimum_required(VERSION 2.8)
project(my_module)
find_package(qibuild)

option(MYMODULE_IS_REMOTE
  "module is compiled as a remote module (ON or OFF)"
  ON)

set(_srcs
  main.cpp
  human_sense.h
  human_sense.cpp
  motion_utils.h
  motion_utils.cpp
  test.h
  test.cpp
  interface.h
  interface.cpp
  human_state.h
  human_state.cpp
  trim.h
  actions.cpp
)

if(MYMODULE_IS_REMOTE)
  add_definitions(" -DMYMODULE_IS_REMOTE")
  qi_create_bin(my_module ${_srcs})
else()
  qi_create_lib(my_module SHARED ${_srcs} SUBFOLDER naoqi)
endif()

qi_use_lib(my_module ALCOMMON ALPROXIES ALTHREAD ALMATH ALAUDIO)
