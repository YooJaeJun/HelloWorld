#include <string>
#include <vector>

int solution(std::string s) {
	static const struct { std::string str; std::string num; } Arr[10]{
		{"zero" , "0"},
		{"one"  , "1"},
		{"two"  , "2"},
		{"three", "3"},
		{"four" , "4"},
		{"five" , "5"},
		{"six"  , "6"},
		{"seven", "7"},
		{"eight", "8"},
		{"nine" , "9"}
	};

	std::size_t offset = 0;
	for (const auto& elem : Arr) {
		while (true)
		{
			offset = s.find(elem.str);
			if (offset == std::string::npos)
			{
				break;
			}
			s.replace(offset, elem.str.length(), elem.num);
		}
	}

	return std::stoi(s);
}