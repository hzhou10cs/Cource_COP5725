CPP_FILES = $(wildcard *.cpp)
OBJ_FILES = $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))

DATALOADER: $(OBJ_FILES)
	g++ -o $@ $^

obj/%.o: %.cpp
	g++ -c -o $@ $<