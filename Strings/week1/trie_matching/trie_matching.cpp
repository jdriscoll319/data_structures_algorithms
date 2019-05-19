#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int const Letters =    4;
int const NA      =   -1;

struct Node
{
	int next [Letters];

	Node ()
	{
		fill (next, next + Letters, NA);
	}

	bool isLeaf () const
	{
	    return (next[0] == NA && next[1] == NA && next[2] == NA && next[3] == NA);
	}
};

int letterToIndex (char letter)
{
	switch (letter)
	{
		case 'A': return 0; break;
		case 'C': return 1; break;
		case 'G': return 2; break;
		case 'T': return 3; break;
		default: assert (false); return -1;
	}
}

void build_trie(vector<Node>& trie, const vector<string>& patterns)
{
	int idx = 0;

	for (const auto & pattern : patterns)
	{
		int level = 0;
		for (const auto & c : pattern)
		{
			if (trie[level].next[letterToIndex(c)] != NA)
				level = trie[level].next[letterToIndex(c)];
			else
			{
				trie[level].next[letterToIndex(c)] = ++idx;
				level = idx;
				trie.resize(trie.size() + 1);
			}
		}
	}
}

bool match_pattern(const vector<Node>& trie, const string& text, int idx)
{
	char c = text[idx];
	int level = 0;
	while (trie[level].next[letterToIndex(c)] != NA)
	{
		level = trie[level].next[letterToIndex(c)]; 
		if (trie[level].isLeaf())
			return true;

		if (idx < text.size() -1)
			c = text[++idx];
		else
			return false;
		
	}
	return false;
}

vector <int> solve (const string& text, int n, const vector <string>& patterns)
{
	vector <int> result;
	vector<Node> trie(1);

	build_trie(trie, patterns);

	for (int i = 0; i < text.size(); ++i)
	{
		char c = text[i];
		if (trie[0].next[letterToIndex(c)] != NA)
		{
			if (match_pattern(trie, text, i))
				result.push_back(i);
		}
	}

	return result;
}

int main (void)
{
	string t;
	cin >> t;

	int n;
	cin >> n;

	vector <string> patterns (n);
	for (int i = 0; i < n; i++)
	{
		cin >> patterns[i];
	}

	vector <int> ans;
	ans = solve (t, n, patterns);

	for (int i = 0; i < (int) ans.size (); i++)
	{
		cout << ans[i];
		if (i + 1 < (int) ans.size ())
		{
			cout << " ";
		}
		else
		{
			cout << endl;
		}
	}

	return 0;
}
