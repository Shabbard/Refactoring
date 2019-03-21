CC = g++
HEADER = ./headers/ 
SOURCE = ./src/
BIN = ./bin/
CXXFLAGS = -std=c++11 -I $(HEADER) -Wall -Wfatal-errors -Ofast
vpath %.h $(HEADER)
GPX = $(SOURCE)GPX-xmlgen.cpp
XMLGEN = ${BIN}xmlgenerator.o
MKDIR = mkdir -p

.PHONY: all
all: $(BIN) $(BIN)GPX-xmlgenerator

$(BIN):
	${MKDIR} $(BIN)

$(BIN)GPX-xmlgenerator: ${GPX} ${XMLGEN}
	$(CC) ${CXXFLAGS} $^ -o $@

${BIN}%.o: $(SOURCE)%.cpp $(INCLUDEDIR)%.h
	$(CC) ${CXXFLAGS} -c $< -o $@

.PHONY: clean
clean:
	rm -f ${BIN}*