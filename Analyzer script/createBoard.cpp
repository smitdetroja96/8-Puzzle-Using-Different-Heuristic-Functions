#include <bits/stdc++.h>
#include <time.h>
using namespace std;

#define ll long long
#define ld long double
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define FOR(i,a,b) for(ll i = a ; i < b ; i++)

const ll n = 3;

typedef vector<vector<ll> > board;
board test_board(n,vector<ll> (n));

int main(int argc, char *argv[])
{
    srand(time(NULL));

    FOR(i,0,n)
    FOR(j,0,n)
    {
        if(i==n-1 && j==n-1)
            test_board[i][j]=0;
        else
            test_board[i][j]=i*n+j+1;
    }    

    board temp = test_board;
    FOR(i,0,100)
    {
        ll x1 = rand()%3;
        ll y1 = rand()%3;
        ll x2 = rand()%3;
        ll y2 = rand()%3;

        swap(temp[x1][y1],temp[x2][y2]);
    }

    FOR(i,0,3)
    {
        FOR(j,0,3)
        cout<<temp[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;

    freopen("input.txt","w",stdout); 
    FOR(i,0,3)
    {
        FOR(j,0,3)
        cout<<temp[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;
}
