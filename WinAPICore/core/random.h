#pragma once
#include <random>

namespace yjj {
	// ���� ����� �õ尪 ����
	std::random_device rd;
	std::mt19937_64 gen(rd());


	// ���� ���ø� �̿�

	template<typename T>
	T rand_int(T n1, T n2) {
		std::uniform_int_distribution<int> dist(n1, n2);
		return dist(gen);
	}

	template<typename T>
	T rand_float(T n1, T n2) {
		std::uniform_real_distribution<float> dist(n1, n2);
		return dist(gen);
	}
}