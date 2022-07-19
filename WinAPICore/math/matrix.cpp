#include "matrix.h"

namespace yjj {
	///////////////////////////////////////////////////////////////////////////
	//행렬 2x2//////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////

	matrix2f::matrix2f() noexcept :
		m0_(0, 0),
		m1_(0, 0) {
	}

	matrix2f::matrix2f(const vec2f& v0, const vec2f& v1) {
		set(v0, v1);
	}

	matrix2f::matrix2f(const matrix2f& m) {
		set(m);
	}


	matrix2f& matrix2f::operator=(const matrix2f& m) {
		set(m);
		return *this;
	}

	matrix2f& matrix2f::operator+=(const matrix2f& m) {
		add(m);
		return *this;
	}
	matrix2f& matrix2f::operator-=(const matrix2f& m) {
		sub(m);
		return *this;
	}


	matrix2f matrix2f::operator*=(const matrix2f& m) {
		mul(m);
		return *this;
	}


	void matrix2f::add(vec2f& v0, vec2f& v1) {
		set_m0(m0_ + v0);
		set_m1(m1_ + v1);
	}
	void matrix2f::add(const matrix2f& m) {
		set_m0(m0_ + m.m0());
		set_m1(m1_ + m.m1());
	}

	void matrix2f::sub(const vec2f& v0, const vec2f& v1) {
		set_m0(m0_ - v0);
		set_m1(m1_ - v1);
	}
	void matrix2f::sub(const matrix2f& m) {
		set_m0(m0_ - m.m0());
		set_m1(m1_ - m.m1());
	}

	vec2f matrix2f::mul(const vec2f& v) {
		vec2f ret;
		ret.set_x(m0().x() * v.x() + m1().x() * v.y());
		ret.set_y(m0().y() * v.x() + m1().y() * v.y());
		return ret;
	}
	void matrix2f::mul(const vec2f& v0, const vec2f& v1) {
		matrix2f ret;
		ret.set({ m0().x() * v0.x() +
			m1().x() * v0.y()
			,
			m0().x() * v1.x() +
			m1().x() * v1.y() }
			, 
			{ m0().y() * v0.x() +
			m1().y() * v0.y()
			,
			m0().y() * v1.x() +
			m1().y() * v1.y() });
		ret.transposed();
	}
	void matrix2f::mul(const matrix2f& m) {
		mul(m.m0(), m.m1());
	}


	float matrix2f::determinant() const {
		float a = m0().x(); float b = m1().x();
		float c = m0().y();	float d = m1().y();
		return a * d - b * c;
	}

	void matrix2f::inverse(const vec2f& v0, const vec2f& v1) {
		set(v0, v1);
		inverse(*this);
	}
	void matrix2f::inverse(const matrix2f& m) {
		float a = m0().x(); float b = m1().x();
		float c = m0().y(); float d = m1().y();
		float ad_bc = a * d - b * c;
		if (0.0f != ad_bc) {
			set({ d,-b }, { -c,a });
			m0_.mul(1 / ad_bc);
			m1_.mul(1 / ad_bc);
		}
		else {
			assert(false);
		}
	}

	bool matrix2f::is_identity() const {
		bool is_identity;
		is_identity =
			m0().x() == 1 && m1().x() == 0 &&
			m0().y() == 0 && m1().y() == 1;
		return is_identity;
	}

	void matrix2f::transposed() {
		matrix2f m(
			{ m0().x(), m1().x() },
			{ m0().y(), m1().y() }
		);
		set(m);
	}

	const vec2f matrix2f::m0() const {
		return m0_;
	}
	const vec2f matrix2f::m1() const {
		return m1_;
	}


	void matrix2f::set(const vec2f& v0, const vec2f& v1) {
		set_m0(v0);
		set_m1(v1);
	}
	void matrix2f::set(const matrix2f& m) {
		set_m0(m.m0());
		set_m1(m.m1());
	}

	void matrix2f::set_m0(const vec2f& v0) {
		m0_ = v0;
	}
	void matrix2f::set_m1(const vec2f& v1) {
		m1_ = v1;
	}







	///////////////////////////////////////////////////////////////////////////
	//행렬 3x3//////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////

	matrix3f::matrix3f() noexcept :
		m0_(0, 0, 0),
		m1_(0, 0, 0),
		m2_(0, 0, 0) {
	}

	matrix3f::matrix3f(const vec3f& v0, const vec3f& v1, const vec3f& v2) {
		set(v0, v1, v2);
	}

	matrix3f::matrix3f(const matrix3f& m) {
		set(m);
	}


	matrix3f& matrix3f::operator=(const matrix3f& m) {
		set(m);
		return *this;
	}

	matrix3f& matrix3f::operator+=(const matrix3f& m) {
		add(m);
		return *this;
	}
	matrix3f& matrix3f::operator-=(const matrix3f& m) {
		sub(m);
		return *this;
	}


	matrix3f matrix3f::operator*=(const matrix3f& m) {
		mul(m);
		return *this;
	}


	void matrix3f::add(const vec3f& v0, const vec3f& v1, const vec3f& v2) {
		set_m0(m0_ + v0);
		set_m1(m1_ + v1);
		set_m1(m2_ + v2);
	}
	void matrix3f::add(const matrix3f& m) {
		set_m0(m0_ + m.m0());
		set_m1(m1_ + m.m1());
		set_m1(m2_ + m.m2());
	}

	void matrix3f::sub(const vec3f& v0, const vec3f& v1, const vec3f& v2) {
		set_m0(m0_ - v0);
		set_m1(m1_ - v1);
		set_m1(m2_ - v2);
	}
	void matrix3f::sub(const matrix3f& m) {
		set_m0(m0_ - m.m0());
		set_m1(m1_ - m.m1());
		set_m2(m2_ - m.m2());
	}

	vec3f matrix3f::mul(const vec3f& v) {
		vec3f ret;
		ret.set_x(m0().x() * v.x() + 
			m1().x() * v.y() + 
			m2().x() * v.z());
		ret.set_y(m0().y() * v.x() + 
			m1().y() * v.y() + 
			m2().y() * v.z());
		ret.set_z(m0().z() * v.x() + 
			m1().z() * v.y() + 
			m2().z() * v.z());
		return ret;
	}
	void matrix3f::mul(const vec3f& v0, const vec3f& v1, const vec3f& v2) {
		matrix3f ret;
		ret.set(
			{ m0().x() * v0.x() +
			m1().x() * v0.y() +
			m2().x() * v0.z()
			, m0().x() * v1.x() +
			m1().x() * v1.y() +
			m2().x() * v1.z()
			, m0().x() * v2.x() +
			m1().x() * v2.y() +
			m2().x() * v2.z() }
			,
			{ m0().y() * v0.x() +
			m1().y() * v0.y() +
			m2().y() * v0.z()
			, m0().y() * v1.x() +
			m1().y() * v1.y() +
			m2().y() * v1.z()
			, m0().y() * v2.x() +
			m1().y() * v2.y() +
			m2().y() * v2.z() }
			,
			{ m0().z() * v0.x() +
			m1().z() * v0.y() +
			m2().z() * v0.z()
			, m0().z() * v1.x() +
			m1().z() * v1.y() +
			m2().z() * v1.z()
			, m0().z() * v2.x() +
			m1().z() * v2.y() +
			m2().z() * v2.z() }
			);
		ret.transposed();
	}
	void matrix3f::mul(const matrix3f& m) {
		mul(m.m0(), m.m1(), m.m2());
	}

	vec3f matrix3f::mul(const vec2f& v) {
		vec3f v3 = { v.x(), v.y(), 1};
		return mul(v3);
	}


	void matrix3f::translate(const float dx, const float dy) {
		set({ 1, 0, dx }, 
			{ 0, 1, dy }, 
			{ 0, 0, 1 });
	}

	void matrix3f::scale(const float sx, const float sy) {
		set({ sx, 0, 0 }, 
			{ 0, sy, 0 },
			{ 0, 0, 1 }
		);
	}

	void matrix3f::rotate(const float angle, const float dx, const float dy) {
		set({ (float)cos(angle), (float)-sin(angle), 0 },
			{ (float)sin(angle), (float)cos(angle), 0 },
			{ 0, 0, 1 });
	}


	float matrix3f::determinant() const {
		float a = m0().x(); float b = m1().x(); float c = m2().x();
		float d = m0().y(); float e = m1().y(); float f = m2().y();
		float g = m0().z(); float h = m1().z(); float i = m2().z();
		return d * (e * i - f * h) - b * (d * i - f * g) + c * (d * h - e * g);
	}

	bool matrix3f::is_identity() const {
		bool is_identity;
		is_identity =
			m0().x() == 1 && m1().x() == 0 && m2().x() == 0 &&
			m0().y() == 0 && m1().y() == 1 && m2().y() == 0 &&
			m0().z() == 0 && m1().z() == 0 && m2().z() == 1;
		return is_identity;
	}

	void matrix3f::transposed() {
		matrix3f m(
			{ m0().x(), m0().y(), m0().z() },
			{ m1().x(), m1().y(), m1().z() },
			{ m2().x(), m2().y(), m2().z() }
		);
		set(m);
	}


	const vec3f& matrix3f::m0() const {
		return m0_;
	}
	const vec3f& matrix3f::m1() const {
		return m1_;
	}
	const vec3f& matrix3f::m2() const {
		return m2_;
	}


	void matrix3f::set(const vec3f& v0, const vec3f& v1, const vec3f& v2) {
		set_m0(v0);
		set_m1(v1);
		set_m2(v2);
	}
	void matrix3f::set(const matrix3f& m) {
		set_m0(m.m0());
		set_m1(m.m1());
		set_m2(m.m2());
	}

	void matrix3f::set_m0(const vec3f& v0) {
		m0_ = v0;
	}
	void matrix3f::set_m1(const vec3f& v1) {
		m1_ = v1;
	}
	void matrix3f::set_m2(const vec3f& v2) {
		m2_ = v2;
	}

}