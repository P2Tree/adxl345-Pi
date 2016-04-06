CXX = g++

CXXFLAGS= -Wall -Werror -lwiringPi

OBJ = main.o ADXL345.o ADXL345PiSPI.o

%.o: %.c
	$(CC) -g -c -o $@ $< $(CXXLAGS)

all: $(OBJ)
	g++ -g -o $@ $^ $(CXXFLAGS)

clean:
	rm *.o
