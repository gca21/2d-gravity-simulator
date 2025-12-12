SFML = -lsfml-graphics -lsfml-window -lsfml-system

OBJS = main.o Body.o Physics.o Renderer.o Universe.o

TARGET = simulator

all: $(TARGET)

$(TARGET): $(OBJS)
	g++ $(OBJS) -o $(TARGET) $(SFML)

Body.o: ../src/Body.cpp ../include/Body.h
	g++ -c ../src/Body.cpp

Physics.o: ../src/Physics.cpp ../include/Physics.h
	g++ -c ../src/Physics.cpp

Renderer.o: ../src/Renderer.cpp ../include/Renderer.h
	g++ -c ../src/Renderer.cpp

Universe.o: ../src/Universe.cpp ../include/Universe.h
	g++ -c ../src/Universe.cpp

main.o: ../src/main.cpp ../include/Body.h ../include/Physics.h ../include/Renderer.h ../include/Universe.h
	g++ -c ../src/main.cpp

clean:
	rm simulator Body.o main.o Physics.o Renderer.o Universe.o