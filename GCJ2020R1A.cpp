#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <deque>
#define N 52
using namespace std;
typedef long long ll;
int t, n;
vector<string> p;
string getmid(string& s) {
	int i = 0;
	while(i < s.size() && s[i] != '*') i++;
	while(i < s.size() && s[i] == '*') i++;
	int j = s.size()-1;
	while(j >= 0 && s[j] != '*') j--;
	while(j >= 0 && s[j] == '*') j--;
	string res= "";
	for (int k = i; k <= j; ++k) {
		if (s[k] != '*') res.push_back(s[k]);
	}
	return res;
}
int main() {
	cin>>t;
	for (int cas = 1; cas <= t; ++cas) {
		cin>>n;
		p.clear();
		for (int i = 0; i < n; ++i) {
			string s;
			cin>>s;
			p.push_back(s);
		}
		vector<string> suf;
		vector<string> pre;
		pre.clear();
		suf.clear();
		for (int i = 0; i < n; ++i) {
			if (p[i][0] != '*') {
				string tmp="";
				for (int j = 0; j < p[i].size(); ++j) {
					if (p[i][j] != '*') tmp.push_back(p[i][j]);
					else break;
				}
				reverse(tmp.begin(), tmp.end());
				pre.push_back(tmp);
			}
			if (p[i].back() != '*') {
				string tmp="";
				for (int j = p[i].size()-1; j >= 0; --j) {
					if (p[i][j] != '*') tmp.push_back(p[i][j]);
					else break;
				}
				reverse(tmp.begin(), tmp.end());
				suf.push_back(tmp);
			}
		}
		string s2 = "";
		string s1 = "";
		bool ok = true;
		while(true) {
			int id = -1;
			for (int i = 0; i < suf.size(); ++i) {
				if (suf[i].empty()) continue;
				if (id < 0) id = i;
				else if (suf[i].back() != suf[id].back()) {
					ok = false;
					break;
				}
			}
			if (!ok) break;
			if (id < 0) break;
			s2.push_back(suf[id].back());
			for (int i = 0; i < suf.size(); ++i) {
				if (!suf[i].empty()) suf[i].pop_back();
			}
		}
		if (!ok) {
			cout<<"Case #"<<cas<<": "<<"*"<<endl;
			continue;
		}
		reverse(s2.begin(), s2.end());

        ok = true;
		while(true) {
			int id = -1;
			
			for (int i = 0; i < pre.size(); ++i) {
				if (pre[i].empty()) continue;
				if (id < 0) id = i;
				else if (pre[i].back() != pre[id].back()) {
					ok = false;
					break;
				}
			}
			if (!ok) break;
			if (id < 0) break;
			s1.push_back(pre[id].back());
			for (int i = 0; i < pre.size(); ++i) {
				if (!pre[i].empty()) pre[i].pop_back();
			}
		}
		if (!ok) {
			cout<<"Case #"<<cas<<": "<<"*"<<endl;
			continue;
		}
		string mid = "";
		for (int i = 0; i < n; ++i) {
			mid += getmid(p[i]);
		}
		string ans=s1+mid+s2;
		if (ans.size() > 10000) {
			cout<<"Case #"<<cas<<": "<<"*"<<endl;
		} else {
			cout<<"Case #"<<cas<<": "<<ans<<endl;
		}
	}
	return 0;
}
