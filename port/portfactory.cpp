#include "portfactory.hpp"
#include "comportlnx.hpp"

#include "log/logger.h"

PortFactory::PortFactory(){
}

PortInterface *PortFactory::createPort(std::string strPort){
    LOG_I("Port Factory",strPort,'=');

    if(strPort.compare(STR_LINUX_PORT)==0){
        return new COMPortLnx();        
    }

    return NULL;
}
