#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<map>
#include<queue>
using namespace std;
#define MAX 20
#define INVALID 3
#define VALID 1
#define VISITED 1
 
int f_x[]={+1,0,0,-1};
int f_y[]={+0,-1,+1,0};
 
bool adj_mat[MAX][MAX];
bool visited[MAX][MAX];
 
class point
{
	public:
		int x,y;
		bool operator!=(point);
		bool operator==(point);
};
 
bool point::operator!=(point temp)
{
	if(temp.x!=x || temp.y!=y)
		return true;
	else
		return false;
}
 
bool point::operator==(point temp)
{
	if(temp.x==x || temp.y==y)
		return true;
	else
		return false;
}
 
int bfs(point source,int W,int H)
{
	memset(visited,0,sizeof(visited));

	int counter=1;
	queue<point>Q;

	visited[source.x][source.y]=VISITED;
	Q.push(source);

	while(!Q.empty())
	{
		source=Q.front();
		Q.pop();

		for(int i=0;i<4;i++)
		{
			point temp;
			temp.x=source.x+f_x[i];
			temp.y=source.y + f_y[i];

			if(temp.x>=0 && temp.y>=0 && temp.x<W && temp.y <H)
			{
				if(visited[temp.x][temp.y] != VISITED && adj_mat[temp.x][temp.y]==1)
				{
				  visited[temp.x][temp.y]=VISITED;
				  Q.push(temp);
				  counter++;
				}
			}
		}
	}

	return counter;
}
  
int main(void)
{
    //std::ios::sync_with_stdio(false);
    int testcase,caseno;
    caseno=0;
    scanf("%d",&testcase);
 
    while(testcase--)
	{
		memset(adj_mat,0,sizeof(adj_mat));

		int W,H;
		scanf("%d %d\n",&W,&H);

		int x=0;
		int y=0;

		point source;
		char ch;

		for(int i=0;i<W*H;i++)
	    {
		   scanf("%c\n",&ch);

		   if(x==W)
		   {
				x=0;
				y++;
			}

			if(ch =='.')
			{
				adj_mat[y][x++]=1;
			}
			else if(ch=='#')
			{
				adj_mat[y][x++]=0;
			}
			else if(ch=='@')
			{
				source.x=y;
				source.y=x;
				adj_mat[y][x++]=5;
			}
		}

		int result=bfs(source,H,W);
		printf("Case %d: %d\n",++caseno,result);

	}	

    return 0;
}