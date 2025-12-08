SFML = -lsfml-graphics -lsfml-window -lsfml-system

OBJS = main.o Body.o Physics.o

TARGET = simulator

all: $(TARGET)

$(TARGET): $(OBJS)
	g++ $(OBJS) -o $(TARGET) $(SFML)

Body.o: Body.cpp Body.h
	g++ -c Body.cpp

Physics.o: Physics.cpp Physics.h
	g++ -c Physics.cpp

main.o: main.cpp Body.h Physics.h
	g++ -c main.cpp

clean:
	rm simulator Body.o main.o Physics.o