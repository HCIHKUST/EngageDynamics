#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <qi/log.hpp>
#include <iconv.h>
#include "tulingmodule.h"
#include "exec_shell.h"

tulingModule::tulingModule(){
}

void tulingModule::init()
{
}

string tulingModule::getResponse(string text)
{
    static int index=0;
    if(text == ""){
        return string("不好意思，我没有听清楚你说的话^startTag(not know)，您可以再说一遍么？");
    }
    string cmd = "curl -G http://www.tuling123.com/openapi/api -d key=c237b459589ef904699807b7dadcc300 -d info="+text+"/";

    string result = exec_shell(cmd);
    string rec_result;

    qiLogInfo("Result From Tuling:")<<result<<std::endl;
    std::string loc = "\"text\"";
    int ind_e = result.find(loc);
    while(result[ind_e] != ':'){
        ind_e++;
    }
    while(result[ind_e] != '"'){
        if(result[ind_e] == '}'){
            rec_result = "";
            return rec_result;
        }
        ind_e++;
    }
    int ind_s = ++ind_e;
    while(result[ind_e] != '"'){
        ind_e++;
    }
    rec_result = result.substr(ind_s, ind_e-ind_s);

    //char* expr = "animations/Stand/BodyTalk/BodyTalk_";
    char* expr = "animations/Stand/Gestures/Explain_";
    char buffer[2000];

    sprintf(buffer, "^start(%s%d)%s", expr, index%12, rec_result.c_str());
    index++;

    qiLogInfo("Result From Tuling:")<<string(buffer)<<std::endl;

    return string(buffer);
}
