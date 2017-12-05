#include <string>
#include <iostream>
#include <iomanip>

int main(int, char*[]) {
	std::string input;
	std::cin >> input;
	std::cout << "Input is: " << std::quoted(input) << std::endl;
	auto len = input.size();
	input += input;
	size_t i = 0;
	int sum = 0;
	std::cout << "0";
	for (auto it = input.begin(); i < len; i++, it++) {
		if (*it != *(it + (len / 2))) continue;
		sum += (int)(*it) - 48;
		std::cout << " + " << ((int)(*it) - 48) << " = " << sum;
	} 

	std::cout << std::endl << "Sum is: " << sum << std::endl;
}

