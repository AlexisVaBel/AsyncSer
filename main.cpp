#include "contr/sercontroller.hpp"

int main(int argc,char ** argv){
    SerController *cntr=new SerController("portlinux");
    cntr->printComs();
    cntr->sendCmd("ttyUSB0","hello");
    cntr->sendCmd("ttyUSB0","world");
    return 0;
}
