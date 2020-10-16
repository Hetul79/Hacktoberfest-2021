#include <bits/stdc++.h>
 
using namespace std;
using nagai = long long;
 
nagai gcd(nagai a, nagai b) {
	if (a == 0) return b;
	if (b == 0) return a;
	return __gcd(a, b);
}
 
nagai lcm(nagai a, nagai b){
	return a / gcd(a, b) * b;
}
 
int main() {
	 cin.tie(0);
	 ios::sync_with_stdio(false);
	 int t;
	 cin >> t;
	 vector<bool>ispr(10005, true);
	 vector<nagai>pks;
	 for(int i=2;i<ispr.size();++i) {
		 if (!ispr[i])continue;
		 for(int j=2*i;j<ispr.size();j += i)
			 ispr[j]=false;
		 nagai pk=i;
		 while(pk<ispr.size())
			 pks.push_back(pk), pk*=i;
	 }
	 while(t--) {
		  int n; 
			cin >> n;
			vector<nagai>a(n);
			vector<nagai>b(n);
			for(auto&x:a)
				cin >> x;
			for(auto&x:b)
				cin >> x;
			if (count(a.begin(),a.end(),0) == n) {
				 cout << "YES\n";
				 continue;
			}
			b.insert(b.begin(), 0);
			vector<int>c(n);
			for(int i=0;i<n;++i)
				c[i] = a[(i+1)%n] - a[i];
			bool bad=false;
			for(int pk:pks) { 
				bool ok=false;
				for(int x:b) 
					if (x % pk == 0)ok=true;
				if (!ok)continue;
				nagai d = n;
				for(int i=1;i<=n;++i)
					if (b[i] % pk)
						d = gcd(d, i);
				for(int i=0;i<d;++i) {
					nagai s = 0;
					for(int j=i; j < n; j += d) 
						s += c[j];
					if (s % pk){
						bad=true;
					}
				}
			}
			nagai d1 = n;
			for(int i=1;i<=n;++i)
				if (b[i] != 0)
					d1=gcd(d1, i);
			for(int i=0;i<d1;++i) {
				nagai s = 0;
				for(int j=i; j < n; j += d1) 
					s += c[j];
				if (s != 0) {
					bad=true;
				}
			}
			nagai d=0;
			for(int i=1; i<=n;++i)
				d = gcd(d, b[i] * lcm(i, n) / n);
			if (d == 0) {
				cout << "NO\n";
				continue;
			}
			for(int p=2;p<=d;++p) {
				if (ispr[p] && d % p == 0) {
					nagai pt=1;
					while(n%(pt*p) == 0)pt *= p;
					nagai pk=1;
					while(d%(pk*p) == 0) pk *= p;
					for(int i=0;i<pt;++i) {
						nagai s =0;
						for(int j=i;j<n;j+=pt)
							s += a[j];
						if (s % pk)
							bad=true;
					}
				}
			}
			if (!bad)
				cout << "YES\n";
			else
				cout << "NO\n";
	 }
	 return 0;
}
