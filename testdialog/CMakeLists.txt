cmake_minimum_required(VERSION 2.8)
project(test_dialog)

find_package(qibuild)
set(_srcs
    exec_shell.h
    exec_shell.cpp
    tulingmodule.h    
    tulingmodule.cpp
    dialogtext.h
    dialogtext.cpp
    grabcafe.h
    grabcafe.cpp
    converter.cpp
    converter.h
    wakeup.cpp
    wakeup.h
    main.cpp)

qi_create_bin(test_dialog ${_srcs})
set_target_properties(test_dialog PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
qi_use_lib(test_dialog ALCOMMON ALPROXIES)

