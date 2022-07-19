#include <iostream>
#include <algorithm>
using namespace std;

int gcd(int a, int b) {
    if (a < b) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    while (b != 0) {
        int n = a % b;
        a = b;
        b = n;
    }
    return a;
}
long long solution(int w, int h) {
    long long answer = 1;
    long long ret;
    /*
    if (w == 1 || h == 1) {
        return 0;
    }
    ret = max(w, h) / min(w, h);
    if (max(w, h) % min(w, h) != 0) {
        ret++;
    }*/
    //Ǯ�� ���� ǰ.
    /*
    �켱 w�� h�� ������� �ִٸ� ������ ������� ���� w' �� h'�� ��ҽ�ų���ֽ��ϴ�.
    w'�� h'�� ���μҶ� ���������� �밢���� �ݴ��� �ڳʿ� �����ϱ��� w'-1 ���μ��� h' - 1 ���μ��� ������
    ���������� ���ο� ���簢���� �߰��˴ϴ�.
    �׷��� ù ���簢���� ���� 1 + (w'-1) + (h' - 1) = w' + h' - 1���� ���簢���� ������ �ǹǷ�
    ������� �ٽ� �����ָ� w + h - gcd(w, h)���� ���簢���� �����°��� ã�����ֽ��ϴ�.
    */
    ret = w + h - gcd(w, h);
    answer = w * h - ret;
    return answer;
}
void main() {
    printf("%d", solution(8, 12));
}