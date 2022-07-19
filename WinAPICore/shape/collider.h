#pragma once
#include "../core/core.h"
#include "circle.h"
#include "rect.h"

namespace yjj {
	enum class collide_type {
		none,
		intersect,
		contain
	};

	class collider {
	public:
		// 충돌
		// cf) intersect, contain: 왼쪽 매개변수가 오른쪽 매개변수를 충돌, 포함할 경우

		// 점 vs 선
		const collide_type intersect(const vec2f& begin, const vec2f& end, const vec2f& pt);
		// 점 vs 사각형
		const collide_type intersect(const rectf& rectf, const vec2f& pt);
		// 점 vs 원형
		const collide_type intersect(const circlef& Ellipse, const vec2f& pt);
		// 선 vs 선 1. 외적 벡터 이용 방법
		const int comparator(const vec2f& l, const vec2f& r);
		void swap(vec2f& l, vec2f& r);
		const collide_type intersect_with_vector(vec2f& begin1, vec2f& end1, vec2f& begin2, vec2f& end2);
		// 선 vs 선 2.1. 방정식 pt대입 버전 
		const collide_type intersect(const vec2f& begin1, const vec2f& end1, const vec2f& begin2, const vec2f& end2, vec2f& out_pt);
		// 선 vs 선. 2.2. 방정식 pt대입 버전 활용
		const collide_type intersect(const vec2f& begin1, const vec2f& end1, const vec2f& begin2, const vec2f& end2);

		// 선 vs 사각형 (사각형이 선을 포함하는가)
		const collide_type intersect(const rectf& rectf, const vec2f& begin, const vec2f& end);
		// 선 vs 원형 (원형이 선을 포함하는가)
		const collide_type intersect(const circlef& Ellipse, vec2f& begin, vec2f& end);
		// const collide_type intersect2(const circlef& Ellipse, const vec2f& begin, const vec2f& end);
		// 사각형 vs 사각형
		const collide_type intersect(const rectf& rectf1, const rectf& rectf2);
		// 원형 vs 원형
		const collide_type intersect(const circlef& Ellipse1, const circlef& Ellipse2);
		// 사각형 vs 원형
		const collide_type intersect(const rectf& rectf, const circlef& Ellipse);
		// 원형 vs 사각형
		const collide_type intersect(const circlef& Ellipse, const rectf& rectf);
	};
}