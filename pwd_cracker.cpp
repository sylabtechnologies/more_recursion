// 04_pwd_cracker.cpp : https://www.hackerrank.com/challenges/password-cracker/problem
// 

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <string>
using namespace std;

typedef vector<string>	Myvec;

#define _OS(x) ostream_iterator<x>(cout, " ")
#define _CR cout << endl
#define _R1(x) x.begin(), x.end()
#define _R2(x) auto iter = x.begin(); iter != x.end(); ++iter
#define PRN(x) cout << x << endl
#define PRV(x) copy(_R1(x), _OS(string)); _CR

Myvec get_solution(const Myvec&, const string&);

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

		Myvec sol = get_solution(passwords, attempt);

		if (sol.size() == 0)
			cout << "WRONG PASSWORD";
		else
		{
			for (_R2(sol))
			{
				cout << *iter;
				if (iter + 1 != sol.end()) cout << " ";
			}
		}
		cout << endl;

		t--;
	}

	return 0;
}

Myvec get_solution(const Myvec& passwords, const string& attempt)
{
	Myvec result;

	// check if it starts w/ one of the words
	for (_R2(passwords))
	{
		string test = attempt.substr(0, (*iter).length());

		if (*iter == test)
		{
			result.push_back(test);

			if (test.length() == attempt.length()) return result;

			Myvec next_result = get_solution(passwords, attempt.substr(test.length(), attempt.length() - test.length()));

			if (next_result.size() == 0) return next_result;

			for (_R2(next_result))
			{
				result.push_back(*iter);
			}

			return result;
		}
	}

	return result;
}
