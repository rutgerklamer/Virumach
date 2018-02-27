#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <vector>
#include <stdint.h>

typedef int32_t i32;

typedef enum {
	$0, $1, $2, $3, $4, $5, $6, $7, $8, $9, SP, IP,
	NUM_OF_REGISTERS
} Registers;

#define sp (registers[SP])
#define pc (registers[IP])

class Stack {
	//i32 pc = 100;			 // Program counter, Adress 100
	std::vector<i32> memory; // memory vector
	int registers[NUM_OF_REGISTERS];
	i32 typ = 0;			 // type
	i32 dat = 0;			 // data
	i32 running = 1;		 // running cehck
	int false_if;

	i32 getType(i32 instruction);
	i32 getData(i32 instruction);
	void fetch();
	void decode();
	void execute();
	void doPrimitive();

public:
	Stack();
	void run();
	void loadProgram(std::vector<i32> prog);

};

#endif STACK_H
