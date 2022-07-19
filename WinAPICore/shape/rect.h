#pragma once
#include "../core/core.h"
#include "../math/vec.h"

namespace yjj {
	class rectf {
	public:
		rectf() noexcept;
		rectf(const rectf& r);
		explicit rectf(const float left, const float right, const float top, const float bottom);
		explicit rectf(const vec2f& lt, const vec2f& rb);
		explicit rectf(const vec2f& lt, const vec2f& lb, const vec2f& rt, const vec2f& rb);

		virtual ~rectf() noexcept;

		rectf& operator=(const rectf& r);
		rectf& operator=(const RECT r);

		bool operator==(const rectf& r) const;

		float left() const;
		float right() const;
		float top() const;
		float bottom() const;

		const vec2f& lt() const;
		const vec2f& lb() const;
		const vec2f& rt() const;
		const vec2f& rb() const;

		float width() const;
		float height() const;

		void set(const rectf& r);
		void set(const vec2f& lt, const vec2f& rb);
		void set(const vec2f& lt, const vec2f& lb, const vec2f& rt, const vec2f& rb);
		void set(const float left, const float right, const float top, const float bottom);
		void set_lt(const vec2f& lt);
		void set_lb(const vec2f& lb);
		void set_rt(const vec2f& rt);
		void set_rb(const vec2f& rb);

	private:
		vec2f lt_;
		vec2f lb_;
		vec2f rt_;
		vec2f rb_;
	};
}