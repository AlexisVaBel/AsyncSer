#include "sercontroller.hpp"


#include <list>
#include <thread>
#include <chrono>

#include "port/portfactory.hpp"
#include "port/serialparams.hpp"
#include "log/logger.h"



SerController::SerController(std::string strPort):m_strPort(strPort){

}

SerController::~SerController(){
    delete [] m_port;
}

void SerController::printComs(){
    PortFactory *portFactory=new PortFactory();
    m_port=portFactory->createPort(m_strPort);
    if(m_port==NULL)return;
    std::list<std::string> *lstPorts=nullptr;
    lstPorts=reinterpret_cast<std::list<std::string> *> (m_port->getAllPorts());
    if(lstPorts!=nullptr){
        LOG_I("Serr controller","available ports",'=');

        auto lstBegin=lstPorts->begin();
        auto lstEnd  =lstPorts->end();
        while(lstBegin!=lstEnd){
            LOG_I("",*lstBegin++);
        }

    };    
    delete portFactory;
}



void SerController::accAnsw(std::promise<std::string> readStop){
    std::string strAnsw="";
    char chIn='0';
    while(chIn!=-1){
        m_port->readPort(&chIn,1);
        if(chIn!=-1)
            strAnsw.push_back(chIn);
    }
    readStop.set_value(strAnsw);
    LOG_I("tread joined","ok ");
}

bool SerController::sendCmd(std::string strPort,std::string strCmd){
    //
    bool bRes=false;

    SerialParams prm;
    prm.strPort=strPort;

    prm.iBaudRate=000015;
    prm.iDataBits=000060;
    prm.iStopBits=0;
    prm.iFlowCnt=0;
    if(!m_port->openPort(&prm)){
        LOG_E(strPort,"can`t open");
        return bRes;
    }
    //
    char *chSend=const_cast<char*>(strCmd.c_str());
    std::promise<std::string> readPromise;
    std::future<std::string>  readFuture=readPromise.get_future();
    //here send package to port
    LOG_I("sercontr ","sending to port");
    m_port->writePort(chSend,strCmd.length());
    //here send package to port
    std::thread readThr(&SerController::accAnsw,this,std::move(readPromise));
    readThr.detach();
    std::chrono::system_clock::time_point milis200=std::chrono::system_clock::now()+std::chrono::milliseconds(200);
    if(readFuture.wait_until(milis200)!=std::future_status::ready){
        LOG_E(strPort,"timedout");        
    }else{
        LOG_I(strPort,"ok "+readFuture.get());
        bRes=true;
    };
    m_port->closePort();
    delete chSend;
    return bRes;
}

