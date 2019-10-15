GG = g++
OBJ = main.o calculator.o
CFLAGS = -I.
DEPS = calculator.hpp

%.o:%.cpp $(DEPS)
	$(GG) -c -o $@ $< $(CFLAGS)
calculator:$(OBJ) $(DEPS)
	$(GG) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -rf *.o
