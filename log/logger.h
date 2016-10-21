#pragma once
#ifndef LOGGER
#define LOGGER

#include <iostream>
#include <string>

static void printDecor(int iCnt,char chDecor){
    for(int i=0;i<iCnt;i++)std::cout<<chDecor;
    std::cout<<std::endl;
}

static void LOG_I(std::string strSender,std::string msg, char chDecor='0'){
    int iAllItems=strSender.length()+msg.length()+2;
    if(chDecor!='0')printDecor(iAllItems,chDecor);
    std::cout<<strSender<<": "<<msg<<std::endl;
    if(chDecor!='0')printDecor(iAllItems,chDecor);
}

static void LOG_E(std::string strSender,std::string msg){
    LOG_I(strSender,msg,'!');
}

#endif // LOGGER

