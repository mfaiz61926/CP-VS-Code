#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        int n;
        scanf("%d",&n);
        char x[200001];
        scanf("%s",x);
        bool f[2]={true,false};
        bool ok=true;
        for(int k=0;k<n&&ok;k++){
            bool nf[2]={false,false};
            if((n-1-k)%2==0){
                for(int p=0;p<2;p++){
                    if(!f[p])continue;
                    char c=(p==0)?'a':'b';
                    if(x[k]!='?'&&x[k]!=c)continue;
                    nf[p]=true;
                    nf[1-p]=true;
                }
            } else {
                if(f[0]||f[1]){
                    if(x[k]=='a'||x[k]=='?') nf[1]=true;
                    if(x[k]=='b'||x[k]=='?') nf[0]=true;
                }
            }
            f[0]=nf[0]; f[1]=nf[1];
            if(!f[0]&&!f[1]) ok=false;
        }
        puts(ok?"YES":"NO");
    }
}