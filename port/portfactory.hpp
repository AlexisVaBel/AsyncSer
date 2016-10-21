#ifndef PORTFACTORY_HPP
#define PORTFACTORY_HPP

#include <string>
#include "./portinterface.hpp"

static std::string STR_LINUX_PORT="portlinux";

class PortFactory
{
public:
    PortFactory();
    PortInterface *createPort(std::string strPort);
};

#endif // PORTFACTORY_HPP
