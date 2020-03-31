// Brijesh Panara (201601074)
// DAIICT (India)
#include <bits/stdc++.h>
#include <time.h>
using namespace std;

#define ll long long
#define ld long double
#define pb push_back
#define mp make_pair
#define ff first
#define ss second

#define precision(x,d) cout<<fixed<<setprecision(d)<<x
#define minQueue priority_queue<ll,vector<ll>,greater<ll> > 
#define maxQueue priority_queue<ll,vector<ll>,less<ll> > 

#define FOR(i,a,b) for(ll i=a;i<b;i++)
#define RFOR(i,a,b) for(ll i=a;i>b;i--)
#define FILL(a,b) memset((a),(b),sizeof((a)))

#define deb1(x) cout<<#x<<" : "<<x<<endl;
#define deb2(x,y) cout<<#x<<" : "<<x<<"\t"<<#y<<" : "<<y<<endl;
#define deb3(x,y,z) cout<<#x<<" : "<<x<<"\t"<<#y<<" : "<<y<<"\t"<<#z<<" : "<<z<<endl;

#define MOD 1000000007
#define INF LONG_LONG_MAX
#define MINF LONG_LONG_MIN

void FAST()
{
    ios_base::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    //srand(time(NULL));
    freopen("output.txt","r",stdin);
    //freopen("output.txt","w",stdout);    
}

int main()
{
    FAST();

    ll n = 3;
    ll q = 4;

    ld steps[4]={0};
    ld iterations[4]={0};
    ld time[4]={0};
    ld cnt = 0;

    float temp;
    while(scanf("%f",&temp)==true)
    {

    	FOR(i,0,n)
    	FOR(j,0,n)
    	{
    		if(i==n-1 && j==n-1)
    			break;
    		else
    			scanf("%f",&temp);
    	}

    	bool flag = true;
    	FOR(i,0,q)
    	{
	    	char str[50];
    		scanf("%s",str);
			//printf("%s !!!\n",str);
    			
    		FOR(j,0,3)
    		{
    			scanf("%s",str);
    			//printf("%s\n",str);
    			scanf("%s",str);
	    		//printf("%s\n",str);
    			scanf("%f",&temp);
				//printf("%f\n",temp);
				if(j==2)
				{
					scanf("%s",str);
	    			//printf("%s\n",str);
				}

				if(temp==-1)
					flag = false;

    			if(j==0 && flag)
					steps[i]+=temp;
				else if(j==1 && flag)
					iterations[i]+=temp;
				else if(flag)
					time[i]+=temp;
    		}
    	}

		if(flag)
    		cnt++;
    }
    printf("Euclidean\n");
    deb3(steps[0],iterations[0],time[0]);
    printf("Manhattan\n");
    deb3(steps[1],iterations[1],time[1]);
    printf("Hamming\n");
    deb3(steps[2],iterations[2],time[2]);
    printf("Inversion\n");
    deb3(steps[3],iterations[3],time[3]);
    printf("Observations\n");
    deb1(cnt);
    return 0;
}

struct Query
{
    ll L,R,idx;
};
 
bool compare(ll a0, ll a1)
{
    return (a0>a1);
}

//returns (x^(y))%p
ll power(ll x, ll y, ll p)
{
    ll ans = 1;  
    x = x % p;  
    while (y > 0)
    {
        if(y & 1)
            ans = (ans*x) % p;
        y = y>>1;
        x = (x*x) % p;  
    }
    return ans;
}

//store gcd of a,b in g
//store solution of a*x + b*y = g in x,y
// if gcd(a,b)=1 then x = a^(-1)(mod b) and y = b^(-1)(mod a)
ll x,y,g;
void extendedEuclid(ll a, ll b)
{
    if(b==0)
    {
        g = a;x = 1;y = 0;
    }
    else
    {
        extendedEuclid(b,a%b);
        ll temp = x;
        x = y;
        y = temp-(a/b)*y;
    }
}

// return modulo inverse of a wrt modulo p
// retunt -1 if modulo inverse does not exist
ll moduloInverse(ll a, ll p)
{
    extendedEuclid(a,p);
    if(g==1 && p!=1)
        return (x+p)%p;
    else
        return -1;
}