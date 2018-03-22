// https://www.hackerrank.com/challenges/two-characters

#include <iostream>
#include <vector>
#include <set>
#include <iterator>
#include <string>
#include <algorithm>
using namespace std;

#define _R1(x) x.begin(), x.end()
#define _R2(x) auto iter = x.begin(); iter != x.end(); ++iter
#define _OS(x) ostream_iterator<x>(cout, " ")
#define _CR cout << endl;
#define PRN(X) std::cout << X << std::endl
#define TRC(x) cout << #x << ": " << x << endl

bool string_ok(const string& s)
{
	string result;

	if (s.size() < 2) return true;

	for (auto iter = s.begin(); iter != s.end() - 1; ++iter)
	{
		if (*iter == *(iter + 1)) return false;
	}

	return true;
}

string string_mapped(const string& s, const char key1, const char key2)
{
	string result;

	for (_R2(s))
	{
		if (*iter == key1 || *iter == key2)
			result.push_back(*iter);
	}

	return result;
}

int twoCharacters(string s)
{
	set<char> allchars;
	vector<int> result;

	// count all chars
	for (_R2(s))
	{
		allchars.insert(*iter);
	}

	if (allchars.size() <= 2) return 0;

	// copy(_R1(allchars), _OS(char)); _CR;

	// test all char pairs
	for (_R2(allchars))
	{
		auto iter2 = allchars.begin();

		if (iter2 == allchars.end())
			break;
		else
			++iter2;

		for (; iter2 != allchars.end(); ++iter2)
		{
			string tested = string_mapped(s, *iter, *iter2);

			if (tested.size() <= 0) continue;

			if (string_ok(tested))
				result.push_back(tested.size());
		}
	}

	return *max_element(_R1(result));
}
