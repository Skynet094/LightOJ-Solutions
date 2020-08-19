/*Skynet094*/
#include<iostream>
#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<cstdlib>
#include<string>
#include<cstring>
#include<set>
#include<algorithm>
#define MAX_VAL 150
#define MAX(a,b) return (a) >= (b) ? (a) : (b)
#define VI vector<int> 
#define LLInt long long int
#define PII pair<int,int> 
#define PLLI pair<dll,dll>
#define REP(i,a,b) for(int i=a;i<b;i++)
#define REP_D(i,a,b) for(int i=a;i>b;i--)
#define ITER_SETI(name) for(set<int>::iter=name.begin();iter!=name.end();iter++)
#define ITER_MAPII(name) for(map<int,int>::iter=name.begin();iter!=name.end();iter++)
#define VECT(class_name) vector <class_name>
#define CLEAR(name) memset(name,0,sizeof(name))
using namespace std;
 
int parent[MAX_VAL];
 
struct point
{
    int u,v,w;
}_point;
 
bool comp_A(point A,point B)
{
    return A.w>B.w;
}

VECT(point) store;
 
int find_r(int r)
{
    return parent[r]==r ? r : parent[r]=find_r(parent[r]);
}
 
void init_set(int n)
{
    for(int i=0;i<n;i++)
        parent[i]=i;
}
 
LLInt mst(int n)
{
    init_set(n);
 
    int count=0;
    LLInt sum_min=0;
    LLInt sum_max=0;
 
    sort(store.begin(),store.end(),comp_A);
  
    //determining the minimum spanning tree weight
    REP(i,0,(int)store.size())
    {
        int u_r=find_r(store[i].u);
        int v_r=find_r(store[i].v);
       
        if(u_r!=v_r)
        {
            if(count==n-1)
                break; 

            parent[u_r]=v_r;
            sum_min+=store[i].w;
            count++;
        }
    }
  
    init_set(n);
 
    count=0;
    //determining the maximum spanning tree weight
    REP_D(i,(int)store.size()-1,-1)
    {
        int u_r=find_r(store[i].u);
        int v_r=find_r(store[i].v);

        if(u_r!=v_r)
        {
            if(count==n-1)
                break;

            parent[u_r]=v_r; 
            sum_max+=store[i].w;
            count++;
        }
    }

    return  (sum_max+sum_min);
}
 
int main(void)
{
    int testcase=0,caseno=0;
    
    int n;
    
    cin>>testcase;
    
    while(testcase--)
    { 
        store.clear();
    
        cin>>n;   
        int u,v,w;
    
        while(cin>>u>>v>>w)
        {
            //taking values upto , 0 0 0 is given
            if(!u && !v && !w)  
                break;
            _point.u=u;
            _point.v=v;
            _point.w=w;
    
            store.push_back(_point);
        }
    
        LLInt result=mst(n+1);  
    
        if(!(result%2))
            printf("Case %d: %lld\n",++caseno,result/2);
        else
            printf("Case %d: %lld/2\n",++caseno,result);
    }
    
    return 0;
}