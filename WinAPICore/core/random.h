#pragma once
#include <random>

namespace yjj {
	// 엔진 사용해 시드값 생성
	std::random_device rd;
	std::mt19937_64 gen(rd());


	// 추후 템플릿 이용

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