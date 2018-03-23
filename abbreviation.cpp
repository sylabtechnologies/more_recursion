// try to graph from almost solution backwards
// https://www.hackerrank.com/challenges/abbr/problem

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <stdlib.h>
#include <ctype.h>
using namespace std;

#define _R1(x) x.begin(), x.end()
#define _R2(x) auto iter = x.begin(); iter != x.end(); ++iter
#define _OS(x) ostream_iterator<x>(cout, " ")
#define _CR cout << endl;
#define PRN(X) std::cout << X << std::endl
#define MAX(a,b) (a > b ? a : b)
#define MIN(a,b) (a < b ? a : b)
#define ISLWR(a) ( (a >= 'a' && a <= 'z') ? true : false)
#define ISUPR(a) ( (a >= 'A' && a <= 'Z') ? true : false)

typedef vector<char> Myvec;

Myvec vectorize(const string& s)
{
	Myvec result;
	for (_R2(s)) result.push_back(*iter);
	return result;
}

bool check_uppercase_residue(const Myvec& a, int x)
{
	for (int i = x; i < a.size(); i++)
	{
		if (ISUPR(a[i]))
			return false;
	}

	return true;
}

bool abbreviation(const Myvec& a, const Myvec& b, int x, int y)
{
	bool answer = false;

	// PRN(x); copy(_R1(a), _OS(char)); _CR;

	if (y == b.size()) return check_uppercase_residue(a, x);
	if (x == a.size()) return false;

	if (ISLWR(a[x]))
	{
		if (toupper(a[x]) == b[y])
			answer = abbreviation(a, b, x + 1, y + 1) || abbreviation(a, b, x + 1, y);
		else
			answer = abbreviation(a, b, x + 1, y);
	}
	else
	{
		if (a[x] == b[y])
			answer = abbreviation(a, b, x + 1, y + 1);
		else
			answer = false;
	}

	return answer;
}

int main()
{
	string a = "daBcd";
	string b = "ABC";
	bool result = abbreviation(vectorize(a), vectorize(b), 0, 0);

	_CR; _CR; PRN(result);

	return 0;
}
