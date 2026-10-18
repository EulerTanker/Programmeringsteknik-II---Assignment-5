slm: main.o Arguments.o LanguageModel.o TextGenerator.o
	g++ -o slm main.o Arguments.o LanguageModel.o TextGenerator.o

main.o: src/main.cpp src/Arguments.h src/LanguageModel.h src/TextGenerator.h
	g++ -Wall -c src/main.cpp

Arguments.o: src/Arguments.cpp src/Arguments.h
	g++ -Wall -c src/Arguments.cpp

LanguageModel.o: src/LanguageModel.cpp src/LanguageModel.h
	g++ -Wall -c src/LanguageModel.cpp

TextGenerator.o: src/TextGenerator.cpp src/TextGenerator.h src/LanguageModel.h
	g++ -Wall -c src/TextGenerator.cpp

clean:
	rm -f slm *.o
