#include "support.h"
extern vector<string> alphabets;

extern SymbolTable symtab;

Alignment::Alignment(int t){
    T = t;
    create_fst();
}
void Alignment::create_fst(){
    for(int i =0; i<= T; i++){
        fst.AddState();
    }
    fst.SetStart(0);
    fst.SetFinal(T, 0);
    for (int i =0; i< T; i++){
        for(auto c: alphabets){
            fst.AddArc(i,StdArc(symtab.Find(c),symtab.Find(c),0,i+1));
        }
        fst.AddArc(i,StdArc(symtab.Find("epsilon"),symtab.Find("epsilon"),0,i+1));
    }
    
}
