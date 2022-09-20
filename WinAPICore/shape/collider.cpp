#include <cmath>
#include <numeric>
#include "collider.h"
#include "../math/vec.h"
using namespace std;

namespace yjj {
	// �浹
	// cf) intersect, contain: ���� �Ű������� ������ �Ű������� �浹, ������ ���
		 
	// �� vs ��
	const collide_type collider::intersect(const vec2f& begin, const vec2f& end, const vec2f& pt) {	//����ã��.
		if (pt.x() >= begin.x() && pt.x() <= end.x()
			&& pt.y() >= begin.y() && pt.y() <= end.y()) {
			return collide_type::intersect;
		}
		return collide_type::none;
	}

	// �� vs �簢��
	const collide_type collider::intersect(const rectf& rect, const vec2f& pt) {
		if ((pt.x() >= rect.left() && pt.x() <= rect.right())
			&& (pt.y() <= rect.bottom() && pt.y() >= rect.top())) {
			return collide_type::intersect;
		}
		return collide_type::none;
	}

	// �� vs ����
	const collide_type collider::intersect(const circlef& circle, const vec2f& pt) {
		if (circle.origin().distance_sq(pt) <= circle.radius() * circle.radius()) {
			return collide_type::intersect;
		}
		return collide_type::none;
	}

	// �� vs �� 1. ���� ���� �̿� ���
	const int collider::comparator(const vec2f& l, const vec2f& r) {
		//operator< > �Լ� �ʿ�
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
		//���� ��� �ݽð�, ���� ���� �ð�, ���� 0 ����		==> ��ǥ�谡 y()������̶� �ݴ��ε�
		//(x()1, y()1) ���� (x()2, y()2) == (x()1*y()2) - (x()2*y()1).	
		//�� ������ begin���� �ٸ� ������ begin����, end���� ������ �ϳ��� ���, �ϳ��� ������ ���;� ��. �ٸ� ���� begin�� �ݺ�.

		//�� ������ �� ���� ���� �ְų�, ������ ��ġ�� ���
		float ccw1 = begin1.ccw(begin2) * begin1.ccw(end2);
		float ccw2 = begin2.ccw(begin1) * begin2.ccw(end1);
		if (ccw1 == 0 && ccw2 == 0) {
			//���� ����. ���� ���ش� ����
			if (comparator(end1, begin1)) {
				swap(begin1, end1);
			}
			if (comparator(end2, begin2)) {
				swap(begin2, end2);
			}
			//����
			if (comparator(begin2, end1) && comparator(begin1, end2)) {
				//���� ����
				if (begin1.x() <= begin2.x() && begin1.y() <= begin2.y() && end1.x() >= end2.x() && end1.y() >= end2.y()) {	//operator < > �ʿ�
					return collide_type::contain;	//���Եȴٰ� ����
				}
				return collide_type::intersect;
			}
		}
		//�߰����� ��ġ�� ���
		else if (ccw1 <= 0 && ccw2 <= 0) {
			return collide_type::intersect;
		}
		return collide_type::none;
	}

	// �� vs �� 2.1. ������ pt���� ���� 
	const collide_type collider::intersect(const vec2f& begin1, const vec2f& end1, const vec2f& begin2, const vec2f& end2, vec2f& out_pt) {
		float t;
		float s;
		//������ ������ ���� ���� 1
		float under = (end2.y() - begin2.y()) * (end1.x() - begin1.x()) - (end2.x() - begin2.x()) * (end1.y() - begin1.y());
		if (under == 0) {
			//���� ����: �º� ���� �캯 ���� ������ ������ ���
			if (begin1.x() <= begin2.x() && begin1.y() <= begin2.y() && end1.x() >= end2.x() && end1.y() >= end2.y()) {	//operator < > �ʿ�
				return collide_type::contain;	//���Եȴٰ� ����
			}
			//�Ϻ� ����
			else if (begin1.x() <= begin2.x() && end1.x() >= begin1.x()) {
				return collide_type::intersect;
			}
			//����, ������ ����
			else {
				return collide_type::none;
			}
		}
		//������ ������ ���� ���� 2
		float t_ = (end2.x() - begin2.x()) * (begin1.y() - begin2.y()) - (end2.y() - begin2.y()) * (begin1.x() - begin2.x());
		float s_ = (end1.x() - begin1.x()) * (begin1.y() - begin2.y()) - (end1.y() - begin1.y()) * (begin1.x() - begin2.x());
		t = t_ / under;
		s = s_ / under;
		//���Ŀ��� t�� s�� 0�� 1 ���̿��� ���� �Ǵ�.
		if (t < 0.0 || t > 1.0 || s < 0.0 || s > 1.0) {
			return collide_type::none;
		}
		//����
		vec2f e1 = end1;
		vec2f b1 = begin1;
		out_pt = b1 + (e1 - b1) * t;	// const �� ���� ��� �� �ϰ� ���� ����
		return collide_type::intersect;
	}

	// �� vs ��. 2.2. ������ pt���� ���� Ȱ��
	const collide_type collider::intersect(const vec2f& begin1, const vec2f& end1, const vec2f& begin2, const vec2f& end2) {
		vec2f tmp = { -2000, -2000 };	//�������� �ǹ� ���� �� �� ����
		return intersect(begin1, end1, begin2, end2, tmp);
	}

	// �� vs �簢�� (�簢���� ���� �����ϴ°�)
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

	// �� vs ���� (������ ���� �����ϴ°�)
	const collide_type collider::intersect(const circlef& circle, vec2f& begin, vec2f& end) {
		//���� �ڵ�� ���۸� �� ���Ǹ� �� ������.
		const vec2f& origin_to_begin = begin - circle.origin();
		const vec2f& origin_to_end = end - circle.origin();
		float c_begin = origin_to_begin.dot(origin_to_begin) - circle.radius() * circle.radius();
		float c_end = origin_to_end.dot(origin_to_end) - circle.radius() * circle.radius();

		//������ ���������� ���� �߽ɱ����� �Ÿ��� ���� ���������� ũ�� �ʴٸ�,
		//������ �������� ���� �ȿ� �����Ƿ� ������.
		//������ ��������, ������ �� �ȿ� �ִٸ� ����
		if (c_begin <= 0.0f && c_end <= 0.0f) {
			return collide_type::contain;
		}
		else if (c_begin <= 0.0f || c_end <= 0.0f) {
			return collide_type::intersect;
		}

		vec2f dir = end - begin;
		float length = sqrt(dir.dot(dir));	//������
		if (length == 0.0f) {
			return collide_type::none;
		}
		const vec2f normalized_dir = dir / length;
		float b_prime = origin_to_begin.dot(normalized_dir);

		//������ �������� ���� �ۿ� �ְ�, ���� �߽ɿ��� ������ �������� ���ϴ� ���Ϳ� ������ ����
		//���Ͱ� �̷�� ���� 90�� �̸��̶�� �������� ����
		if (b_prime > 0.0f) {
			return collide_type::none;
		}

		//������ b' * b' - a * c�� ����ؾ� ��. �׷��� ������ ���� ���Ͱ� ���� ���͸�,
		//a�� normalized_dir.dot(normalized_dir) = 1
		//�̹Ƿ�, a�� ���� ����.
		float square_root_of_discriminant = sqrt(b_prime * b_prime - c_begin);	//discriminant == �Ǻ���

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
	// �� �Ǵ� ����
	/*
	const collide_type collision::intersect2(const circlef& circle, const vec2f& begin, const vec2f& end) {
		float d_cb = circle.origin().distance(begin);	//���� �������� �� �߽� ���� �Ÿ�
		float d_ce = circle.origin().distance(end);
		//����
		if (d_ce < circle.radius() && d_cb < circle.radius()) {
			return collide_type::contain;
		}
		//����: ���� �� ���� �� �ȿ�
		else if ((d_cb < circle.radius() && d_ce > circle.radius()) || (d_cb > circle.radius() && d_ce < circle.radius())) {
			return collide_type::intersect;
		}
		else {
			return collide_type::none;
		}
	}
	*/
	// �簢�� vs �簢��
	const collide_type collider::intersect(const rectf& rect1, const rectf& rect2) {
		const rectf collision_rect{
			max(rect1.left(), rect2.left()),
			max(rect1.top(), rect2.top()),
			min(rect1.right(), rect2.right()),
			min(rect1.bottom(), rect2.bottom())
		};
		if (collision_rect.width() != 0 || collision_rect.height() != 0) {	//collision_rect�� �浹�Ǵ� ����
			if (collision_rect == rect1 || collision_rect == rect2) {
				return collide_type::contain;
			}
			//contain �ƴ� �� �������� ����
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

	// ���� vs ����
	const collide_type collider::intersect(const circlef& circle1, const circlef& circle2) {
		const float rad_minus = abs(circle1.radius() - circle2.radius());
		const float rad_plus = circle1.radius() + circle2.radius();
		const float dist_sq = circle1.origin().distance_sq(circle2.origin());
		//1 �� �� ��, 2 �� �� ����, 3 �� �� ����
		if (dist_sq >= rad_minus * rad_minus && dist_sq <= rad_plus * rad_plus) {
			return collide_type::intersect;
		}
		//4 ������ �ʴ� ���
		if (dist_sq > rad_plus * rad_plus) {
			return collide_type::none;
		}
		//5 ���� ���� ū �� �ȿ� �����鼭 ������ �ʴ� ���, ū ���� �Ű����� �����̸� ����, �ƴϸ� none
		if (dist_sq < rad_minus * rad_minus && circle1.radius() > circle2.radius()) {
			return collide_type::contain;
		}
		//6 �� ���� �߽��� ���� �������� �ٸ� ���, ū ���� �Ű����� �����̸� ����, �ƴϸ� none
		if (dist_sq == 0 && circle1.radius() > circle2.radius()) {
			return collide_type::contain;
		}
		return collide_type::none;
	}

	// �簢�� vs ����
	const collide_type collider::intersect(const rectf& rect, const circlef& circle) {
		vec2f lt = rect.lt();
		vec2f lb = rect.lb();
		vec2f rt = rect.rt();
		vec2f rb = rect.rb();
		//����: �� �� �� �ϳ��� ��ħ
		if (intersect(circle, lt, lb) == collide_type::intersect
			|| intersect(circle, lb, rb) == collide_type::intersect
			|| intersect(circle, rb, rt) == collide_type::intersect
			|| intersect(circle, rt, lt) == collide_type::intersect) {
			return collide_type::intersect;
		}
		//����
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

	// ���� vs �簢��
	const collide_type collider::intersect(const circlef& circle, const rectf& rect) {
		vec2f lt = rect.lt();
		vec2f lb = rect.lb();
		vec2f rt = rect.rt();
		vec2f rb = rect.rb();
		//����: �� �� �� �ϳ��� ��ħ
		if (intersect(circle, lt, lb) == collide_type::intersect
			|| intersect(circle, lb, rb) == collide_type::intersect
			|| intersect(circle, rb, rt) == collide_type::intersect
			|| intersect(circle, rt, lt) == collide_type::intersect) {
			return collide_type::intersect;
		}
		//���� : �� �� ��� ����
		if (intersect(circle, lt, lb) == collide_type::contain
			|| intersect(circle, lb, rb) == collide_type::contain
			|| intersect(circle, rb, rt) == collide_type::contain
			|| intersect(circle, rt, lt) == collide_type::contain) {
			return collide_type::contain;
		}
		//�Ʒ� �ڵ嵵 �۵�������, �̹� �ۼ��� �� vs ���� �ڵ� Ȱ��
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