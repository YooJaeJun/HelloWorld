#include <cmath>
#include <numeric>
#include "collider.h"
#include "../math/vec.h"
using namespace std;

namespace yjj {
	// 충돌
	// cf) intersect, contain: 왼쪽 매개변수가 오른쪽 매개변수를 충돌, 포함할 경우
		 
	// 점 vs 선
	const collide_type collider::intersect(const vec2f& begin, const vec2f& end, const vec2f& pt) {	//접점찾기.
		if (pt.x() >= begin.x() && pt.x() <= end.x()
			&& pt.y() >= begin.y() && pt.y() <= end.y()) {
			return collide_type::intersect;
		}
		return collide_type::none;
	}

	// 점 vs 사각형
	const collide_type collider::intersect(const rectf& rect, const vec2f& pt) {
		if ((pt.x() >= rect.left() && pt.x() <= rect.right())
			&& (pt.y() <= rect.bottom() && pt.y() >= rect.top())) {
			return collide_type::intersect;
		}
		return collide_type::none;
	}

	// 점 vs 원형
	const collide_type collider::intersect(const circlef& circle, const vec2f& pt) {
		if (circle.origin().distance_sq(pt) <= circle.radius() * circle.radius()) {
			return collide_type::intersect;
		}
		return collide_type::none;
	}

	// 선 vs 선 1. 외적 벡터 이용 방법
	const int collider::comparator(const vec2f& l, const vec2f& r) {
		//operator< > 함수 필요
		int ret;
		if (l.x() == r.x()) {
			ret = (l.y() <= r.y());
		}
		else {
			ret = (l.x() <= r.x());
		}
		return ret;
	}

	void collider::swap(vec2f& l, vec2f& r) {
		vec2f tmp = l;
		l = r;
		r = tmp;
	}

	const collide_type collider::intersect_with_vector(vec2f& begin1, vec2f& end1, vec2f& begin2, vec2f& end2) {
		//외적 양수 반시계, 외적 음수 시계, 외적 0 평행		==> 좌표계가 y()축반전이라 반대인듯
		//(x()1, y()1) 외적 (x()2, y()2) == (x()1*y()2) - (x()2*y()1).	
		//각 선분의 begin에서 다른 선분의 begin까지, end까지 외적이 하나는 양수, 하나는 음수로 나와야 함. 다른 선의 begin도 반복.

		//두 선분이 한 직선 위에 있거나, 끝점이 겹치는 경우
		float ccw1 = begin1.ccw(begin2) * begin1.ccw(end2);
		float ccw2 = begin2.ccw(begin1) * begin2.ccw(end1);
		if (ccw1 == 0 && ccw2 == 0) {
			//공식 참고. 원리 이해는 못함
			if (comparator(end1, begin1)) {
				swap(begin1, end1);
			}
			if (comparator(end2, begin2)) {
				swap(begin2, end2);
			}
			//포함
			if (comparator(begin2, end1) && comparator(begin1, end2)) {
				//완전 포함
				if (begin1.x() <= begin2.x() && begin1.y() <= begin2.y() && end1.x() >= end2.x() && end1.y() >= end2.y()) {	//operator < > 필요
					return collide_type::contain;	//포함된다고 정의
				}
				return collide_type::intersect;
			}
		}
		//중간점이 겹치는 경우
		else if (ccw1 <= 0 && ccw2 <= 0) {
			return collide_type::intersect;
		}
		return collide_type::none;
	}

	// 선 vs 선 2.1. 방정식 pt대입 버전 
	const collide_type collider::intersect(const vec2f& begin1, const vec2f& end1, const vec2f& begin2, const vec2f& end2, vec2f& out_pt) {
		float t;
		float s;
		//직선의 방정식 공식 참고 1
		float under = (end2.y() - begin2.y()) * (end1.x() - begin1.x()) - (end2.x() - begin2.x()) * (end1.y() - begin1.y());
		if (under == 0) {
			//완전 내접: 좌변 선이 우변 선을 완전히 포함할 경우
			if (begin1.x() <= begin2.x() && begin1.y() <= begin2.y() && end1.x() >= end2.x() && end1.y() >= end2.y()) {	//operator < > 필요
				return collide_type::contain;	//포함된다고 정의
			}
			//일부 내접
			else if (begin1.x() <= begin2.x() && end1.x() >= begin1.x()) {
				return collide_type::intersect;
			}
			//평행, 만나지 않음
			else {
				return collide_type::none;
			}
		}
		//직선의 방정식 공식 참고 2
		float t_ = (end2.x() - begin2.x()) * (begin1.y() - begin2.y()) - (end2.y() - begin2.y()) * (begin1.x() - begin2.x());
		float s_ = (end1.x() - begin1.x()) * (begin1.y() - begin2.y()) - (end1.y() - begin1.y()) * (begin1.x() - begin2.x());
		t = t_ / under;
		s = s_ / under;
		//공식에선 t와 s가 0과 1 사이여야 교차 판단.
		if (t < 0.0 || t > 1.0 || s < 0.0 || s > 1.0) {
			return collide_type::none;
		}
		//교차
		vec2f e1 = end1;
		vec2f b1 = begin1;
		out_pt = b1 + (e1 - b1) * t;	// const 라서 직접 계산 안 하고 변수 선언
		return collide_type::intersect;
	}

	// 선 vs 선. 2.2. 방정식 pt대입 버전 활용
	const collide_type collider::intersect(const vec2f& begin1, const vec2f& end1, const vec2f& begin2, const vec2f& end2) {
		vec2f tmp = { -2000, -2000 };	//교차점에 의미 없는 값 선 세팅
		return intersect(begin1, end1, begin2, end2, tmp);
	}

	// 선 vs 사각형 (사각형이 선을 포함하는가)
	const collide_type collider::intersect(const rectf& rect, const vec2f& begin, const vec2f& end) {

		if (intersect(rect, begin) == collide_type::intersect
			&& intersect(rect, end) == collide_type::intersect) {
			return collide_type::contain;
		}
		else if (intersect(begin, end, rect.lt(), rect.lb()) == collide_type::intersect
			|| intersect(begin, end, rect.lb(), rect.rb()) == collide_type::intersect
			|| intersect(begin, end, rect.rb(), rect.rt()) == collide_type::intersect
			|| intersect(begin, end, rect.rt(), rect.lt()) == collide_type::intersect) {
			return collide_type::intersect;
		}
		return collide_type::none;
	}

	// 선 vs 원형 (원형이 선을 포함하는가)
	const collide_type collider::intersect(const circlef& circle, vec2f& begin, vec2f& end) {
		//이하 코드는 구글링 후 조건만 좀 변경함.
		const vec2f& origin_to_begin = begin - circle.origin();
		const vec2f& origin_to_end = end - circle.origin();
		float c_begin = origin_to_begin.dot(origin_to_begin) - circle.radius() * circle.radius();
		float c_end = origin_to_end.dot(origin_to_end) - circle.radius() * circle.radius();

		//선분의 시작점부터 구의 중심까지의 거리가 구의 반지름보다 크지 않다면,
		//선분의 시작점이 구의 안에 있으므로 교차함.
		//선분의 시작점도, 끝점도 구 안에 있다면 포함
		if (c_begin <= 0.0f && c_end <= 0.0f) {
			return collide_type::contain;
		}
		else if (c_begin <= 0.0f || c_end <= 0.0f) {
			return collide_type::intersect;
		}

		vec2f dir = end - begin;
		float length = sqrt(dir.dot(dir));	//수정함
		if (length == 0.0f) {
			return collide_type::none;
		}
		const vec2f normalized_dir = dir / length;
		float b_prime = origin_to_begin.dot(normalized_dir);

		//선분의 시작점이 구의 밖에 있고, 구의 중심에서 선분의 시작점을 향하는 벡터와 선분의 방향
		//벡터가 이루는 각이 90도 미만이라면 교차하지 않음
		if (b_prime > 0.0f) {
			return collide_type::none;
		}

		//원래는 b' * b' - a * c를 사용해야 함. 그런데 선분의 방향 벡터가 단위 벡터면,
		//a는 normalized_dir.dot(normalized_dir) = 1
		//이므로, a를 생략 가능.
		float square_root_of_discriminant = sqrt(b_prime * b_prime - c_begin);	//discriminant == 판별식

		float t1 = -b_prime + square_root_of_discriminant;
		if (t1 >= 0.0f && t1 <= length) {
			return collide_type::intersect;
		}
		float t2 = -b_prime + square_root_of_discriminant;
		if (t2 >= 0.0f && t2 <= length) {
			return collide_type::intersect;
		}
		return collide_type::none;
	}
	// 안 되는 듯함
	/*
	const collide_type collision::intersect2(const circlef& circle, const vec2f& begin, const vec2f& end) {
		float d_cb = circle.origin().distance(begin);	//선분 시작점과 원 중심 사이 거리
		float d_ce = circle.origin().distance(end);
		//포함
		if (d_ce < circle.radius() && d_cb < circle.radius()) {
			return collide_type::contain;
		}
		//교차: 선분 한 점이 원 안에
		else if ((d_cb < circle.radius() && d_ce > circle.radius()) || (d_cb > circle.radius() && d_ce < circle.radius())) {
			return collide_type::intersect;
		}
		else {
			return collide_type::none;
		}
	}
	*/
	// 사각형 vs 사각형
	const collide_type collider::intersect(const rectf& rect1, const rectf& rect2) {
		const rectf collision_rect{
			max(rect1.left(), rect2.left()),
			max(rect1.top(), rect2.top()),
			min(rect1.right(), rect2.right()),
			min(rect1.bottom(), rect2.bottom())
		};
		if (collision_rect.width() != 0 || collision_rect.height() != 0) {	//collision_rect는 충돌되는 범위
			if (collision_rect == rect1 || collision_rect == rect2) {
				return collide_type::contain;
			}
			//contain 아닐 때 조건으로 변경
			else if (!(rect1.right() < rect2.left()
				|| rect1.left() > rect2.right()
				|| rect1.bottom() < rect2.top()
				|| rect1.top() > rect2.bottom()
				)) {
				return collide_type::intersect;
			}
		}
		return collide_type::none;
	}

	// 원형 vs 원형
	const collide_type collider::intersect(const circlef& circle1, const circlef& circle2) {
		const float rad_minus = abs(circle1.radius() - circle2.radius());
		const float rad_plus = circle1.radius() + circle2.radius();
		const float dist_sq = circle1.origin().distance_sq(circle2.origin());
		//1 두 점 접, 2 한 점 외접, 3 한 점 내접
		if (dist_sq >= rad_minus * rad_minus && dist_sq <= rad_plus * rad_plus) {
			return collide_type::intersect;
		}
		//4 만나지 않는 경우
		if (dist_sq > rad_plus * rad_plus) {
			return collide_type::none;
		}
		//5 작은 원이 큰 원 안에 있으면서 만나지 않는 경우, 큰 원이 매개변수 좌측이면 포함, 아니면 none
		if (dist_sq < rad_minus * rad_minus && circle1.radius() > circle2.radius()) {
			return collide_type::contain;
		}
		//6 두 원의 중심이 같고 반지름이 다른 경우, 큰 원이 매개변수 좌측이면 포함, 아니면 none
		if (dist_sq == 0 && circle1.radius() > circle2.radius()) {
			return collide_type::contain;
		}
		return collide_type::none;
	}

	// 사각형 vs 원형
	const collide_type collider::intersect(const rectf& rect, const circlef& circle) {
		vec2f lt = rect.lt();
		vec2f lb = rect.lb();
		vec2f rt = rect.rt();
		vec2f rb = rect.rb();
		//교차: 네 선 중 하나라도 겹침
		if (intersect(circle, lt, lb) == collide_type::intersect
			|| intersect(circle, lb, rb) == collide_type::intersect
			|| intersect(circle, rb, rt) == collide_type::intersect
			|| intersect(circle, rt, lt) == collide_type::intersect) {
			return collide_type::intersect;
		}
		//포함
		else if (circle.origin().x() > rect.left()
			&& circle.origin().x() < rect.right()
			&& circle.origin().y() > rect.top()
			&& circle.origin().y() < rect.bottom()
			&& circle.radius() * 2 <= rect.width()
			&& circle.radius() * 2 <= rect.height()) {
			return collide_type::contain;
		}
		return collide_type::none;
	}

	// 원형 vs 사각형
	const collide_type collider::intersect(const circlef& circle, const rectf& rect) {
		vec2f lt = rect.lt();
		vec2f lb = rect.lb();
		vec2f rt = rect.rt();
		vec2f rb = rect.rb();
		//교차: 네 선 중 하나라도 겹침
		if (intersect(circle, lt, lb) == collide_type::intersect
			|| intersect(circle, lb, rb) == collide_type::intersect
			|| intersect(circle, rb, rt) == collide_type::intersect
			|| intersect(circle, rt, lt) == collide_type::intersect) {
			return collide_type::intersect;
		}
		//포함 : 네 선 모두 포함
		if (intersect(circle, lt, lb) == collide_type::contain
			|| intersect(circle, lb, rb) == collide_type::contain
			|| intersect(circle, rb, rt) == collide_type::contain
			|| intersect(circle, rt, lt) == collide_type::contain) {
			return collide_type::contain;
		}
		//아래 코드도 작동하지만, 이미 작성한 선 vs 원형 코드 활용
		/*
		else if (rect.left > circle.origin.x() - circle.radius
			&& rect.right < circle.origin.x() + circle.radius
			&& rect.bottom < circle.origin.x() + circle.radius
			&& rect.top > circle.origin.x() - circle.radius) {
			return collide_type::contain;
		}
		*/
		return collide_type::none;
	}
}