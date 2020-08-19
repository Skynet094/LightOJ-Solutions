#include<bits/stdc++.h>
using namespace std;
 
#define MAX 100000 + 5
 
struct TreeNode
{
    int maxVal;
    int minVal;
 
    TreeNode()   
    {
        maxVal = -1;
        minVal = INT_MAX;
    }
};
 
 
int arr[ MAX ];
TreeNode Tree[3 * MAX];
 
TreeNode makeTree(int b, int e, int nodeNumber)
{
    if(b > e)
    {
        TreeNode a;
        a.maxVal = -500;
        a.minVal =  INT_MAX;
        return a;
    }

    if(b==e )
    {
        Tree[nodeNumber].maxVal = arr[b];
        Tree[nodeNumber].minVal = arr[b];
        return Tree[nodeNumber];
    }

    int left = nodeNumber * 2 + 1;
    int right = nodeNumber* 2 + 2;
    int mid = (b + e )/2;

    Tree[left] = makeTree(b, mid,  left);
    Tree[right] = makeTree( mid + 1, e, right);

    Tree[nodeNumber].maxVal = max( Tree[left].maxVal , Tree[right].maxVal);
    Tree[nodeNumber].minVal = min ( Tree[left].minVal, Tree[right].minVal);

    return Tree[nodeNumber];
}
  
TreeNode range_query( int i , int j , int b , int e , int nodeNumber)
{
    if( b>= i && j>=e){
        //relevant node. take it.
        return Tree[nodeNumber];
    }
 
    if( b> j || e < i || b > e)
    {
        TreeNode a;
        a.maxVal = -500;
        a.minVal =  INT_MAX;
        return a;
    }
 
    int mid = (b + e )/2;
 
    int left= nodeNumber * 2 + 1;
    int right = nodeNumber * 2 + 2;
 
 
    TreeNode leftVal = range_query(i, j , b, mid, left);
    TreeNode rightVal = range_query(i, j , mid+1, e, right);
 
    TreeNode temp;
    temp.maxVal = max( leftVal.maxVal, rightVal.maxVal );
    temp.minVal = min( leftVal.minVal, rightVal.minVal);
 
    return temp; 
}
 
void init()
{
    memset(arr, 0, sizeof(arr));
 
        TreeNode a;
        a.maxVal = -500;
        a.minVal =  INT_MAX;
 
    for(int i=0 ; i < 3 * MAX; i++)
    {
        Tree[i] = a;
    }
}
 
int main(void)
{
    int testCase , caseno;
    caseno = 0;
 
    scanf("%d", &testCase);
 
    while(testCase--)
    {
        init();
        vector<int> sort_this;
 
        int n , d;
        scanf("%d %d", &n, &d);
 
        for(int i=0; i<n; i++)
        {
            int temp;
            scanf("%d", &arr[i]);
        }
 
         TreeNode test = makeTree( 0 , n-1, 0);
 
         int max_diff = -1;
 
        for(int i=0; i<n -d + 1 ; i++)
        {
            TreeNode  temp = range_query( i, i + d-1, 0, n-1, 0);

            if( temp.maxVal - temp.minVal > max_diff)
            {
                max_diff = temp.maxVal - temp.minVal;
            }
        }
 
        printf("Case %d: %d\n", ++caseno, max_diff);
    }
 
    return 0;
}
 