TEMPLATE=app
QT+=core
CONFIG+=console
CONFIG+=static

QMAKE_CXXFLAGS+=-std=c++11

HEADERS += \
    port/comportlnx.hpp \
    port/portfactory.hpp \
    port/portinterface.hpp \
    port/serialparams.hpp \
    contr/sercontroller.hpp \
    log/logger.h

SOURCES += \
    port/comportlnx.cpp \
    port/portfactory.cpp \
    main.cpp \
    contr/sercontroller.cpp
