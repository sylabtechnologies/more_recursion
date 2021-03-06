// Greedy_beautiful_pairs.cpp : https://www.hackerrank.com/challenges/beautiful-pairs/problem

#include <bits/stdc++.h>
using namespace std;

typedef vector<int> I_vec;
typedef map<int, int> I_map;

int count_btf_pairs(const I_vec& A, const I_vec& B)
{
	size_t N_size = A.size();
	int result = 0;
	I_map indx_map;

	for (size_t i = 0; i < N_size; i++)
	{
		indx_map[A[i]]++;
	}

	// find all matches that we can count
	for (size_t i = 0; i < N_size; i++)
	{
		int curr_indx = B[i];
		if (indx_map[curr_indx] > 0)
		{
			indx_map[curr_indx]--;
			result++;
		}
	}

	if (result == N_size)
		result--;
	else
		result++;

	return result;
}

int main()
{
    int N;
    int temp;
    I_vec A, B;
    
    cin >> N;
    
    for (int i=0; i < N; i++)
    {
        cin >> temp;
        A.push_back(temp);
    }
    
    for (int i=0; i < N; i++)
    {
        cin >> temp;
        B.push_back(temp);
    }
    
    cout << count_btf_pairs(A, B) << endl;

}