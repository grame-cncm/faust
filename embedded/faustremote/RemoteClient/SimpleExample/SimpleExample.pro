######################################################################
# FAUSTLIVE.PRO
######################################################################

# THANKS TO QMAKE, THIS FILE WILL PRODUCE THE MAKEFILE OF FAUSTLIVE APPLICATION
# IT DESCRIBES ALL THE LINKED LIBRAIRIES, COMPILATION OPTIONS, THE SOURCES TO BE COMPILED

# APPLICATION SETTINGS

TARGET = SimpleExample

#QMAKE_CXXFLAGS += -Wno-unused-variable -g
QMAKE_EXTRA_TARGETS += all

#CONFIG -= x86_64
#CONFIG += exceptions rtti

QT+=widgets
QT+=core
QT+=gui

LLVMLIBS = $$system(llvm-config --libs)
LLVMDIR = $$system(llvm-config --ldflags)

LIBS += -L/usr/local/lib
LIBS += -L/usr/lib 
LIBS += -L/usr/local/lib/faust 
LIBS += -lfaustremote
LIBS += -lfaust
LIBS += -L/usr/lib/x86_64-linux-gnu
LIBS += -lcurl
LIBS += -ljack
LIBS += -ljacknet
LIBS+= $$LLVMDIR
LIBS+= $$LLVMLIBS
LIBS += -ldl
LIBS += -ldbus-1
LIBS += -lpthread
LIBS += -lrt
LIBS += -ldaemon

HEADERS += ../../utilities.h \
			/usr/local/include/faust/gui/faustqt.h

SOURCES += main.cpp \
			../../utilities.cpp


