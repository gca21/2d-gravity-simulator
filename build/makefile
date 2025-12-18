SFML = -lsfml-graphics -lsfml-window -lsfml-system

OBJS = main.o Body.o Physics.o Renderer.o Universe.o BodyManager.o VecMath.o
CFLAGS = -Wall -Wextra

IDIR = ../include/
SRCDIR = ../src/

TARGET = simulator

all: $(TARGET)

$(TARGET): $(OBJS)
	g++ $(CFLAGS) $(OBJS) -o $(TARGET) $(SFML)

VecMath.o: $(SRCDIR)VecMath.cpp $(IDIR)VecMath.hpp
	g++ $(CFLAGS) -c $(SRCDIR)VecMath.cpp

Body.o: $(SRCDIR)Body.cpp $(IDIR)Body.hpp
	g++ $(CFLAGS) -c -I $(IDIR) $(SRCDIR)Body.cpp

BodyManager.o: $(SRCDIR)BodyManager.cpp $(IDIR)BodyManager.hpp $(IDIR)Body.hpp $(IDIR)VecMath.hpp
	g++ $(CFLAGS) -c -I $(IDIR) $(SRCDIR)BodyManager.cpp

Physics.o: $(SRCDIR)Physics.cpp $(IDIR)Physics.hpp $(IDIR)Body.hpp $(IDIR)VecMath.hpp $(IDIR)BodyManager.hpp
	g++ $(CFLAGS) -c -I $(IDIR) $(SRCDIR)Physics.cpp

Renderer.o: $(SRCDIR)Renderer.cpp $(IDIR)Renderer.hpp $(IDIR)VecMath.hpp $(IDIR)BodyManager.hpp
	g++ $(CFLAGS) -c -I $(IDIR) $(SRCDIR)Renderer.cpp

Universe.o: $(SRCDIR)Universe.cpp $(IDIR)Universe.hpp $(IDIR)Body.hpp $(IDIR)BodyManager.hpp $(IDIR)Physics.hpp $(IDIR)Renderer.hpp
	g++ $(CFLAGS) -c -I $(IDIR) $(SRCDIR)Universe.cpp

main.o: $(SRCDIR)main.cpp $(IDIR)Universe.hpp
	g++ $(CFLAGS) -c -I $(IDIR) $(SRCDIR)main.cpp

clean:
	rm simulator Body.o main.o Physics.o Renderer.o Universe.o BodyManager.o VecMath.o