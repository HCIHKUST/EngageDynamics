#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "dialogtext.h"
#include "exec_shell.h"

dialogText::dialogText()
{
}

void dialogText::init()
{
    getResponse("RESET");
}

string dialogText::getResponse(string text)
{
    static int index=0;
    if(text == ""){
        return string("不好意思，我没有听清楚你说的话^startTag(not know)，您可以再说一遍么？");
    }
    string cmd = "sh dialog.sh ";
    string text_res = exec_shell(cmd+text);

    //char* expr = "animations/Stand/BodyTalk/BodyTalk_";
    char* expr = "animations/Stand/Gestures/Explain_";

    char buffer[200];
    sprintf(buffer, "^start(%s%d)%s", expr, index%12, text_res.c_str());
    index++;

    std::string result(buffer);

    std::string loc = "num";
    std::string yuan_loc = "元";
    std::string hour_loc = "小时";
    std::string min_loc = "分钟";

    int ind_e = result.find(loc);
    int ind_yuan = result.find(yuan_loc);
    int ind_hour = result.find(hour_loc);
    int ind_min = result.find(min_loc);

    if(ind_e == -1){
        return result;
    }
    else{
        if(ind_yuan != -1){
            return result.replace(ind_e, 3, "24");
        }
        if(ind_hour != -1){
            return result.replace(ind_e, 3, "1");
        }
        if(ind_min != -1){
            return result.replace(ind_e, 3, "30");
        }
    }

}
