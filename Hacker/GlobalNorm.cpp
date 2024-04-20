#include"support.h"



vector<string> alphabets = {"a", "b"};

SymbolTable symtab;
bool option=false;

void create_symbol_table(vector<string> &alphabets, SymbolTable* symtab){
	for(auto c : alphabets){
		symtab->AddSymbol(c);
	}
}

class Glob_Norm_ASR{
	public: 
	int C;
	int T;
	int N;
	vector<Eigen::MatrixXf> wt_sigma;
	vector<Eigen::MatrixXf> wt_epsilon;
	Context* Cont;
	Glob_Norm_ASR(int N, int C,int T, Context& cont, Alignment& alg){
		this->N = N;
		this->C = C;
		this->T = T;
		Cont=&cont;
		wt_sigma=vector<Eigen::MatrixXf>(T,Eigen::MatrixXf(C, C));
		wt_epsilon=vector<Eigen::MatrixXf>(T,Eigen::MatrixXf(C, C));

		for(int i=0;i<T;i++){
			for(int j=0;j<C;j++){
				for(int k=0;k<C;k++){
					if(cont.check_edge(j, k)) {wt_sigma[i](j, k)= option?rand()%100:1;} // Change this According to weight
					else{
						wt_sigma[i](j, k)= 0;
					}
					if(j==k){ wt_epsilon[i](j, k)= option?rand()%100:1;} // Change this According to weight
					else{
						wt_epsilon[i](j, k)= 0;
					}
				}
			}
		}
	}
	Glob_Norm_ASR(){}

	float get_denominator(){

		Eigen::MatrixXf alpha(1,C);  
		for (int i =0; i< C; i++){
			alpha(0,i) = 0;
		}
		alpha(0,0)=1;
		for(int i=0;i<T;i++){
			alpha=alpha*(wt_sigma[i]+wt_epsilon[i]);
		}

		return alpha.sum();
	}

	float get_numerator(string s){
		Eigen::MatrixXf v(T+1,s.length()+1);
		for(int i=0;i<=T;i++){
			for(int j=0;j<=s.length();j++){
				v(i,j)=0;
			}
		}
		v(0,0)=1;
		for(int i=1;i<=T;i++){
			v(i,0)=wt_epsilon[i-1](0,0)*v(i-1,0);

			for(int j=1;j<=s.length();j++){

				string s1=s.substr(0,j-1),s2=s.substr(0,j);

				if(s1.length()>N)s1=s.substr(j-1-N,N);
				if(s2.length()>N)s2=s.substr(j-N,N);
				int i1=Cont->state_map[s1],i2=Cont->state_map[s2];

				v(i,j)=wt_epsilon[i-1](i2,i2)*v(i-1,j)+
						wt_sigma[i-1](i1,i2)*v(i-1,j-1);
			}
		}
		return v(T,s.length());
	}
	vector<string> all_strings;
	void generateStrings( string current ) {
		
		all_strings.push_back(current);
		if(current.length()==T)return;
		for (string ch : alphabets) {
			generateStrings( current + ch);
		}
	}
	
	void get_pdf(){
		int deno=get_denominator();
		generateStrings("");
		cout<<"\tString\tProbability\n";
		float f;
		for(auto i:all_strings){
			float f1=get_numerator(i);
			cout<<"\t"<<i<<"\t"<<f1/deno<<endl;
			f+=get_numerator(i)/deno;
		}
		cout<<"\tSUM\t"<<f<<endl;
	}
};

int main(){
	int n,T;
	cout<<"Enter the n for nth order markovian\n";
	cin>>n;

	cout<<"Enter the number of timesteps\n";
	cin>>T;
	cout<<"Select initialisation of weights (0 for uniform 1 for random)\n";
	cin>> option;

	symtab.AddSymbol("epsilon");
    create_symbol_table(alphabets, &symtab);
	Context context_fsa = Context(n);
    context_fsa.fst.Write("context.fst");
	

	Alignment alignment_fsa = Alignment(T);
    alignment_fsa.fst.Write("alignment.fst");

	fst::StdVectorFst composed_fsa; // The fst composed
	
	// fst::StdVectorFst projected_c, projected_a;

	// Project(alignment_fsa.fst, &projected_a, ProjectType::INPUT);
	// Project(context_fsa.fst, &projected_c, ProjectType::INPUT);

	// ArcSort(&projected_a, StdOLabelCompare());
	// ArcSort(&projected_c, StdILabelCompare());

	// Intersect(projected_a, projected_c, &composed_fsa);
	int C = ((1<<(n+1))-1);
	Glob_Norm_ASR x = Glob_Norm_ASR(n, C, T, context_fsa, alignment_fsa);
	x.get_pdf();
	

}