#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "exec_shell.h"

std::string exec_shell(std::string cmd){
    std::cout<<"Executed command: "<<cmd<<std::endl;
    char buffer[128];
    std::string result ="";
    FILE* pipe = popen(cmd.c_str(), "r");
    if(!pipe) throw std::runtime_error("popen() failed!");
    while(!feof(pipe)){
        if(fgets(buffer, 128, pipe) != NULL )
            result += buffer;
    }
    pclose(pipe);
    return result;
}
