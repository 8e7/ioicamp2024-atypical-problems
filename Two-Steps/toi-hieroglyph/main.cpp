//Challenge: Accepted
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
//#include "hieroglpyhs.h"
using namespace std;
#ifdef zisk
void debug(){cout << endl;}
template<class T, class ... U> void debug(T a, U ... b){cout << a << " ", debug(b...);}
template<class T> void pary(T l, T r) {
	while (l != r) cout << *l << " ", l++;
	cout << endl;
}
#else
#define debug(...) 0
#define pary(...) 0
#endif
#define ll unsigned long long
#define maxn 92
#define pii pair<int, int>
#define ff first
#define ss second
#define io ios_base::sync_with_stdio(0);cin.tie(0);
#define iter(v) v.begin(),v.end()
#define SZ(v) (int)v.size()
#define pb emplace_back
ll fib[maxn], cnt[maxn], tot[maxn];
void build() {
	fib[0] = fib[1] = 1;
	for (int i = 2;i < maxn;i++) fib[i] = fib[i-1] + fib[i-2];
	for (int i = 1;i < maxn-1;i++) cnt[i] = fib[i+1]; 
	for (int i = 1;i < maxn-1;i++) tot[i] = tot[i-1] + cnt[i];
	cnt[0] = 1;
}
string Alice(ll x) {
	build();
	string ret;	
	int len = 0;
	for (int i = 1;i < maxn;i++) {
		if (x < tot[i]) {
			len = i;
			break;
		}
	}
	x -= tot[len-1];
	//lexicographic x-th fib sequence of length len
	while (len > 0) {
		if (x < cnt[len-1]) {
			ret += 'W';
		   	len--;
		}
		else {
			x -= cnt[len-1];
			ret += 'B';
			if (len >= 2) ret += 'W';
			len -= 2;
		}
	}
	return ret;
}
ll Bob(string s) {
	build();
	ll ans = tot[(int)s.size() - 1];
	int len = s.size();
	for (int i = 0;i < len;i++) {
		if (s[i] == 'B') {
			ans += cnt[len-i-1];
			i++;
		}
	}
	return ans;
}
