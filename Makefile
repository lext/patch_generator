all:
	g++ `pkg-config --cflags opencv` main.cpp `pkg-config --libs opencv` -o patch_generator

