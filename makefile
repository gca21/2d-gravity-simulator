SFML = -lsfml-graphics -lsfml-window -lsfml-system

OBJS = main.o Body.o

TARGET = simulator

all: $(TARGET)

$(TARGET): $(OBJS)
	g++ $(OBJS) -o $(TARGET) $(SFML)

Body.o: Body.cpp Body.h
	g++ -c Body.cpp

main.o: main.cpp Body.h
	g++ -c main.cpp

clean:
	rm simulator Body.o main.o