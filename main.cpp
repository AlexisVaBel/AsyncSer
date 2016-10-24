#include "contr/sercontroller.hpp"

int main(int argc,char ** argv){
    SerController *cntr=new SerController("portlinux");
    cntr->printComs();
    cntr->sendCmd("ttyUSB0","49 03 04 00 02 00 00 93 F7");
//    cntr->sendCmd("ttyUSB0","49 03 04 00 02 00 00 93 F7");
//    delete cntr;
    return 0;
}
