using namespace std;

long long solution(int price, int money, int count) {
    long long answer = -1;
    long long sum = (static_cast<long long>(count) * (price + price * count)) / 2;    //�������� �� ����
    answer = money - sum;
    if (answer > 0) {
        answer = 0;
    }
    return -answer;
}