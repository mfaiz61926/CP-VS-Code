/******************************************************************************

                              بسم الله الرحمان الرحيم
author:mfaiz_1

*******************************************************************************/
#include "bits/stdc++.h"
#define int long long
#define uint unsigned long long
#define vi vector<int>
#define vvi vector<vi >  
#define vb vector<bool>
#define vvb vector<vb >
#define fr_3(i,n) for(int i=0; i<(n); i++)
#define fb_3(i,a,n) for(int i=(a); i<=(n); i++)
#define nl cout<<"\n"
#define dbg(var) cout<<#var<<"="<<var<<" "
#define all_3(v) v.begin(),v.end()
#define srt_3(v)  sort(v.begin(),v.end())         // sort 
#define mxe_3(v)  *max_element(v.begin(),v.end())     // find max element in vector
#define mne_3(v)  *min_element(v.begin(),v.end())     // find min element in vector
#define unq_3(v)  v.resize(distance(v.begin(), unique(v.begin(), v.end())));
// make sure to sort before applying unique // else only consecutive duplicates would be removed 
#define bin(x,y)  bitset<y>(x) 
using namespace std;
     // Hardcoded, directly change from here for functions!



int MOD=1e9+7; 
void mod_add(int &a , int b) {a=((a%MOD)+(b%MOD))%MOD;}
void mo_dsub(int &a , int b) {a=((a%MOD)-(b%MOD)+MOD)%MOD;}
void mo_dmul(int &a , int b) {a=((a%MOD)*(b%MOD))%MOD;}
// ================================== take ip/op like vector,pairs directly!==================================
template<typename typC,typename typD> istream &operator>>(istream &cin,pair<typC,typD> &a) { return cin>>a.first>>a.second; }
template<typename typC> istream &operator>>(istream &cin,vector<typC> &a) { for (auto &x:a) cin>>x; return cin; }
template<typename typC,typename typD> ostream &operator<<(ostream &cout,const pair<typC,typD> &a) { return cout<<a.first<<' '<<a.second; }
template<typename typC,typename typD> ostream &operator<<(ostream &cout,const vector<pair<typC,typD>> &a) { for (auto &x:a) cout<<x<<'\n'; return cout; }
template<typename typC> ostream &operator<<(ostream &cout,const vector<typC> &a) { int n=a.size(); if (!n) return cout; cout<<a[0]; for (int i=1; i<n; i++) cout<<' '<<a[i]; return cout; }
// ===================================END Of the input module ==========================================


void funny_3(){
    
}

int32_t main()
{
 
 ios_base::sync_with_stdio(false);
 cin.tie(NULL);

    int t_c_3= 1;
    cin >> t_c_3;
    while (t_c_3--)
    {
        funny_3();
    }
    return 0;
}

    

class STree{        
private:

    // [IMPORTANT]  CHANGE this function as required. 
    int defaultVal=INT_MAX;
    vector<int> tree,lazy;
    int n;
    
    // [IMPORTANT] CHANGE this function as required.
    void pushDown(int v,int tl, int tr){    // if your current node had some changes and it's there in the lazy vector i.e. 
    // lazy[v] that means they weren't propagated to it's children .... .


        // this block is responsible for adding the values to both the left and right children.
        // the limits of these children are from tl to tmid & tmid+1,tl
        int tmid=(tl+tr)>>1;
        // the below is an example for adding a value to all nodes in the range 
        // and utilising the tree for minimum in the range
        tree[v*2]+=lazy[v];
        tree[v*2+1]+=lazy[v];
        lazy[v*2]+=lazy[v];         // take a note that you made some changes that haven't been passed on to your children . 
        lazy[v*2+1]+=lazy[v];           

        //once the updates are pushed to the children the parent can get rid of the update!
        lazy[v]=0;  // my responsibility is completely I've told the changes to my children.. now it's their headache!!!!1  
    }


    // [IMPORTANT] CHANGE this function as required.
    void combine(int v){  
        tree[v]=min(tree[v<<1],tree[v<<1|1]);
    }
    
    int query(int v, int tl, int tr, int l, int r) {      
        if (tr <tl) return defaultVal;
        if(tl>r || tr<l)    return defaultVal;       // invalid indices tried!
        if (l <= tl && r >= tr) return tree[v];     // the current segment completely belongs to the answer
        int tm = (tl + tr)>>1;
        pushDown(v,tl,tr);
        combine(v);

        // [IMPORTANT] CHANGE this code below as required.
        return min(query(v<<1, tl, tm, l, r)  , query(v<<1|1, tm+1, tr, l, r));
    }
    void buildTree(vector<int>& a,int tl, int tr,int v=1){  // builds up the tree starting from the root.
        if(tl>tr) return;
        if(tl==tr){
            tree[v]=a[tl];
            return;
        }
        int mid=(tl+tr)>>1;
        buildTree(a,tl,mid,v<<1);
        buildTree(a,mid+1,tr,v<<1|1);
        combine(v);
    }
    void update(int l,int r,int val,int v,int tl,int tr){
        if(tl>tr) return;
        if(tl>r || tr<l)  return;     //not in the current range
        
        if(tl>=l && tr<=r){        // [IMPORTANT] CHANGE the code below as required.
        // if the subtree is completely inside the range then update the current node ... 
        // also make sure your children can get this info in the future if and when they need it ...
            tree[v]+=val;   // update the value! 
            lazy[v]+=val;   // this is just for reference for the children and not for the current node as your current node is already updated!   
            return;         // return;
        }
        pushDown(v,tl,tr);          // notifying my children of the changes (if any! )
        int tmid=(tl+tr)>>1;
        update(l,r,val,v<<1,tl,tmid);
        update(l,r,val,v<<1|1,tmid+1,tr);
        combine(v);
    }
public:
    STree(vector<int>& vec){
        n=vec.size();
        tree.assign(n<<2,defaultVal);       // all nodes initially have default values 
        lazy.assign(n<<2,0);
        buildTree(vec,0,n-1);
    }

    int query(int l,int r){             // query in the range l to r.
        return query(1,0,n-1,l,r);
    }
    void update(int idx,int val){       // this is overloaded for point updates
        update(idx,idx,val,1,0,n-1);
    }
    void update(int l,int r,int val){     
        update(l,r,val,1,0,n-1);
    }
};