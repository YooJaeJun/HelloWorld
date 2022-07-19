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
		// �浹
		// cf) intersect, contain: ���� �Ű������� ������ �Ű������� �浹, ������ ���

		// �� vs ��
		const collide_type intersect(const vec2f& begin, const vec2f& end, const vec2f& pt);
		// �� vs �簢��
		const collide_type intersect(const rectf& rectf, const vec2f& pt);
		// �� vs ����
		const collide_type intersect(const circlef& Ellipse, const vec2f& pt);
		// �� vs �� 1. ���� ���� �̿� ���
		const int comparator(const vec2f& l, const vec2f& r);
		void swap(vec2f& l, vec2f& r);
		const collide_type intersect_with_vector(vec2f& begin1, vec2f& end1, vec2f& begin2, vec2f& end2);
		// �� vs �� 2.1. ������ pt���� ���� 
		const collide_type intersect(const vec2f& begin1, const vec2f& end1, const vec2f& begin2, const vec2f& end2, vec2f& out_pt);
		// �� vs ��. 2.2. ������ pt���� ���� Ȱ��
		const collide_type intersect(const vec2f& begin1, const vec2f& end1, const vec2f& begin2, const vec2f& end2);

		// �� vs �簢�� (�簢���� ���� �����ϴ°�)
		const collide_type intersect(const rectf& rectf, const vec2f& begin, const vec2f& end);
		// �� vs ���� (������ ���� �����ϴ°�)
		const collide_type intersect(const circlef& Ellipse, vec2f& begin, vec2f& end);
		// const collide_type intersect2(const circlef& Ellipse, const vec2f& begin, const vec2f& end);
		// �簢�� vs �簢��
		const collide_type intersect(const rectf& rectf1, const rectf& rectf2);
		// ���� vs ����
		const collide_type intersect(const circlef& Ellipse1, const circlef& Ellipse2);
		// �簢�� vs ����
		const collide_type intersect(const rectf& rectf, const circlef& Ellipse);
		// ���� vs �簢��
		const collide_type intersect(const circlef& Ellipse, const rectf& rectf);
	};
}