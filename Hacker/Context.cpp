#include "support.h"

extern vector<string> alphabets;

extern SymbolTable symtab;

Context::Context(int n){
    num_states = 0;
    this->n = n;
    generateStrings("");
    create_fst();
}

// Context::Context(){}

string Context::next_state (string s, string c){
    if(s.length() < n) {
        s = s+c;
    }
    else{
        s = s+ c;
        s = s.substr(1);
    }	
    return s;
}

void Context::generateStrings(string current) {
    
    state_map[current] = num_states++;
    string_states.push_back(current);
    if (current.size() == n) {
        return;
    }
    
    for (string ch : alphabets) {
        generateStrings(current+ch);
    }
}
void Context::create_fst(){

    for( int i =0 ; i< num_states; i++){
        fst.AddState();
        fst.SetFinal(i, 0);
    }
    fst.SetStart(0);

    for( int i =0 ; i< num_states; i++){
        for(auto j:alphabets){
            fst.AddArc(i,StdArc(symtab.Find(j),symtab.Find(j),0,state_map[next_state(string_states[i],j)]));
        }
        fst.AddArc(i,StdArc(symtab.Find("epsilon"),symtab.Find("epsilon"),0,i));
    }

}

bool Context::check_edge(int i, int j){
    for(ArcIterator<fst::StdVectorFst> aiter(fst, i); !aiter.Done(); aiter.Next()){
        if(aiter.Value().nextstate == j && aiter.Value().ilabel != 0){
            return true;
        }
    }
    return false;
}
