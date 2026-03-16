#include <bits/stdc++.h>
using namespace std;

struct Node {
    string op;
    int id;
    vector<Node*> child;
};

vector<string> tok;
int posi;

Node* parse(){
    if(isdigit(tok[posi][0])){
        Node* t=new Node();
        t->op="var";
        t->id=stoi(tok[posi++]);
        return t;
    }

    Node* t=new Node();
    t->op=tok[posi++]; // min/max

    posi++; // (

    while(true){
        t->child.push_back(parse());

        if(tok[posi]==","){
            posi++;
            continue;
        }

        if(tok[posi]==")"){
            posi++;
            break;
        }
    }

    return t;
}

long long eval(Node* node, vector<long long>& x){

    if(node->op=="var")
        return x[node->id-1];

    long long res = eval(node->child[0],x);

    for(int i=1;i<node->child.size();i++){
        long long v=eval(node->child[i],x);

        if(node->op=="min") res=min(res,v);
        else res=max(res,v);
    }

    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin>>t;

    while(t--){

        int n;
        cin>>n;

        tok.clear();

        string s;
        getline(cin,s);
        getline(cin,s);

        stringstream ss(s);
        string w;

        while(ss>>w)
            tok.push_back(w);

        posi=0;
        Node* root=parse();

        while(true){

            long long first;
            if(!(cin>>first)) return 0;

            if(first==0) break;

            vector<long long> x(n);
            x[0]=first;

            for(int i=1;i<n;i++)
                cin>>x[i];

            cout<<eval(root,x)<<"\n";
        }
    }
}