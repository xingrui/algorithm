#include<cstdio>
#include<cstring>
#include<iostream>
#include<utility>
#include<string>
#include<set>
#include<vector>
#include<stack>
#include<algorithm>
#include<queue>
#include<cstdlib>
#include<map>
#include<cmath>
using namespace std;
#define FOR(i,a,b) for(int i(a);i<(b);i++)
#define REP(i,n) FOR(i,0,n)
#define CL(a,b) memset(a,b,sizeof(a))

const int M = 200;
const int N = 120;
//const __int64 inf=0x7fffffffffffffff;
const int inf = 1 << 29;
//const double inf=1e250;
const double eps = 1e-8;
const double pi = acos(-1.0);
const double sq2 = sqrt(2.0);
bool vis[M];
bool mp[M][M];
int result[M];
int n, m;

void init()
{
    for (int i = 0; i <= n + 3; i++) {
        result[i] = 0;

        for (int j = 0; j <= n + 3; j++)
            mp[i][j] = 0;
    }
}

bool find(int a)
{
    for (int i = 1; i <= n; i++) {
        if (mp[a][i] && !vis[i]) {
            vis[i] = 1;

            if (result[i] == 0 || find(result[i])) {
                result[i] = a;
                return true;
            }
        }
    }

    return false;
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d%d", &n, &m);
        init();

        while (m--) {
            int a, b;
            scanf("%d%d", &a, &b);
            mp[a][b] = 1;
        }

        int cnt = 0;

        for (int i = 1; i <= n; i++) {
            memset(vis, 0, sizeof(vis));

            if (find(i)) cnt++;
        }

        printf("%d\n", n - cnt);
    }

    return 0;
}
