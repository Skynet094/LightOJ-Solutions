/*Skynet094*/
#include<bits/stdc++.h>
#define MAX 1000000+50
#define max_val 10000000
#define REP(i,a,b) for(int i=a;i<b;i++)
using namespace std;
 
int tree[MAX*3];
int arr[MAX];
 
void init(int node,int b,int e)
{
    if(b==e)
    {
        tree[node]=arr[b];
        return;
    }
 
    int left_child=2*node;
    int right_child=2*node+1;
    int mid=(b+e)/2;
 
    init(left_child,b,mid);
    init(right_child,mid+1,e);
 
    if(tree[left_child]>=tree[right_child])
        tree[node]=tree[right_child];
    else
        tree[node]=tree[left_child];
    return;
}
 
 
int queries(int node,int b,int e,int i,int j)
{
    if(i>e || b>j)
        return max_val;
 
    if(b>=i && e<=j)
        return tree[node];
 
    int left_child=2*node;
    int right_child=2*node+1;
 
    int mid=(b+e)/2;
 
    int left_min=queries(left_child,b,mid,i,j);
    int right_min=queries(right_child,mid+1,e,i,j);
 
    return left_min>= right_min ? right_min : left_min;
}
 
 
int main(void)
{
    int testcase,caseno=0;
    scanf("%d",&testcase);
 
    while(testcase--)
    {
        memset(arr,0,sizeof(arr));
        memset(tree,0,sizeof(tree));
 
        int n,m,I,J;
        scanf("%d %d",&n,&m);
 
        REP(i,0,n)
            scanf("%d",&arr[i]);
 
        init(1,0,n-1);
 
        printf("Case %d:\n",++caseno);
 
        while(m--)
        {
            scanf("%d %d",&I,&J);
            int val=queries(1,0,n-1,I-1,J-1);
            printf("%d\n",val);
        }
    }
return 0;
}