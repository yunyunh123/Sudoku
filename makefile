# Copyright 2021 Julia Hua jhua2@bu.edu

main: main.cpp Box.o Box.h Grid.o Grid.h Textbox.o Textbox.h Button.o Button.h
	g++ main.cpp Box.o Grid.o Textbox.o Button.o -o main -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network

prob: Sudoku.py
	python3 Sudoku.py