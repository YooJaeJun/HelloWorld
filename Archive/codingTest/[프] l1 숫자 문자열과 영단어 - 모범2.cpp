#include <string>
#include <vector>

using namespace std;

string solution(string new_id) {
	for (auto& c : new_id)
	{
		if (std::isupper(c))
		{
			c += 'a' - 'A';
		}
	}

	for (auto iter = new_id.begin(); iter != new_id.end();)
	{
		const char c = *iter;
		if (!(std::isalpha(c) || std::isalnum(c) || c == '-' || c == '_' || c == '.'))
		{
			iter = new_id.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	if (new_id.size() > 0)
	{
		char prev_char = new_id[0];
		for (auto iter = new_id.begin() + 1; iter != new_id.end();)
		{
			const char cur_char = *iter;
			if (cur_char == '.' && cur_char == prev_char)
			{
				prev_char = *iter;
				iter = new_id.erase(iter);
			}
			else
			{
				prev_char = *iter;
				++iter;
			}
		}
	}

	if (new_id.size() > 0)
	{
		if (new_id.front() == '.')
		{
			new_id.erase(new_id.begin());
		}
	}

	if (new_id.size() > 0)
	{
		if (new_id.back() == '.')
		{
			new_id.pop_back();
		}
	}

	if (new_id.size() == 0)
	{
		new_id = "a";
	}

	if (new_id.size() >= 16)
	{
		new_id = string(new_id.begin(), new_id.begin() + 15);
	}

	if (new_id.size() > 0)
	{
		if (new_id.back() == '.')
		{
			new_id.pop_back();
		}
	}

	while (new_id.size() <= 2)
	{
		new_id += new_id.back();
	}

	return new_id;
}