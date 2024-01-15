//Challenge: Accepted
#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <random>
#include "meetings.h"
#define ll long long
#define maxn 3005
#define pii pair<int, int>
#define ff first
#define ss second
#define io ios_base::sync_with_stdio(0);cin.tie(0);
using namespace std;
 
int tot;
vector<pii> ans;
 
vector<int> adj[maxn], sub[maxn];
bool found[maxn];
void dfs(int n, vector<int> &add) {
	found[n] = 1;
	add.push_back(n);
	for (int v:adj[n]) {
		if (!found[v]) {
			dfs(v, add);
		}
	}
}
 
int getcon(int root, vector<int> v) {
	if (v.size() == 1) return v[0];
	int ret = Query(root, v[0], v[1]);
	for (int i = 2;i < v.size();i++) {
		if (ret != v[i]) ret = Query(root, ret, v[i]);
	}
	return ret;
}
 
int curroot;
inline bool cmp(int x, int y) {
	return Query(curroot, x, y) == x;
}
 
void solve(int root, vector<int> v) {
	if (v.size() == 0) return;
	if (v.size() == 1) {
		ans.push_back(make_pair(root, v[0]));
		return;
	}
	v.push_back(root);
	random_shuffle(v.begin(), v.end());
	for (int i = 0;i < v.size();i++) found[v[i]] = 0;
	sub[root].clear();
 
	vector<int> path;
	root = v[0];
	path.push_back(v[1]);
	found[root] = found[v[1]] = 1;
	int x = v[1];
	sub[x].clear();
	for (int i = 2;i < v.size();i++) {
		int val = Query(root, x, v[i]);
		if (val == x) {
			if (!found[v[i]]) {
				path.push_back(v[i]);
				found[v[i]] = 1;
				sub[v[i]].clear();
			}
			x = v[i];
		} else {
			if (!found[val]) {
				path.push_back(val);
				found[val] = 1;
				sub[val].clear();
			}
			if (val != v[i]) {
				sub[val].push_back(v[i]);
			}
		}
	}
	//finds a path from root to leaf and splits other nodes (vs - 1 queries)
	curroot = root;
	sort(path.begin(), path.end(), cmp);
	for (int i = 0;i < path.size();i++) {
		ans.push_back(i ? make_pair(path[i], path[i - 1]) : make_pair(path[i], root));
	}
	//cout << endl;
	path.push_back(root);
	for (int i = 0;i < path.size();i++) {
		solve(path[i], sub[path[i]]);
	}
}
 
void Solve(int N) {
	srand(time(NULL));
	ans.clear();
	tot = N;
	vector<int> v;
	for (int i = 1;i < tot;i++) v.push_back(i);
	solve(0, v);
	for (auto i:ans) {
		if (i.ff > i.ss) swap(i.ff, i.ss);
		//cout << i.ff << "  " << i.ss << endl;
		Bridge(i.ff, i.ss);
	}
}
