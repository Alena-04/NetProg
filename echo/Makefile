.PHONY: all debug release clean

PR_NAME = server

DB_FLAGS = -g -Wall
RL_FLAGS = -Wall -DNDEBUG

DB_EXEC = $(PR_NAME)-dbg
RL_EXEC = $(PR_NAME)
SOURCE = *.cpp

all: debug release

debug: $(DB_EXEC)
release: $(RL_EXEC)

clean:
	rm -f $(RL_EXEC) $(DB_EXEC)

$(DB_EXEC): $(SOURCE)
	g++ $(DB_FLAGS) $(SOURCE) -o $(DB_EXEC)

$(RL_EXEC): $(SOURCE)
	g++ $(RL_FLAGS) $(SOURCE) -o $(RL_EXEC)
