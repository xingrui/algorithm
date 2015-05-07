//http://acm.hust.edu.cn/problem/show/1004
# include<stdio.h>
# include<string.h>
# include<stdlib.h>
#include<iostream>
#include<algorithm>

using namespace std;
# define inf  11519
struct node{
    char a[50];
}s[50005];
bool cmp(node a1,node b1)
{
    return strcmp(a1.a,b1.a)<0;
}
int main()
{
    int T,ans,n,i,j,k,len;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(i=0;i<n;i++) scanf("%s",s[i].a);
        sort(s,s+n,cmp);
        ans=0;
        for(i=0;i<n-1;i++)
        {
            len = strlen(s[i].a);
            for(j=i+1;j<n;j++)
            {
                for(k=0;k<len;k++)
                {
                    if(s[i].a[k]==s[j].a[k]);
                    else break;
                }
                if(k<len) break;
                else ans++;
            }
        }
        if(ans>inf) ans=ans%inf;
        printf("%d\n",ans);
    }
    return 0;
}
