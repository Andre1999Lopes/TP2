all:
	g++ main.cpp -o jogo -lGLEW -lglut -lGL -lSOIL -lGLU -lSDL -lSDL_mixer

install-libraries:
	sudo apt-get update
	sudo apt-get install build-essential -y
	sudo apt-get install freeglut3-dev -y
	sudo apt-get install libglew-dev -y
	sudo apt-get install libsoil-dev -y
	sudo apt-get install libsdl-mixer1.2-dev -y
	sudo apt install libsdl2-dev libsdl2-2.0-0 -y

run:
	./jogo

clean:
	rm jogo
