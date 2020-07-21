#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;
const int maxn = 100;
int map[maxn][maxn];
int dis[maxn];
int path[maxn];
int vis[maxn];
int n;
void dijk(int s)
{
    memset(path,-1,sizeof(path));
    
    memset(dis,0x3f,sizeof(dis));
    memset(vis,0,sizeof(vis));
    dis[s] = 0; 
    while(1)
    {
        int k = 0;
        for(int j = 1; j <= n; j++)
        {
            if(!vis[j]&&dis[j]<dis[k])
                k=j; 
        }
        if(!k) return; 
        vis[k] = 1;
      
        for(int j = 1; j <= n; j++)
        {
            if(dis[j]>dis[k]+map[k][j])
            {
                dis[j]=dis[k]+map[k][j];
                path[j]=k;
            }
        }
    }
}

void print(int x)
{
    if(x == -1) return;
    
    print(path[x]);
    printf("%d->",x);
}
int main()
{
    int m,x,y,z,order;
    scanf("%d%d",&n,&m);
    memset(map,0x3f,sizeof(map));
    for(int i = 0; i < m; i++)
    {
        scanf("%d%d%d",&x,&y,&z);
        map[x][y] = z;
    }
    dijk(1);
    scanf("%d",&order);
    print(path[order]);
    printf("%d\n",order);
    
    printf("%d\n",dis[order]);
    return 0;
}

