//그대로 출력하기 1
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
using namespace std;

int main() {
	char c[101];
	while (scanf("%[^\n]s", c) != EOF) {	//%[^\n]s 있어야 공백을 출력할 때 엔터로 안 띄움
		printf("%s\n", c);
		getchar();
		//while (getchar() != '\n') {}
	}
	return 0;
}

//그대로 출력하기 2
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

int main() {
	string s;
	while (!cin.eof()) {
		getline(cin, s);
		cout << s << endl;
	}
	return 0;
}