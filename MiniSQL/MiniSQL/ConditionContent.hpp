//
//  ConditionContent.hpp
//  MiniSQL
//
//  Created by zyy on 15/10/28.
//  Copyright © 2015年 Fan Wu. All rights reserved.
//

#ifndef ConditionContent_hpp
#define ConditionContent_hpp

#include <stdio.h>
#include <string>
using namespace std;

class ConditionContent
{
    string attrName;
    string attrValueStr;
    int attrValueInt;
    float attrValueFlo;
    int attrType;
    string op; // "="、"<>"、"<"、">"、"<="、">="
};

#endif /* ConditionContent_hpp */
