CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror=vla -MMD -g
EXEC = biquadris
OBJECTS = main.o subject.o observer.o grid.o cell.o textdisplay.o levelZero.o levelOne.o levelTwo.o levelThree.o levelFour.o  block.o blockS.o blockZ.o blockI.o blockJ.o blockL.o blockT.o blockO.o level.o window.o graphicsdisplay.o blockX.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
