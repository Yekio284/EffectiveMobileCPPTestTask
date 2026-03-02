.PHONY: all setup clean run

all: setup app clean

app: exceptions.o infileparser.o serializer.o deserializer.o main.o
	g++ -o build/app -std=c++17 build/exceptions.o build/infileparser.o build/serializer.o build/deserializer.o build/main.o

exceptions.o:
	g++ -c -o build/exceptions.o -std=c++17 src/exceptionsLib/exceptions.cpp

infileparser.o:
	g++ -c -o build/infileparser.o -std=c++17 src/inFileParser/inFileParser.cpp

serializer.o:
	g++ -c -o build/serializer.o -std=c++17 src/serializer/serializer.cpp

deserializer.o:
	g++ -c -o build/deserializer.o -std=c++17 src/deserializer/deserializer.cpp

main.o:
	g++ -c -o build/main.o -std=c++17 src/main/main.cpp

run:
	./build/app input/inlet.in output/outlet.out

setup:
	mkdir -p build
	mkdir -p output

clean:
	rm build/*.o