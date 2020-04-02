/*
author       : Mayuresh Rajesh Dindorkar
problem link : https://www.hackerrank.com/challenges/build-a-string/problem
level 		 : complex
*/

#include<bits/stdc++.h>

using namespace std;

#define MAXN 30010
#define MAXLG 20
#define INF 1000000009


struct entry
{
    int nr[2];
    int p;
} L[MAXN];

int P[MAXLG][MAXN];
int N,i;
int stp, cnt,ar[MAXN],comp[MAXN];

int cmp(entry a, entry b)
{
    if (a.nr[0]!=b.nr[0]) return a.nr[0]<b.nr[0];
    else return a.nr[1]<b.nr[1];
}

int FindLCP (int x,int y)
{
    int ans = 0 , k=0 , tmp=cnt;
    for (k=stp-1;k>= 0;k--,tmp>>=1)
    {
        if (x+tmp <= N && y+tmp <= N && P[k][x] == P[k][y])
        {// sort-index is same if the first k characters are same
            ans += tmp;
            // now we wish to find the characters that are same in the remaining strings
            x += tmp;
            y += tmp;
		}
	}
	return ans;
}

int bin1(int a,int b,int x, int val)
{
    if(a==b) return a;
    int mid = (a+b+1)/2;
    if(FindLCP(L[mid].p,x) >= val)
    {
        return bin1(mid,b,x,val);
    }
    else return bin1(a,mid-1,x,val);
}

int bin2(int a,int b,int x, int val)
{
    if(a==b) return a;
    int mid = (a+b)/2;
    if(FindLCP(L[mid].p,x) >= val)
    {
        return bin2(a,mid,x,val);
    }
    else return bin2(mid+1,b,x,val);
}

#define LN 20

int mn[MAXN][LN],dp[MAXN],br[MAXN];

int rmq(int a,int b)
{
    int len = b-a+1,ans = mn[a][0],j=0;
    while(len > 0)
    {
        if(len&1)
        {
            ans = min(ans,mn[a][j]);
            a+= (1<<j);
        }
        len>>=1;
        j++;
    }
    return ans;
}

void solve()
{
    string s;
    int n,a,b;
    cin>>n>>a>>b;
    cin>>s;
    N=s.length();
    for(int i=0;i<N;i++)P[0][i] = s[i];
    for(stp=1, cnt = 1; cnt < N; stp++, cnt *= 2)
    {
        for(i=0; i < N; i++)
        {
            L[i].nr[0]=P[stp- 1][i];
            L[i].nr[1]=i +cnt <N? P[stp -1][i+ cnt]:-1;
            L[i].p= i;
        }
        sort(L, L+N, cmp);
        for(i=0; i < N; i++)
            P[stp][L[i].p] =(((i> 0) && (L[i].nr[0]==L[i-1].nr[0]) && (L[i].nr[1] == L[i- 1].nr[1])) ? P[stp][L[i-1].p] : i);
    }
    for(int i=0;i<N-1;i++)
    {
		ar[i]=FindLCP(L[i].p,L[i+1].p);
		//cout<<i<<" "<<L[i].p<<" "<<L[i+1].p<<" "<<ar[i]<<endl;
    }

    for(int i=0;i<n;i++)
    {
        mn[i][0] = L[i].p;
        br[L[i].p] = i;
    }

    for(int j = 1;j<LN;j++)
    {
        for(int i=0;i + (1<<j)<=n;i++)
        {
            mn[i][j] = min(mn[i][j-1], mn[i+(1<<(j-1))][j-1]);
        }
    }

    dp[0] = 0;
    for(int i=1;i<=n;i++)
    {
        //cout<<L[i-1].p<<endl;
        //cout<<br[i-1]<<endl;
        dp[i] = INF;
    }
    int j = 0,x,y,tmp;
    for(int i=1;i<=n;i++)
    {
        dp[i] = min(dp[i], dp[i-1] + a);
        if(i<=j)continue;
        x = bin2(0,br[j],j,i-j);
        y = bin1(br[j],n-1,j,i-j);
        tmp = rmq(x,y);
        //cout<<x<<y<<" "<<br[j]<<endl;
        //cout<<i<<" "<<j<<" "<<tmp<<" "<<dp[i]<<endl;
        if(tmp+i-j <= j)
        {
            dp[i] = min(dp[i],dp[j] + b);

        //cout<<i<<" "<<j<<" "<<tmp<<" "<<dp[i]<<endl;
        }
        else
        {
            j++;
            i--;
        }
    }
    cout<<dp[n]<<endl;
}
int main()
{
	int t=1,tmp,last;
	scanf("%d",&t);
	while(t--)
	{
		solve();
	}
}