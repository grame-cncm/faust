#############################################################################
# Makefile for building: DynamicCompiler.app/Contents/MacOS/DynamicCompiler
####### Compiler, tools and options

CC            = gcc -g
CXX           = g++ -g
DEFINE			= D_REENTRANT	 
INCPATH       = -I. -I/usr/include -I. -I/opt/local/include -I. -F/Library/Frameworks
LINK          = g++
LIBS          = $(SUBLIBS) -F/Library/Frameworks -L/Library/Frameworks -L/opt/local/libexec/llvm-3.1/lib -lffi -lm -lLLVMAsmParser -lLLVMInstrumentation -lLLVMLinker -lLLVMArchive -lLLVMBitReader -lLLVMDebugInfo -lLLVMJIT -lLLVMipo -lLLVMVectorize -lLLVMBitWriter -lLLVMTableGen -lLLVMHexagonCodeGen -lLLVMHexagonDesc -lLLVMHexagonInfo -lLLVMHexagonAsmPrinter -lLLVMPTXCodeGen -lLLVMPTXDesc -lLLVMPTXInfo -lLLVMPTXAsmPrinter -lLLVMMBlazeDisassembler -lLLVMMBlazeCodeGen -lLLVMMBlazeDesc -lLLVMMBlazeAsmPrinter -lLLVMMBlazeAsmParser -lLLVMMBlazeInfo -lLLVMCppBackendCodeGen -lLLVMCppBackendInfo -lLLVMMSP430CodeGen -lLLVMMSP430Desc -lLLVMMSP430Info -lLLVMMSP430AsmPrinter -lLLVMXCoreCodeGen -lLLVMXCoreDesc -lLLVMXCoreInfo -lLLVMCellSPUCodeGen -lLLVMCellSPUDesc -lLLVMCellSPUInfo -lLLVMMipsDisassembler -lLLVMMipsCodeGen -lLLVMMipsAsmParser -lLLVMMipsDesc -lLLVMMipsInfo -lLLVMMipsAsmPrinter -lLLVMARMCodeGen -lLLVMARMDisassembler -lLLVMARMAsmParser -lLLVMARMDesc -lLLVMARMInfo -lLLVMARMAsmPrinter -lLLVMPowerPCCodeGen -lLLVMPowerPCDesc -lLLVMPowerPCInfo -lLLVMPowerPCAsmPrinter -lLLVMSparcCodeGen -lLLVMSparcDesc -lLLVMSparcInfo -lLLVMX86AsmParser -lLLVMX86Disassembler -lLLVMX86CodeGen -lLLVMSelectionDAG -lLLVMAsmPrinter -lLLVMX86Desc -lLLVMX86Info -lLLVMX86AsmPrinter -lLLVMX86Utils -lLLVMMCDisassembler -lLLVMMCParser -lLLVMInterpreter -lLLVMCodeGen -lLLVMScalarOpts -lLLVMInstCombine -lLLVMTransformUtils -lLLVMipa -lLLVMAnalysis -lLLVMMCJIT -lLLVMRuntimeDyld -lLLVMExecutionEngine -lLLVMTarget -lLLVMMC -lLLVMObject -lLLVMCore -lLLVMSupport -L/usr/local/lib/faust -lfaust -lHTTPDFaust -ljacknet -L/opt/local/lib -lmicrohttpd  -lboost_system-mt -lboost_filesystem-mt -lboost_program_options-mt -lpthread 

sources =  $(wildcard *.cpp)
objects = $(sources:.cpp=.o)

####### Files

SOURCES       = Server.cpp \
				main.cpp 
				
OBJECTS       = Server.o \
				main.o
DESTDIR       = 
TARGET        = ./RemoteServer

first: all

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)
			$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

clean: 
	rm -f $(objects)

####### Compile

Server.o: Server.cpp Server.h TMutex.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Server.o Server.cpp

main.o: main.cpp Server.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

