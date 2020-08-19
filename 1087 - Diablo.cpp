#include<bits/stdc++.h>
using namespace std;
 
#define max_val  100000 + 50000 + 5
 
bool position[max_val];
int segment_tree[5 * max_val];
int ids[max_val];
 
void init()
{
    memset(position, 0, sizeof(position));
    memset(segment_tree, 0, sizeof(segment_tree));
    memset(ids, 0, sizeof(ids)); 
}
 
 
int make_tree(int L , int R, int node)
{ 
    if(L > R || L<0)
        return 0;
    else if(L == R)
    {
        return (int)position[L];
    }

    int left = node *  2 + 1;
    int right= node* 2 + 2;
    int mid = (L + R )/ 2;
 
    segment_tree[left] = make_tree(L, mid, left);
    segment_tree[right] = make_tree(mid+1 , R, right);
    segment_tree[node] = segment_tree[left] + segment_tree[right];
 
    return segment_tree[node]; 
}
 
//now I want to query the index of the element.
 
int find_index(int K , int L , int R , int node)
{ 
    if(L == R)
    {
        if(segment_tree[node]==1)
            return L;
        else
            return -1;
    }
 
    int left = node  * 2 + 1;
    int right= node  * 2 + 2;
 
    int mid = ( L + R )/2;
 
    if(segment_tree[left]  >= K)
    {
        return find_index(K, L, mid, left);
    }

    else if( K - segment_tree[left] > segment_tree[right])
    {
         return -1;
    }
 
    return find_index(K - segment_tree[left] , mid+1, R, right );   
}   
 
void update(int current_index, int L , int R, int node,  int newValue)
{
    if( L> current_index || current_index > R)
        return;
 
    if(L == R && L == current_index)
    {
        position[current_index] = newValue;
        segment_tree[node] = newValue;
        return;
    }
 
    int mid = ( L + R ) / 2;
    int left =  node * 2 + 1;
    int right=  node * 2 + 2;
 
    update(current_index, L, mid,left, newValue);
    update(current_index, mid+1, R, right, newValue);
    segment_tree[node] = segment_tree[left] + segment_tree[right];
}
 
 
int range_query_normal(int i, int j, int b, int e, int node)
{
    if(b>= j || e<=i)
        return 0;
 
    if(b>=i && e>=j)
    {
        return segment_tree[node];
    }
 
    int mid = (b+e)/2;
    int left= node * 2 + 1;
    int right= node*2 + 2;
 
    int left_sum = range_query_normal(i,j,b,mid,left);
    int right_sum = range_query_normal(i,j,mid+1, e, right);
 
    return left_sum+ right_sum;
}
 
 
int main(void)
{
   // ios_base::sync_with_stdio(false);
   // for(int i=0; i< 100; i++)
   //   position[i] = 1;

   //make_tree(0 , 99, 0);
   //update(0, 0, 99, 0, 0);
   //update(1, 0, 99, 0, 0);
   
    //cout<< range_query_normal(0,99,0,99,0)<<endl;
    //cout<< find_index(5, 0, 99, 0 ) <<endl;

    int testCase, caseNo,N,Q ;
    caseNo=0;
    scanf("%d",&testCase); 
  
    while(testCase--)
    {
		int current_limit = 0;
        init();
        scanf("%d %d",&N, &Q);
        current_limit+=N-1;
 
        for(int i=0; i<N;i++){
            int id;
          //cin>>id;
            scanf("%d",&id);
            position[i]=1;
            ids[i]= id;
        }

		make_tree(0, max_val, 0);	  
		printf("Case %d:\n",++caseNo);

		for(int i=0;i<Q;i++){
	 
			char c;
			int k;
			scanf(" %c %d",&c, &k);
	 
			if(c=='c')
            {
				//remove and show id.
				int index = find_index(k, 0, max_val, 0);

				if(index == -1)
                {
					printf("none\n");
				}	 
				else
                { 
					printf("%d\n",ids[index]);
				}

				update(index, 0, max_val, 0, 0);
			}
	 
			else
            {	 
				current_limit+=1;
				ids[current_limit]=k;
				update(current_limit, 0, max_val, 0, 1);	 
			}
		}
    }
 
    return 0;
}