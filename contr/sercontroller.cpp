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
    m_port->readPort(&chIn,1);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    readStop.set_value(strAnsw);
    LOG_I("tread joined","ok ");
}

void SerController::sendCmd(std::string strPort,std::string strCmd){
    //
    char *chSend=const_cast<char*>(strCmd.c_str());
    SerialParams prm;
    prm.strPort=strPort;
    prm.iBaudRate=9600;
    prm.iDataBits=8;
    prm.iStopBits=1;
    prm.iFlowCnt=0;
    if(!m_port->openPort(&prm)){
        LOG_E(strPort,"can`t open");
        return;
    }
    //


    std::promise<std::string> readPromise;
    std::future<std::string>  readFuture=readPromise.get_future();
    //here send package to port
    m_port->writePort(chSend,strCmd.length());
    //here send package to port
    std::thread readThr(&SerController::accAnsw,this,std::move(readPromise));
    readThr.detach();
    std::chrono::system_clock::time_point milis200=std::chrono::system_clock::now()+std::chrono::milliseconds(200);
    if(readFuture.wait_until(milis200)!=std::future_status::ready){
        LOG_E(strPort,"timedout");
    }else{
        LOG_I(strPort,"ok "+readFuture.get());
    };
    m_port->closePort();
}

