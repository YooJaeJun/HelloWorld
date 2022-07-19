#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			printf("*");
		}
		for (int j = 1; j <= (n - i) * 2; j++) {
			printf(" ");
		}
		for (int j = 1; j <= i; j++) {
			printf("*");
		}
		printf("\n");
	}
	for (int i = 1; i <= n - 1; i++) {
		for (int j = 1; j <= n - i; j++) {
			printf("*");
		}
		for (int j = 1; j <= i * 2; j++) {
			printf(" ");
		}
		for (int j = 1; j <= n - i; j++) {
			printf("*");
		}
		printf("\n");
	}
	return 0;
}



#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n - i; j++) {
			printf(" ");
		}
		if (i == 1) {
			printf("*");
		}
		else if (i != n) {
			printf("*");
			for (int j = 1; j <= (i - 2) * 2 + 1; j++) {
				printf(" ");
			}
			printf("*");
		}
		else {
			for (int j = 1; j <= n * 2 - 1; j++) {
				printf("*");
			}
		}
		printf("\n");
	}
	return 0;
}





#include <iostream>
#include <vector>
using namespace std;

void solution() {
	int n;
	cin >> n;

	for (int i = 0; i != n; i++) {
		for (int j = 0; j < i; j++) {
			cout << ' ';
		}
		for (int j = 2 * (n - i - 1) + 1; j > 0; j--) {
			cout << '*';
		}
		cout << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	solution();
	return 0;
}