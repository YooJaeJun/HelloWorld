#pragma once
#include "../core/core.h"

namespace yjj {
	class vec2f {
	public:
		vec2f() noexcept;
		explicit vec2f(const POINT& p);
		vec2f(const vec2f& p);
		vec2f(const float x, const float y);
		virtual ~vec2f() noexcept;

		vec2f& operator=(const vec2f& p);

		bool operator==(const vec2f& p) const;

		vec2f& operator+(const vec2f& p);
		vec2f& operator-(const vec2f& p);
		vec2f& operator*(const vec2f& p);
		vec2f& operator/(const vec2f& p);
		vec2f& operator+(const float val);
		vec2f& operator-(const float val);
		vec2f& operator*(const float val);
		vec2f& operator/(const float val);

		void sum(const vec2f& p);
		void sub(const vec2f& p);
		void mul(const vec2f& p);
		void div(const vec2f& p);
		void sum(const float val);
		void sub(const float val);
		void mul(const float val);
		void div(const float val);


		float dot(const vec2f& p) const;
		float distance_sq(const vec2f& p) const;
		float distance(const vec2f& p) const;
		float ccw(const vec2f& p) const;
		float reciprocal(const float val) const;	//开荐
		const vec2f reciprocal() const;	//开荐
		const vec2f& normalize(const vec2f& p);

		float x() const;
		float y() const;
		void set(const vec2f& p);
		void set_x(const float x);
		void set_y(const float y);

	private:
		float x_ = 0;
		float y_ = 0;
	};



	class vec3f {
	public:
		vec3f() noexcept;
		explicit vec3f(const POINT& p);
		vec3f(const vec3f& p);
		vec3f(const float x, const float y, const float z);
		virtual ~vec3f() noexcept;

		vec3f& operator=(const vec3f& p);

		bool operator==(const vec3f& p) const;

		vec3f& operator+(const vec3f& p);
		vec3f& operator-(const vec3f& p);
		vec3f& operator*(const vec3f& p);
		vec3f& operator/(const vec3f& p);
		vec3f& operator+(const float val);
		vec3f& operator-(const float val);
		vec3f& operator*(const float val);
		vec3f& operator/(const float val);

		void sum(const vec3f& p);
		void sub(const vec3f& p);
		void mul(const vec3f& p);
		void div(const vec3f& p);
		void sum(const float val);
		void sub(const float val);
		void mul(const float val);
		void div(const float val);


		float dot(const vec3f& p) const;
		float distance_sq(const vec3f& p) const;
		float distance(const vec3f& p) const;
		float ccw(const vec3f& p) const;
		float reciprocal(const float val) const;	//开荐
		const vec3f reciprocal() const;	//开荐
		const vec3f& normalize(const vec3f& p);

		float x() const;
		float y() const;
		float z() const;
		void set(const vec3f& p);
		void set_x(const float x);
		void set_y(const float y);
		void set_z(const float z);

	private:
		float x_ = 0;
		float y_ = 0;
		float z_ = 0;
	};
}