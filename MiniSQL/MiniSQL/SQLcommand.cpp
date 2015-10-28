//
//  SQLcommand.cpp
//  MiniSQL
//
//  Created by zyy on 15/10/28.
//  Copyright © 2015年 Fan Wu. All rights reserved.
//

#include "SQLcommand.hpp"

string firstWord(string s)
{
    int k;
    
    k=(int)s.find(' ');
    return s.substr(0,k);
}

//将tab字符和换行符全部转换为空格，以便于后续的find函数操作
string replaceTab(string s)
{
    int l,i;
    
    l=(int)s.length();
    for (i=0; i<l; i++)
        if (s[i]=='\t' || s[i]=='\n')
            s[i]=' ';
    
    return s;
}

string throwLeadingSpaces(string s)
{
    int i;
    i=0;
    while (s[i]==' ')
        i++;

    return s.substr(i);
}

void SQLcommand::parseComm(string commandCont)
{
    //这个函数用来分析sql语句
    string fw;
    
    commandCont=replaceTab(commandCont);
    fw=firstWord(commandCont);
    if (fw=="create")
    {
        commandCont=throwLeadingSpaces(commandCont);
        fw=firstWord(commandCont);
        if (fw=="table")
        {
            
        }
        else
        if (fw=="index")
        {
            
        }
        else
        {
            commandType=0;
            errorInfo="Syntax error near '"+fw+"'.";
        }
    }
    else
    if (fw=="drop")
    {
        commandCont=throwLeadingSpaces(commandCont);
        fw=firstWord(commandCont);
        if (fw=="table")
        {
            
        }
        else
        if (fw=="index")
        {
        
        }
        else
        {
            commandType=0;
            errorInfo="Syntax error near '"+fw+"'.";
        }
    }
    else
    if (fw=="insert")
    {
        
    }
    else
    if (fw=="select")
    {
            
    }
    else
    if (fw=="delete")
    {
        
    }
    else
    if (fw=="quit")
    {
        
    }
    else
    if (fw=="execfile")
    {
        
    }
    else
    {
        commandType=0;
        errorInfo="Syntax error near '"+fw+"'.";
    }
}