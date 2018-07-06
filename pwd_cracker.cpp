// 04_pwd_cracker.cpp : https://www.hackerrank.com/challenges/password-cracker/problem
// - memoize all in GLookup

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <iterator>
#include <string>
using namespace std;

typedef vector<string> Myvec;
typedef vector<size_t> Mysol;

#define _OS(x) ostream_iterator<x>(cout, " ")
#define _CR cout << endl
#define _R1(x) x.begin(), x.end()
#define _R2(x) auto iter = x.begin(); iter != x.end(); ++iter
#define PRN(x) cout << x << endl
#define PRV(x) copy(_R1(x), _OS(string)); _CR

Mysol get_solution(const Myvec&, const string&);

// look up here:
map<string, Mysol> GLookup;

int main()
{
	int t;

	cin >> t;

	while (t > 0)
	{
		int n;
		cin >> n;

		Myvec passwords;
		while (n > 0)
		{
			string temp;

			cin >> temp;
			passwords.push_back(temp);

			n--;
		}

		string attempt;
		cin >> attempt;

		Mysol sol = get_solution(passwords, attempt);

		if (sol.size() == 0)
			cout << "WRONG PASSWORD" << endl;
		else
		{
			for (_R2(sol))
			{
				cout << passwords[*iter];
				if (iter + 1 != sol.end()) cout << " ";
			}
			cout << endl;

		}

		t--;
	}

	return 0;
}

Mysol get_solution(const Myvec& passwords, const string& attempt)
{
	Mysol result;

	auto g_iter = GLookup.find(attempt);
	if (g_iter != GLookup.end()) return g_iter->second;

	// check if it starts w/ one of the words
	for (size_t i = 0; i < passwords.size(); i++)
	{
		string test = attempt.substr(0, passwords[i].length());

		if (passwords[i] == test)
		{
			result.push_back(i);

			if (test.length() == attempt.length()) return result;

			Mysol next_result = get_solution(passwords, attempt.substr(test.length(), attempt.length() - test.length()));

			if (next_result.size() == 0) return next_result;

			for (_R2(next_result))
			{
				result.push_back(*iter);
			}

			GLookup[attempt] = result;
			return result;
		}
	}

	return result;
}
