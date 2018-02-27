#include <iostream>
#include "Stack.h"
#include <Windows.h>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>

std::vector<std::string> m_program;
std::vector<i32> m_prog;

void makeCode();

int main()
{
	std::fstream inf("main.ruc", std::ios::in);
	std::string rawprogram;
	while (std::getline(inf, rawprogram)) {
		std::string str = rawprogram;
		std::istringstream buf(str);
		std::istream_iterator<std::string> beg(buf), end;

		std::vector<std::string> tokens(beg, end); // done!
		for (auto& s : tokens)
			m_program.push_back(s);
	}
	//std::cout << (i32(0x40000010) & i32(0x3fffffff)) << std::flush;
	makeCode();
	Stack vm;
	vm.loadProgram(m_prog);
	vm.run();
	Sleep(500000);
	return 0;
}

void makeCode()
{
	for (int i = 0; i < m_program.size(); i++) {
		//std::cout << m_program[i] << std::endl;
		if (m_program[i][0] == '/' && m_program[i][1] == '/') {
		}
		else if (m_program[i] == "HALT") {
			m_prog.push_back(0x40000000); // 0
		}
		else if (m_program[i] == "ADD") {
			m_prog.push_back(0x40000001); // 1
		}
		else if (m_program[i] == "SUB") {
			m_prog.push_back(0x40000002); // 2
		}
		else if (m_program[i] == "MULT") {
			m_prog.push_back(0x40000003); // 3
		}
		else if (m_program[i] == "DIV") {
			m_prog.push_back(0x40000004); // 4
		}
		else if (m_program[i] == "MOD") {
			m_prog.push_back(0x40000005); // 5
		}
		else if (m_program[i] == "PSHR") {
			m_prog.push_back(0x40000006); // 6
		}
		else if (m_program[i] == "SWAP") {
			m_prog.push_back(0x40000007); // 7
		}
		else if (m_program[i] == "PSH") {
			m_prog.push_back(0x40000008); // 8
		}
		else if (m_program[i] == "SET") {
			m_prog.push_back(0x40000009); // 9
		}
		else if (m_program[i] == "MV") {
			m_prog.push_back(0x4000000A); // 10
		}
		else if (m_program[i] == "PSHSTCK") {
			m_prog.push_back(0x4000000B); // 11
		}
		else if (m_program[i] == "PSHREG") {
			m_prog.push_back(0x4000000C); // 12
		}
		else if (m_program[i] == "IF") {
			m_prog.push_back(0x4000000D); // 13
		}
		else if (m_program[i] == "ENDIF") {
			m_prog.push_back(0x4000000E); // 14
		}
		else if (m_program[i] == "IFE") {
			m_prog.push_back(0x4000000F); // 15
		}
		else if (m_program[i] == "PRNTR") {
			m_prog.push_back(0x40000010); // 16
		}
		else if (m_program[i] == "PRNTA") {
			m_prog.push_back(0x40000011); // 17
		}
		else {
			m_prog.push_back(std::stoi(m_program[i]));
		}
	}
}
