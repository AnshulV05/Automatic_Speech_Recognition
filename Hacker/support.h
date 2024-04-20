

#include <fst/fstlib.h>
#include <bits/stdc++.h>
#include <fst/project.h>
#include <Eigen/Dense>

using namespace std;
using namespace fst;
using namespace Eigen;

class Context{
public:
	map<string, int> state_map;
	int num_states;
	int n; // n-gram context dependency
	fst::StdVectorFst fst; // The fst underlying in the context fst
	vector<string> string_states;
    Context(int n);
	Context();
	string next_state (string s, string c);
	void generateStrings(string current);
	void create_fst();
	bool check_edge(int i, int j);
};

class Alignment{
public:
	int T;
	fst::StdVectorFst fst; // The fst underlying in the alignment fst
	Alignment(int t);
	void create_fst();
};


// #endif