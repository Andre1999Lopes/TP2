all:
	g++ main.cpp -lGLEW -lglut -lGL -lSOIL -lGLU

install-libraries:
	sudo apt-get update
	sudo apt-get install build-essential -y
	sudo apt-get install freeglut3-dev -y
	sudo apt-get install libglew-dev -y
	sudo apt-get install libsoil-dev -y

run:
	./jogo

clean:
	rm jogo
