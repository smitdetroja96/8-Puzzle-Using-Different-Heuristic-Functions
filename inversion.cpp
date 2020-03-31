#include <bits/stdc++.h>
using namespace std;

#define ll int
#define ld float
#define pb push_back
#define mp make_pair

#define FOR(i,a,b) for(ll i=a;i<b;i++)

#define board vector<vector<ll>>
#define pair_board pair<vector<vector<ll> > ,ll> 

const int n = 3;
ll iterations = 0;

map<board,bool> visited;
map<board,board> parent;
board end_board(n,vector<ll> (n));

ll dx[]={-1,+1,0,0};
ll dy[]={0,0,-1,+1};

//----------------- To find inversion of board ----------------//

ll inversion(board curr_board, ll moves)
{
    vector<int> arr(n*n);
    int cnt = 0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            arr[cnt++] = curr_board[i][j];
        }
    }
    int num = 0;
    for(int i=0;i<n*n-1;i++)
    {
        if(arr[i] != 0)
        for(int j=i+1;j<n*n;j++)
        {
            if(arr[j] != 0 && arr[j] < arr[i])
                num++;
        }
    }
    return num + moves;
}


bool isSolvable(board start)
{
    ll pos = 0;
    FOR(i,0,n)
    FOR(j,0,n)
    if(start[i][j]==0)
        pos = i+1;

    ll inv = inversion(start,0);

    if(n%2==1 && inv%2==0)
        return true;
    else if(n%2==0 && pos%2==inv%2)
        return true;

    return false;
}

//----------------- To find all possible neighbours of board ----------------//

bool isGood(ll i,ll j)
{
    if(i>=0 && i<n && j>=0 && j<n)
        return true;
    else
        return false;
}

vector<board> possible_neighbours(board curr_board)
{
    ll pos[2];
    FOR(i,0,n)
    FOR(j,0,n)
    {
        if(curr_board[i][j]==0)
        {
            pos[0]=i;
            pos[1]=j;
            break;
        }
    }

    vector<board> neighbour;
    FOR(i,0,4)
    {
        ll x = pos[0];
        ll y = pos[1];

        board temp = curr_board;
        if(isGood(x+dx[i],y+dy[i]))
        {
            swap(temp[x+dx[i]][y+dy[i]],temp[x][y]);
            neighbour.pb(temp);
        }
    }

    return neighbour;
}

//----------------- To find solution of board ----------------//

struct cmp
{
    bool operator() (pair_board &a, pair_board &b)
    {
        ld x = inversion(a.first,a.second);
        ld y = inversion(b.first,b.second);
        return x > y;
    }
};

void print_path(board curr_board)
{
    if(parent.count(curr_board))
        print_path(parent[curr_board]);

    FOR(i,0,n)
    {
        FOR(j,0,n)
        printf("%d ",curr_board[i][j]);
        printf("\n");
    }
    printf("\n");
}

ll solve(board start)
{
    if(isSolvable(start)==false)
        return -1;

    priority_queue<pair_board,vector<pair_board>,cmp> q;

    q.push(mp(start,0));
    
    while(!q.empty())
    {
        pair_board temp = q.top();
        q.pop();

        board curr_board = temp.first;
        ll curr_moves = temp.second;

        visited[curr_board]=true;
        if(curr_board == end_board)
        {
            print_path(curr_board);
            return curr_moves;
        }

        iterations++;
        vector<board> neighbour = possible_neighbours(curr_board);

        ll sz = neighbour.size();
        FOR(i,0,sz)
        {
            board temp = neighbour[i];
            if(visited[temp]==false)
            {
                parent[temp]=curr_board;
                q.push(mp(temp,curr_moves+1));
            }
        }
    }
    return -1;
}

int main()
{
    FOR(i,0,n)
    FOR(j,0,n)
    {
        if(i==n-1 && j==n-1)
            end_board[i][j]=0;
        else
            end_board[i][j]=n*i+j+1;
    }

    board curr_board(n,vector<ll> (n));
    FOR(i,0,n)
    FOR(j,0,n)
    cin>>curr_board[i][j];


    printf("Inversion\n");
    ll steps = solve(curr_board);
    printf("Steps      = %d\n",steps);
    printf("Iterations = %d\n",iterations);
    printf("Time       = %fs\n",static_cast<double>(clock())/(CLOCKS_PER_SEC));
    printf("\n");
}