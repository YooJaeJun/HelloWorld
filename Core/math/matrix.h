#pragma once
#include "vec.h"

namespace yjj {
	///////////////////////////////////////////////////////////////////////////
	//��� 2x2//////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////

	class matrix2f {
	public:
		//�⺻
		matrix2f() noexcept;
		explicit matrix2f(const vec2f& v0, const vec2f& v1);
		matrix2f(const matrix2f& m);

		virtual ~matrix2f() noexcept = default;

		//������
		matrix2f& operator=(const matrix2f& m);
		matrix2f& operator+=(const matrix2f& m);
		matrix2f& operator-=(const matrix2f& m);

		//2x2 * 2x2
		matrix2f operator*=(const matrix2f& m);

		//����
		void add(vec2f& v0, vec2f& v1);
		void add(const matrix2f& m);

		void sub(const vec2f& v0, const vec2f& v1);
		void sub(const matrix2f& m);

		//2x2 * 1x2
		vec2f mul(const vec2f& v);
		//2x2 * 2x2
		void mul(const matrix2f& m);
		void mul(const vec2f& v0, const vec2f& v1);


		//��Ľ�: 2x2 ad-bc
		float determinant() const;
		//�����: �׵���� ������ ��. 1/ad-bc * (d -b; -c a).
		void inverse(const vec2f& v0, const vec2f& v1);
		void inverse(const matrix2f& m);
		//�������: ����
		bool is_identity() const;
		//��ġ���: ��� ���� ��ȯ
		void transposed();

		//get, set
		const vec2f m0() const;
		const vec2f m1() const;

		void set(const vec2f& v0, const vec2f& v1);
		void set(const matrix2f& m);
		void set_m0(const vec2f& m);
		void set_m1(const vec2f& m);


	private:
		vec2f m0_;
		vec2f m1_;
	};


	
	///////////////////////////////////////////////////////////////////////////
	//��� 3x3//////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////

	class matrix3f {
	public:
		//�⺻
		matrix3f() noexcept;
		explicit matrix3f(const vec3f& v0, const vec3f& v1, const vec3f& v2);
		matrix3f(const matrix3f& m);

		virtual ~matrix3f() noexcept = default;

		//������
		matrix3f& operator=(const matrix3f& m);
		matrix3f& operator+=(const matrix3f& m);
		matrix3f& operator-=(const matrix3f& m);

		//3x3 * 3x3
		matrix3f operator*=(const matrix3f& m);

		//����
		void add(const vec3f& v0, const vec3f& v1, const vec3f& v2);
		void add(const matrix3f& m);

		void sub(const vec3f& v0, const vec3f& v1, const vec3f& v2);
		void sub(const matrix3f& m);

		//3x3 * 1x3
		vec3f mul(const vec3f& v);
		//3x3 * 3x3
		void mul(const matrix3f& m);
		void mul(const vec3f& v0, const vec3f& v1, const vec3f& v2);

		//3x3 * 1x2  2���� ��ȯ��� (���� Ŭ���� ���� �ʰ� ����� ����)
		vec3f mul(const vec2f& v);

		//��ȯ (2���������� ��ȯ ����)
		void translate(const float dx, const float dy);
		void scale(const float sx, const float sy);
		void rotate(const float angle, const float dx, const float dy);

		//��Ľ�: 3x3 d(ei-fh)-b(di-fg)+c(dh-eg)
		float determinant() const;
		//�����: �׵���� ������ ��.
		//void inverse(const vec3f& v0, const vec3f& v1, const vec3f& v2);
		//void inverse(const matrix3f& m);
		//�������: ����
		bool is_identity() const;
		//��ġ���: ��� ���� ��ȯ
		void transposed();

		//get, set
		const vec3f& m0() const;
		const vec3f& m1() const;
		const vec3f& m2() const;

		void set(const vec3f& v0, const vec3f& v1, const vec3f& v2);
		void set(const matrix3f& m);
		void set_m0(const vec3f& v0);
		void set_m1(const vec3f& v1);
		void set_m2(const vec3f& v2);


	private:
		vec3f m0_;
		vec3f m1_;
		vec3f m2_;
	};
}