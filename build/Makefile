Q = @
COMPILE = /usr/bin/
CC = ${Q}${COMPILE}gcc-9
CXX = ${Q}${COMPILE}g++-9
SIZE = ${Q}${COMPILE}size
CFLAGS = -std=c++17 -Wall -g 
ECHO = ${Q}echo
TARGET = server


SRC_PATH = ../code/http/httpconn.cpp \
../code/http/httprequest.cpp \
../code/http/httpresponse.cpp \
../code/server/epoller.cpp \
../code/server/webserver.cpp \
../code/buffer/buffer.cpp \
../code/buildFile/buildXML_Rou.cpp \
../code/buildFile/buildXML_Net.cpp \
../code/buildFile/buildXML_Config.cpp \
../code/main.cpp \

OFILE = $(patsubst %.cpp,%.o,$(SRC_PATH))

LDFLAGS = ${INCLUDE_PATH}
CXXFLAGS = ${INCLUDE_PATH} ${CFLAGS}

all: ${OFILE}
	${ECHO} "cxx all $@"
	$(CXX) ${LDFLAGS} ${OFILE} -o ../bin/$(TARGET) -pthread
	${SIZE} ../bin/$(TARGET)

${OFILE}: ${SRC_PATH}
	${ECHO} "cxx $@"
	${CXX} ${CXXFLAGS} -c $(patsubst %.o,%.cpp,$@) -o $@ 

.PHONY : clean
clean:
	rm -rf ../bin/* $(TARGET)
	rm ${OFILE}




