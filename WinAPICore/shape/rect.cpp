#include "rect.h"

namespace yjj {
	rectf::rectf() noexcept
		: lt_({ -1000, -1000 }), lb_({ -1000, -1000 }), rt_({ -1000, -1000 }), rb_({ -1000, -1000 }) {
	}

	rectf::rectf(const rectf& r) {
		set(r);
	}

	rectf::rectf(const float left, const float right, const float top, const float bottom) {
		set(left, right, top, bottom);
	}

	rectf::rectf(const vec2f& lt, const vec2f& rb) {
		set(lt, rb);
	}

	rectf::rectf(const vec2f& lt, const vec2f& lb, const vec2f& rt, const vec2f& rb) {
		set(lt, lb, rt, rb);
	}

	rectf::~rectf() noexcept {
	}

	rectf& rectf::operator=(const rectf& r) {
		set(r.lt(), r.rb());
		return *this;
	}

	rectf& rectf::operator=(const RECT r) {
		set((float)r.left, (float)r.top, (float)r.right, (float)r.bottom);
		return *this;
	}


	bool rectf::operator==(const rectf& r) const {
		return lt() == r.lt() && 
			lb() == r.lb() &&
			rt() == r.rt() &&
			rb() == r.rb();
	}


	float rectf::width() const {
		return abs(right() - left());
	}

	float rectf::height() const {
		return abs(bottom() - top());
	}


	float rectf::left() const {
		return lt().x();
	}

	float rectf::right() const {
		return rt().x();
	}

	float rectf::top() const {
		return lt().y();
	}

	float rectf::bottom() const {
		return lb().y();
	}

	const vec2f& rectf::lt() const {
		return lt_;
	}

	const vec2f& rectf::lb() const {
		return lb_;
	}

	const vec2f& rectf::rt() const {
		return rt_;
	}

	const vec2f& rectf::rb() const {
		return rb_;
	}


	void rectf::set(const rectf& r) {
		set(r.lt(), r.rb());
	}

	void rectf::set(const vec2f& lt, const vec2f& rb) {
		lt_ = lt;
		rb_ = rb;
		lb_ = { lt.x(), rb.y() };
		rt_ = { rb.x(), lt.y() };
	}

	void rectf::set(const vec2f& lt, const vec2f& lb, const vec2f& rt, const vec2f& rb) {
		lt_ = lt;
		lb_ = lb;
		rt_ = rt;
		rb_ = rb;
	}

	void rectf::set(const float left, const float right, const float top, const float bottom) {
		lt_ = { left, top };
		lb_ = { left, bottom };
		rt_ = { right, top };
		rb_ = { right, bottom };
	}

	void rectf::set_lt(const vec2f& lt) {
		lt_ = lt;
	}

	void rectf::set_lb(const vec2f& lb) {
		lb_ = lb;
	}

	void rectf::set_rt(const vec2f& rt) {
		rt_ = rt;
	}

	void rectf::set_rb(const vec2f& rb) {
		rb_ = rb;
	}
}