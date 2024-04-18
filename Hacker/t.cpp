#include <fst/fstlib.h>
#include <bits/stdc++.h>

using namespace std;
using namespace fst;

//**** Structure of StdArc ****//
/* 
struct StdArc {
  typedef int Label;
  typedef TropicalWeight Weight;  // see "FST Weights" below 
  typedef int StateId; 
  Label ilabel;
  Label olabel;
  Weight weight;
  StateId nextstate;
};
*/
SymbolTable symtab;

void create_symbol_table(vector<string> &alphabets, SymbolTable* symtab){
	for(auto c : alphabets){
		symtab->AddSymbol(c);
	}
}

float get_string_weight(fst::StdVectorFst fst, string input_string){
	fst::StdVectorFst input_fst;
	input_fst.AddState();
	input_fst.SetStart(0);

	for (char c : input_string) {
		input_fst.AddState();
		string c_ = "";
		c_ += c;
		input_fst.AddArc(input_fst.NumStates() - 2, StdArc(symtab.Find(c_), symtab.Find(c_), 1, input_fst.NumStates()-1));
	}
cout<<endl;
	input_fst.SetFinal(input_fst.NumStates() - 1, 5);
	
	fst::StdVectorFst result;

	cout<<"FST-ORIGINAL "<<fst.NumStates()<<endl;
	fst.Write("actual.fst");

	cout<<"FST-INPUT-STRING "<<fst.NumStates()<<endl;
	input_fst.Write("input.fst");

  	ArcSort(&input_fst, StdOLabelCompare());
  	ArcSort(&fst, StdILabelCompare());

	Compose(fst, input_fst, &result);
	result.Write("composed.fst");

	cout<<"FST-COMPOSED "<<result.NumStates()<<endl;

	vector<StdArc::Weight> distances;

	ShortestDistance(result, &distances);
	
	for(auto c : distances){
		cout<<c<<" ";
	}
	cout<<endl;
	// return distances[distances.size()-1].Value();
	return 0.99;
}

// class Context{
// 	int n; // n-gram context dependency
// 	fst::StdVectorFst fst; // The fst underlying in the context fst

// };

// class Alignment{

// };

// class Weight{

// };

int main(){

	vector<string> alphabets = {"a", "b", "c"};

	create_symbol_table(alphabets, &symtab);

	fst::StdVectorFst fst;


	fst.AddState();
	fst.SetStart(0);

	fst.AddState();

	fst.AddState();
	fst.AddArc(0, StdArc(symtab.Find("a"), symtab.Find("a"), 3.4, 1));
	fst.AddArc(1, StdArc(symtab.Find("b"), symtab.Find("b"), 2, 2));

	fst.SetFinal(2, 3.5);

	cout<<get_string_weight(fst, "ab");
}
// int main(){
//   // A vector FST is a general mutable FST 
//   fst::StdVectorFst fst;

// // Adds state 0 to the initially empty FST and make it the start state. 
// fst.AddState();   // 1st state will be state 0 (returned by AddState) 
// fst.SetStart(0);  // arg is state ID

// // Adds two arcs exiting state 0.
// // Arc constructor args: ilabel, olabel, weight, dest state ID. 
// fst.AddArc(0, StdArc(1, 1, 0.5, 1));  // 1st arg is src state ID 
// fst.AddArc(0, StdArc(1, 1, 1.5, 1)); 

// // Adds state 1 and its arc. 
// fst.AddState();
// fst.AddArc(1, StdArc(3, 3, 2.5, 2));

// // Adds state 2 and set its final weight. 
// fst.AddState();
// fst.SetFinal(2, 3.5);  // 1st arg is state ID, 2nd arg weight 

// StdArc x = StdArc(3, 3, 2.5, 2);

// cout<<x.weight<<endl;
// fst.Write("binary.fst");
// }