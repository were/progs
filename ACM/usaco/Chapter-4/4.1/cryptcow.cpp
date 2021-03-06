/*
PROG : cryptcow
ID : weng_xo2
LANG : C++11
*/
//============================================================================
// Name        : cryptcow.cpp
// Author      : were
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cctype>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

using std::vector;

const char Goal[] = "Begin the Escape execution at the Break of Dawn";
const int Mod = 999983;

char s[100];
int ans, cnt;
bool flag, hsh[Mod];

void work(int a, int b, int c) {
//	puts(s);
	static char tmp[100];
	int len = strlen(s), tot = 0;
	for(int i = 0; i < a; ++i) {
		tmp[tot++] = s[i];
	}
	for(int i = b + 1; i < c; ++i) {
		tmp[tot++] = s[i];
	}
	for(int i = a + 1; i < b; ++i) {
		tmp[tot++] = s[i];
	}
	for(int i = c + 1; i < len; ++i) {
		tmp[tot++] = s[i];
	}
	tmp[tot] = 0;
	strcpy(s, tmp);
}

int getHash() {
	int ret = 0, len = strlen(s);
	for(int i = 0; i < len; ++i) {
		int num = 0;
		if(s[i] == ' ') {
			num = 1;
		}
		else {
			num = isupper(s[i]) ? s[i] - 'A' + 2 : s[i] - 'a' + 28;
		}
		ret = (ret * 57 + num) % Mod;
	}
	return ret;
}

void dfs(int depth) {
	if(strcmp(s, Goal) == 0) {
		ans = depth;
		flag = true;
		return;
	}
	int x = getHash();
	if(hsh[x]) {
		return;
	}
	hsh[x] = true;
	++cnt;
	char pre[100];
	static char sub[100];
	strcpy(pre, s);
	int len = strlen(s);
	int c[20], o[20], w[20];
	c[0] = o[0] = w[0] = 0;
	for(int i = 0, j = 0; i < len; ++i) {
		if(s[i] == 'C' || s[i] == 'O' || s[i] == 'W') {
			if(s[i] == 'C') {
				c[++c[0]] = i;
			}
			if(s[i] == 'O') {
				o[++o[0]] = i;
			}
			if(s[i] == 'W') {
				w[++w[0]] = i;
			}
			sub[j] = 0;
			if(!strstr(Goal, sub)) {
				return;
			}
			j = 0;
		}
		else {
			sub[j++] = s[i];
		}
	}
	if(o[0] != c[0] || o[0] != w[0] || w[0] != c[0]) {
		return;
	}
	for(int j = 1; j <= o[0]; ++j) {
		for(int k = w[0]; k >= 1 && w[k] > o[j]; --k) {
			for(int i = 1; i <= c[0] && c[i] < o[j]; ++i) {
				work(c[i], o[j], w[k]);
				dfs(depth + 1);
				if(flag || cnt > 200000) {
					return;
				}
				strcpy(s, pre);
			}
		}
	}
}


int main() {
	freopen("cryptcow.in", "r", stdin);
	freopen("cryptcow.out", "w", stdout);
	gets(s);
	dfs(0);
	printf("%d %d\n", flag ? 1 : 0, ans);
	return 0;
}
