#include "circle.h"

namespace yjj {
	circlef::circlef() noexcept {
	}

	circlef::circlef(const circlef& c) {
		set(c);
	}

	circlef::circlef(const vec2f& origin, const float radius) {
		origin_ = origin;
		radius_ = radius;
	}

	circlef::~circlef() noexcept {
	}


	bool circlef::operator==(const circlef& c) const {
		return origin() == c.origin() && radius() == c.radius();
	}



	const vec2f& circlef::origin() const {
		return origin_;
	}
	const float circlef::radius() const {
		return radius_;
	}


	void circlef::set(const circlef& c) {
		set(c.origin(), c.radius());
	}

	void circlef::set(const vec2f& origin, const float radius) {
		origin_ = origin;
		radius_ = radius;
	}

	void circlef::set_origin(const vec2f& other) {
		origin_ = other;
	}

	void circlef::set_radius(const float other) {
		radius_ = other;
	}
}