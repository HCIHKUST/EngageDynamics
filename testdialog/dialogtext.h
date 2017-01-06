#ifndef DIALOGTEXT_H
#define DIALOGTEXT_H

#include <iostream>

using std::string;

class dialogText{

public:
    dialogText();
    virtual void init();
    string getResponse(string text);
};

#endif // DIALOGTEXT_H
