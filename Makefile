EXECUTABLE = test
MAIN = main
GENERATE = generate
CPPFLAGS = -Wall -Wextra -pedantic

$(EXECUTABLE): $(MAIN).o $(GENERATE).o
	g++ $^ -o $@

$(MAIN).o: $(MAIN).cpp
	g++ $< -c -o $@ $(CPPFLAGS)

$(GENERATE).o: $(GENERATE).cpp
	g++ $< -c -o $@ $(CPPFLAGS)

.PHONY: clean

clean:
	rm -f $(EXECUTABLE) *.o *.~

