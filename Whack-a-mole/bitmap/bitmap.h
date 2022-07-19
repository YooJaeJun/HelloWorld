#pragma once
#include <vector>
#include "../../Core/core/core.h"
#include "../../Core/math/vec.h"
#include "../../Core/shape/rect.h"
#include "../../Core/shape/circle.h"
#include "../../Core/math/matrix.h"

namespace yjj {
	class bitmap {
	public:
		// CreateCompatibleDC, SelectObject, DeleteDC
		bitmap() = default;
		bitmap(HDC hdc) noexcept;
		virtual ~bitmap() noexcept;

		// LoadImage
		void load(HDC dest_dc, const tstring& file_path, const vec2f& size);


		// BitBlt
		void bitblt(HDC dest_dc, const vec2f& dest_pos, const vec2f& src_pos);
		void bitblt(HDC dest_dc, const vec2f& dest_pos);

		// TransparentBlt
		void transparentblt(HDC dest_dc, const vec2f& dest_pos, const vec2f& src_pos, DWORD transparent_color);
		void transparentblt(HDC dest_dc, const vec2f& dest_pos, DWORD transparent_color);

		// GdiAlphaBlend
		static BLENDFUNCTION make_blend_func(const float alpha);
		void alphablend(HDC dest_dc, const vec2f& dest_pos, const vec2f& src_pos, const vec2f& src_size, const float alpha);
		void alphablend(HDC dest_dc, const vec2f& dest_pos, const float alpha);

		// PlgBlt
		void plgblt(HDC dest_dc, const vec2f& point, const float angle, const vec2f& src_pos, const vec2f& src_size);
		void plgblt(HDC dest_dc, const vec2f& point, const float angle, const vec2f& src_size);


		// TextOut
		void text_out(const vec2f& p, const tstring& str);

		// brush
		void rectangle(const rectf& rt);
		void circle(const circlef& c);
		void ellipse(int left, int top, int right, int bottom);

		// pen
		void move_to(const vec2f& dot);
		void line_to(const vec2f& line);


		bool is_valid(const HDC dest_dc);


		const HDC hdc() const;
		const HBITMAP bmp() const;
		const HBITMAP mbmp() const;
		const int width() const;
		const int height() const;

		void set_hdc(const HDC hdc);
		void set_bmp(const HBITMAP hbitmap);
		void set_mbmp(const HBITMAP hbitmap);
		void set_width(const int width);
		void set_height(const int height);


	private:
		HDC hdc_ = nullptr;
		HBITMAP bmp_ = nullptr, mbmp_ = nullptr;
		int width_ = 0, height_ = 0;
	};
}