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

bool string_ok(string s)
{
	string result;

	for (auto iter = s.begin(); iter != s.end() - 1; ++iter)
	{
		if (*iter == *(iter + 1)) return false;
	}

	return true;
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

	copy(_R1(allchars), _OS(char)); _CR;

	// test all char pairs
	for (_R2(allchars))
	{
		for (auto iter2 = allchars.begin(); iter2 != allchars.end(); ++iter2)
		{
			if (*iter == *iter2) continue;

			set<char> test;
			for (auto iter3 = allchars.begin(); iter3 != allchars.end(); ++iter3)
			{
				if (*iter3 == *iter) continue;
				if (*iter3 == *iter2) continue;

				test.insert(*iter3);
			}

			copy(_R1(test), _OS(char)); _CR;

			string tested;
			for (auto iter3 = s.begin(); iter3 != s.end(); ++iter3)
			{
				auto keyfound = find(_R1(test), *iter3);

				if (keyfound == test.end())
					tested.push_back(*iter3);
			}

			if (string_ok(tested))
				result.push_back(tested.size());
		}
	}

	return *max_element(_R1(result));
}
