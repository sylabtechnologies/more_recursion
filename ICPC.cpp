// ICPC.cpp : https://www.hackerrank.com/challenges/acm-icpc-team/problem
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <set>
#include <iterator>
#include <algorithm>
#include <string>
#include <fstream>
using namespace std;

#define _R1(x) x.begin(), x.end()
#define _R2(x) auto iter = x.begin(); iter != x.end(); ++iter
#define _OS(x) ostream_iterator<x>(cout, " ")
#define _CR cout << endl
#define PRN(x) cout << x << endl
#define PRV(x) copy(_R1(x), _OS(int)); _CR

struct Team
{
	int first;
	int second;
};

typedef vector<Team> Myvec;
typedef vector<int> Mivec;

// all permutations
Myvec all_perms(const int n)
{
	Myvec ans;
	Myvec addon;

	if (n == 1) return ans;

	Team next{ 1, 2 };
	ans.push_back(next);
	if (n == 2) return ans;

	ans = all_perms(n - 1);

	for (int i = 1; i <= n - 1; i++)
	{
		next.first = i;
		next.second = n;
		ans.push_back(next);
	}

	return ans;
}

int count_topics(const string& topic1, const string& topic2)
{
	int ans = 0;

	if (topic1.length() != topic2.length())
	{
		cout << "Internal error" << endl;
		exit(1);
	}

	for (int i = 0; i < topic1.length(); i++)
	{
		if (topic1[i] == '0' && topic2[i] == '0') continue;
		ans++;
	}

	return ans;
}


Mivec acm_team(const int n, vector<string>& topic)
{
	int max_topics = 0;
	Myvec teams = all_perms(n);
	Mivec answers;

	for (auto iter = teams.begin(); iter != teams.end(); ++iter)
	{	
		int count = count_topics(topic[iter->first - 1], topic[iter->second - 1]);

		answers.push_back(count);
		// if (count > max_topics) max_topics = count;
	}

	int mymax = *max_element(_R1(answers));
	auto mytest = [&](int i) {return i == mymax;};
	int howmany = count_if(_R1(answers), mytest);
	
	return Mivec{ mymax, howmany };
}

int main()
{
	vector<string> topic;
	topic.push_back("10101");
	topic.push_back("11100");
	topic.push_back("11010");
	topic.push_back("00101");

	Mivec a = acm_team(4, topic);

    return 0;
}

