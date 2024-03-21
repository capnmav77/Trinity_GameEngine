CC = g++
PROGRAMME = MCTS_TTT  
CCFLAGS = -Wall -g
HEADERS = mcts.h 
SOURCES = main.cpp mcts.cpp game.cpp 
OBJ = $(SOURCES:.cpp=.o)
RM=rm 
all: $(PROGRAMME)
$(PROGRAMME):$(OBJ)
	$(CC) $(OBJ) $(CCFLAGS) -o $(PROGRAMME)
%.o: %.cpp 
	$(CC) $(CCFLAGS) -c $< -o $@
clean:
	$(RM) -r ./$(PROGRAMME) ./*~ ./$(OBJ)
