#include "vec.h"

namespace yjj {
	///////////////////////////////////////////////////////////////////////////
	//vec2f//////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////

	vec2f::vec2f() noexcept {
	}

	vec2f::vec2f(const POINT& p) {
		x_ = (float)p.x;
		y_ = (float)p.y;
	}

	vec2f::vec2f(const vec2f& p) {
		x_ = p.x();
		y_ = p.y();
	}

	vec2f::vec2f(const float x, const float y) {
		x_ = x;
		y_ = y;
	}

	vec2f::~vec2f() noexcept {
	}



	vec2f& vec2f::operator=(const vec2f& p) {
		set(p);
		return *this;
	}

	bool vec2f::operator==(const vec2f& p) const {
		return x() == p.x() && y() == p.y();
	}


	vec2f& vec2f::operator+(const vec2f& p) {
		sum(p);
		return *this;
	}
	vec2f& vec2f::operator-(const vec2f& p) {
		sub(p);
		return *this;
	}
	vec2f& vec2f::operator*(const vec2f& p) {
		mul(p);
		return *this;
	}
	vec2f& vec2f::operator/(const vec2f& p) {
		div(p);
		return *this;
	}

	vec2f& vec2f::operator+(const float val) {
		sum(val);
		return *this;
	}
	vec2f& vec2f::operator-(const float val) {
		sub(val);
		return *this;
	}
	vec2f& vec2f::operator*(const float val) {
		mul(val);
		return *this;
	}
	vec2f& vec2f::operator/(const float val) {
		div(val);
		return *this;
	}


	void vec2f::sum(const vec2f& p) {
		set({ x() + p.x(), y() + p.y() });
	}

	void vec2f::sub(const vec2f& p) {
		set({ x() - p.x(), y() - p.y() });
	}

	void vec2f::mul(const vec2f& p) {
		set({ x() * p.x(), y() * p.y() });
	}

	void vec2f::div(const vec2f& p) {
		if (p.x() != 0 && p.y() != 0) {
			set({ x() / p.x(), y() / p.y() });
		}
		assert(false);
	}

	void vec2f::sum(const float val) {
		sum({ val, val });
	}

	void vec2f::sub(const float val) {
		sub({ val, val });
	}

	void vec2f::mul(const float val) {
		mul({ val, val });
	}

	void vec2f::div(const float val) {
		div({ val, val });
	}



	float vec2f::dot(const vec2f& p) const {
		return x() * p.x() + 
			y() * p.y();
	}

	float vec2f::distance_sq(const vec2f& p) const {
		return (max(x(), p.x()) - min(x(), p.x())) * (max(x(), p.x()) - min(x(), p.x())) +
			(max(y(), p.y()) - min(y(), p.y())) * (max(y(), p.y()) - min(y(), p.y()));
	}

	float vec2f::distance(const vec2f& p) const {
		return (float)sqrt(distance_sq(p));
	}

	float vec2f::ccw(const vec2f& p) const {
		return x() * p.y() - x() * p.y();
	}

	float vec2f::reciprocal(const float val) const {
		return 1 / val;
	}

	const vec2f vec2f::reciprocal() const {
		return { 1 / x(), 1 / y() };
	}

	const vec2f& vec2f::normalize(const vec2f& p) {
		mul(reciprocal(distance(p)));
		return *this;
	}



	float vec2f::x() const {
		return x_;
	}

	float vec2f::y() const {
		return y_;
	}

	void vec2f::set(const vec2f& p) {
		x_ = p.x();
		y_ = p.y();
	}

	void vec2f::set_x(const float x) {
		x_ = x;
	}

	void vec2f::set_y(const float y) {
		y_ = y;
	}







	///////////////////////////////////////////////////////////////////////////
	//vec3f//////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////

	vec3f::vec3f() noexcept {
	}

	vec3f::vec3f(const POINT& p) {
		x_ = (float)p.x;
		y_ = (float)p.y;
		z_ = 1.0f;
	}

	vec3f::vec3f(const vec3f& p) {
		x_ = p.x();
		y_ = p.y();
		z_ = p.z();
	}

	vec3f::vec3f(const float x, const float y, const float z) {
		x_ = x;
		y_ = y;
		z_ = z;
	}

	vec3f::~vec3f() noexcept {
	}



	vec3f& vec3f::operator=(const vec3f& p) {
		set(p);
		return *this;
	}

	bool vec3f::operator==(const vec3f& p) const {
		return x() == p.x() && y() == p.y() && z() == p.z();
	}


	vec3f& vec3f::operator+(const vec3f& p) {
		sum(p);
		return *this;
	}
	vec3f& vec3f::operator-(const vec3f& p) {
		sub(p);
		return *this;
	}
	vec3f& vec3f::operator*(const vec3f& p) {
		mul(p);
		return *this;
	}
	vec3f& vec3f::operator/(const vec3f& p) {
		div(p);
		return *this;
	}

	vec3f& vec3f::operator+(const float val) {
		sum(val);
		return *this;
	}
	vec3f& vec3f::operator-(const float val) {
		sub(val);
		return *this;
	}
	vec3f& vec3f::operator*(const float val) {
		mul(val);
		return *this;
	}
	vec3f& vec3f::operator/(const float val) {
		div(val);
		return *this;
	}


	void vec3f::sum(const vec3f& p) {
		set({ x() + p.x(), y() + p.y(), z() + p.z() });
	}

	void vec3f::sub(const vec3f& p) {
		set({ x() - p.x(), y() - p.y(), z() - p.z() });
	}

	void vec3f::mul(const vec3f& p) {
		set({ x() * p.x(), y() * p.y(), z() * p.z() });
	}

	void vec3f::div(const vec3f& p) {
		if (p.x() != 0 && p.y() != 0 && p.z() != 0) {
			set({ x() / p.x(), y() / p.y(), z() / p.z() });
		}
		assert(false);
	}

	void vec3f::sum(const float val) {
		sum({ val, val, val });
	}

	void vec3f::sub(const float val) {
		sub({ val, val, val });
	}

	void vec3f::mul(const float val) {
		mul({ val, val, val });
	}

	void vec3f::div(const float val) {
		div({ val, val, val });
	}



	float vec3f::dot(const vec3f& p) const {
		return x() * p.x() + 
			y() * p.y() + 
			z() * p.z();
	}

	float vec3f::distance_sq(const vec3f& p) const {
		return (max(x(), p.x()) - min(x(), p.x())) * (max(x(), p.x()) - min(x(), p.x())) +
			(max(y(), p.y()) - min(y(), p.y())) * (max(y(), p.y()) - min(y(), p.y())) +
			(max(z(), p.z()) - min(z(), p.z())) * (max(z(), p.z()) - min(z(), p.z()));
	}

	float vec3f::distance(const vec3f& p) const {
		return (float)sqrt((float)distance_sq(p));
	}

	float vec3f::ccw(const vec3f& p) const {
		return y() * p.z() - z() * p.y(),
			z()* p.x() - x() * p.z(),
			x()* p.y() - y() * p.x();
	}

	float vec3f::reciprocal(const float val) const {
		return 1 / val;
	}

	const vec3f vec3f::reciprocal() const {
		return { 1 / x(), 1 / y(), 1 / z()};
	}

	const vec3f& vec3f::normalize(const vec3f& p) {
		mul(reciprocal(distance(p)));
		return *this;
	}



	float vec3f::x() const {
		return x_;
	}

	float vec3f::y() const {
		return y_;
	}

	float vec3f::z() const {
		return z_;
	}

	void vec3f::set(const vec3f& p) {
		x_ = p.x();
		y_ = p.y();
		z_ = p.z();
	}

	void vec3f::set_x(const float x) {
		x_ = x;
	}

	void vec3f::set_y(const float y) {
		y_ = y;
	}

	void vec3f::set_z(const float z) {
		z_ = z;
	}
}