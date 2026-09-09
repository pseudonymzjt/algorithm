/*
 * predict blocks of text inserted by "[" and "]"
 */
#include <cstdio>
#include <cstring>
const int maxn = 100000 + 5;
int last, cur, next[maxn]; // cursor after cur
char s[maxn];

int main() {
	while(scanf("%s", s + 1) == 1) {
		int n = strlen(s + 1);
		last = cur = 0;
		next[0] = 0;

		for(int i = 1; i <= n; i++) {
			char ch = s[i];
			if(ch == '[') cur = 0;
			else if(ch == ']') cur = last;
			else {
				next[i] = next[cur];
				next[cur] = i;
				if(cur == last) last = i; // update the id of last char
				cur = i;
			}
		}
		for(int i = next[0]; i != 0; i = next[i])
			printf("%c", s[i]);
		printf("\n");
	}
	return 0;
}
