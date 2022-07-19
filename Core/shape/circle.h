#pragma once
#include "../math/vec.h"

namespace yjj {
	class circlef {
	public:
		circlef() noexcept;
		circlef(const circlef& c);
		explicit circlef(const vec2f& origin, const float radius);
		virtual ~circlef() noexcept;

		bool operator==(const circlef& c) const;

		const vec2f& origin() const;
		const float radius() const;
		void set(const circlef& c);
		void set(const vec2f& origin, const float radius);
		void set_origin(const vec2f& other);
		void set_radius(const float other);
	private:
		vec2f origin_{ -1000, -1000 };
		float radius_ = 0;
	};
}