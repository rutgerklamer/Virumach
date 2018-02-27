#include "Stack.h"

Stack::Stack()
{
	pc = 100;
	sp = 0;
	false_if = 0;
	memory.reserve(1000000);
	for (i32 i = 0; i < 1000000; i++)
		memory.push_back(0);
}

i32 Stack::getType(i32 instruction)
{
	i32 type = 0xc0000000;
	type = (type & instruction) >> 30;

	return type;
}

i32 Stack::getData(i32 instruction)
{
	i32 data = 0x3fffffff;
	data = data & instruction;

	return data;
}

void Stack::doPrimitive() {
	i32 temp;
	if (false_if <= 0) {
		false_if = 0;
		switch (dat)
		{
			int a;
		case 0: // HALT
			//std::cout << "HALT" << std::endl;
			running = 0;
			break;
		case 1: // ADD
			a = memory[sp];
			memory[sp] = 0;
			//std::cout << "ADD: " << a << "  " << memory[sp - 1] << std::endl;
			memory[sp - 1] = memory[sp - 1] + a;
			sp--;
			break;
		case 2: // SUB
			//std::cout << "SUB: " << memory[sp - 1] << "  " << memory[sp] << std::endl;
			memory[sp - 1] = memory[sp - 1] - memory[sp];
			sp--;
			break;
		case 3: // MUL
			//std::cout << "MUL: " << memory[sp - 1] << "  " << memory[sp] << std::endl;
			memory[sp - 1] = memory[sp - 1] * memory[sp];
			sp--;
			break;
		case 4: // DIV
			//std::cout << "DIV: " << memory[sp - 1] << "  " << memory[sp] << std::endl;
			memory[sp - 1] = memory[sp - 1] / memory[sp];
			sp--;
			break;
		case 5: // MOD
			//std::cout << "MOD: " << memory[sp - 1] << "  " << memory[sp] << std::endl;
			memory[sp - 1] = memory[sp - 1] % memory[sp];
			sp--;
			break;
		case 6: // PSHR
			sp++;
			memory[sp] = memory[sp - 1];
			break;
		case 7: // SWAP
			//std::cout << "SWAP: " << memory[sp - 1] << "  " << memory[sp] << std::endl;
			temp = memory[sp - 1];
			memory[sp - 1] = memory[sp];
			memory[sp] = temp;
			break;
		case 8: // PSH
			//std::cout << "PSH: " << getData(memory[pc+1]) << std::endl;
			sp++;
			memory[sp] = getData(memory[++pc]);
			break;
		case 9: // SET REG
			//std::cout << "SET REG: " << getData(memory[pc+1]) << " TO: " << getData(memory[pc+2]) << std::endl;
			registers[getData(memory[pc + 1])] = getData(memory[pc + 2]);
			pc += 2;
			break;
		case 10: // MOVE REG
			//std::cout << "MV REG: " << getData(memory[pc + 1]) << " TO REG: " << getData(memory[pc + 2]) << std::endl;
			registers[getData(memory[pc + 2])] = registers[getData(memory[pc + 1])];
			pc += 2;
			break;
		case 11: // PSHSTCK
			//std::cout << "PSHSTCK: " << getData(memory[pc + 1]) << std::endl;
			sp++;
			memory[sp] = registers[getData(memory[pc + 1])];
			pc++;
			break;
		case 12:
			//std::cout << "PSHREG: " << getData(memory[pc + 1]) << std::endl;
			registers[getData(memory[pc + 1])] = memory[sp];
			pc++;
			break;
		case 13: //IF
			if (memory[sp] == 0)
				false_if++;
			break;
		case 14: // ENDIF
			false_if--;
			break;
		case 15:
			if (memory[sp] == getData(memory[pc + 1]))
				false_if++;
			break;
		case 16: // RAW VALUE
			std::cout << "     RAW: " << memory[sp] << std::endl;
			break;
		case 17: // ASCII VALUE
			std::cout << "ASCII: " << char(memory[sp - 1]) << std::endl;
			break;
		}
	}
	else if (dat == 14) {
		false_if--;
	}
	else if (dat == 13) {
		false_if++;
	}
}

void Stack::fetch()
{
	pc++;
}

void Stack::decode()
{
	typ = getType(memory[pc]);
	dat = getData(memory[pc]);
}

void Stack::execute()
{
	if (typ == 0 || typ == 2 || typ == 3) {
		//sp++;
		//memory[sp] = dat;
	}
	else {
		doPrimitive();
	}
}

void Stack::run()
{
	pc--;
	while (running) {
		fetch();
		decode();
		execute();
		//std::cout << "TOS: " << memory[sp] << std::endl;
	}
}

void Stack::loadProgram(std::vector<i32> prog)
{
	for (i32 i = 0; i < prog.size(); i++) {
		memory[pc + i] = prog[i];
	}
}
