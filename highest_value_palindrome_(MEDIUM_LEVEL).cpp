/*
author       : Mayuresh Rajesh Dindorkar
problem link : https://www.hackerrank.com/challenges/richie-rich/problem
level 		 : medium
*/

#include <bits/stdc++.h>
using namespace std;
int main(){
    ios_base::sync_with_stdio(0); 
    int n, k; cin >> n >> k; 
    string x; cin >> x; 
    string y = x; 
    for (int g=0; g<(x.length() + 1) / 2; g++){
        if (x[g] == x[x.length() - 1 - g]) continue; 
        char t = max (x[g], x[x.length() - 1 - g]); 
        y[g] = t; 
        y[x.length() - 1 - g] = t; 
        k--; 
    }
    if (k < 0){
        cout << -1; return 0; 
    }
    for (int g=0; g<(x.length() + 1) / 2; g++){
        if (y[g] == '9') continue; 
        int ne = 2; 
        if (x[g] != x[x.length() - 1 - g]) ne = 1; 
        if ((x.length() & 1) && g == (x.length() / 2)) ne = 1; 
        if (ne <= k){
            y[g] = '9'; 
            y[x.length() - 1 - g] = '9'; 
            k-=ne; 
        }
    }
    cout << y << '\n';
    return 0; 
}