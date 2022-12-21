#include <iostream>

template<typename T>
concept integral = std::is_integral_v<T>;

int main()
{
	std::cout << "Hello World\n";
}