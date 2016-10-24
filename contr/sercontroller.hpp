#ifndef SERCONTROLLER_H
#define SERCONTROLLER_H

#include <string>
#include <future>
#include "port/portinterface.hpp"

class SerController
{
public:
    SerController(std::string strPort);
    ~SerController();
    void    printComs();
    bool    sendCmd(std::string strPort, std::string strCmd);
private:
    std::string m_strPort;
    PortInterface   *m_port;

    void accAnsw(std::promise<std::string> readStop);
};

#endif // SERCONTROLLER_H
