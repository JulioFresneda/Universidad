all:
	cp ./datos/* ./bin/
	g++ -c ./src/main.cpp -std=c++11 -o ./obj/main.o
	g++ ./src/main.cpp -std=c++11 -o ./bin/main
	doxygen Doxyfile

limpiar:
	rm -R ./doc/*
	rm ./bin/*
	rm ./obj/*
