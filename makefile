SFML = -lsfml-graphics -lsfml-window -lsfml-system

OBJS = main.o Body.o Physics.o Renderer.o

TARGET = simulator

all: $(TARGET)

$(TARGET): $(OBJS)
	g++ $(OBJS) -o $(TARGET) $(SFML)

Body.o: Body.cpp Body.h
	g++ -c Body.cpp

Physics.o: Physics.cpp Physics.h
	g++ -c Physics.cpp

Renderer.o: Renderer.cpp Renderer.h
	g++ -c Renderer.cpp

main.o: main.cpp Body.h Physics.h Renderer.h
	g++ -c main.cpp

clean:
	rm simulator Body.o main.o Physics.o Renderer.o