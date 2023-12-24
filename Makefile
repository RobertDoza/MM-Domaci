EXECUTABLE = test
MAIN = main
GENERATE = generate
MODEL_INSTANCE = model_instance
CPPFLAGS = -Wall -Wextra -Werror -pedantic

$(EXECUTABLE): $(MAIN).o $(GENERATE).o $(MODEL_INSTANCE).o
	g++ $^ -o $@

$(MAIN).o: $(MAIN).cpp $(MODEL_INSTANCE).hpp $(GENERATE).hpp
	g++ $< -c -o $@ $(CPPFLAGS)

$(GENERATE).o: $(GENERATE).cpp $(GENERATE).hpp $(MODEL_INSTANCE).hpp
	g++ $< -c -o $@ $(CPPFLAGS)

$(MODEL_INSTANCE).o: $(MODEL_INSTANCE).cpp $(MODEL_INSTANCE).hpp $(GENERATE).hpp
	g++ $< -c -o $@ $(CPPFLAGS)

.PHONY: clean

clean:
	rm -f $(EXECUTABLE) *.o *.~

