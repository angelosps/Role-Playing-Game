SRC = $(wildcard src/*.cpp)

OBJS = $(SRC:.cpp=.o)

OUT = rpg

CXXFLAGS = -w -std=c++11

CC = g++ 

$(OUT): $(OBJS)
	$(CC) $^ -o $@
	
clean:
	rm -f $(OBJS) $(OUT)

run:	
	./$(OUT)