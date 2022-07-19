#pragma once
#include "bitmap.h"
#include "../main.h"

namespace yjj {
	bitmap::bitmap(HDC hdc) noexcept {
		assert(hdc);
		set_hdc(CreateCompatibleDC(hdc));
	}

	bitmap::~bitmap() noexcept {
		if (hdc_) {
			if (bmp_) {
				SelectObject(hdc_, mbmp_);
				DeleteObject(bmp_);
				DeleteObject(hdc_);
			}
		}
	}

	void bitmap::load(HDC dest_dc, const tstring& file_path, const vec2f& size) {
		//assert(dest_dc);

		if (nullptr != bmp()) {
			DeleteObject(bmp_);
		}

		set_width((int)size.x());
		set_height((int)size.y());

		set_bmp((HBITMAP)LoadImage(
			main::get().hinstance(),
			file_path.c_str(),
			IMAGE_BITMAP,
			width(), height(),
			LR_DEFAULTSIZE | LR_DEFAULTCOLOR | LR_LOADFROMFILE));

		if (dest_dc) {
			set_hdc(CreateCompatibleDC(dest_dc));
			set_mbmp((HBITMAP)SelectObject(hdc_, bmp_));
		}
	}


	// BitBlt
	void bitmap::bitblt(HDC dest_dc, const vec2f& dest_pos, const vec2f& src_pos) {
		assert(is_valid(dest_dc) &&
			BitBlt(
			dest_dc,
			(int)dest_pos.x(), (int)dest_pos.y(),
			width(), height(),
			hdc(),
			(int)src_pos.x(), (int)src_pos.y(),
			SRCCOPY));
	}

	void bitmap::bitblt(HDC dest_dc, const vec2f& dest_pos) {
		bitblt(dest_dc, dest_pos, {});
	}


	// TransparentBlt
	void bitmap::transparentblt(HDC dest_dc, const vec2f& dest_pos, const vec2f& src_pos, DWORD transparent_color) {
		assert(is_valid(dest_dc) &&
			GdiTransparentBlt(
			dest_dc,
			(int)dest_pos.x(), (int)dest_pos.y(),
			width(), height(),
			hdc(),
			(int)src_pos.x(), (int)src_pos.y(),
			width(), height(),
			(UINT)transparent_color));
	}

	void bitmap::transparentblt(HDC dest_dc, const vec2f& dest_pos, DWORD transparent_color) {
		transparentblt(dest_dc, dest_pos, {}, transparent_color);
	}


	// GdiAlphaBlend
	BLENDFUNCTION bitmap::make_blend_func(const float alpha) {
		BLENDFUNCTION ret;
		ret.BlendOp = AC_SRC_OVER;
		ret.AlphaFormat = 0;	// AlphaFormat: 0이면 알파 채널 무시. AC_SRC_ALPHA면 알파 소스 사용.
		ret.BlendFlags = 0;
		ret.SourceConstantAlpha = (BYTE)(min(max(alpha, 0.0f), 1.0f));	//clamp
		return ret;
	}

	void bitmap::alphablend(HDC dest_dc, const vec2f& dest_pos, const vec2f& src_pos, const vec2f& src_size, const float alpha) {
		assert(is_valid(dest_dc) &&
			GdiAlphaBlend(
			dest_dc,
			(int)dest_pos.x(), (int)dest_pos.y(),
			width(), height(),
			hdc(),
			(int)src_pos.x(), (int)src_pos.y(),
			(int)src_size.x(), (int)src_size.y(),
			make_blend_func(alpha)));
	}

	void bitmap::alphablend(HDC dest_dc, const vec2f& dest_pos, const float alpha) {
		alphablend(dest_dc, dest_pos, {}, { static_cast<float>(width()), static_cast<float>(height()) }, alpha);
	}


	// PlgBlt
	void bitmap::plgblt(HDC dest_dc, const vec2f& point, const float angle, const vec2f& src_pos, const vec2f& src_size) {
		is_valid(dest_dc);
		// plg_blt
		std::vector<matrix3f> vm;
		std::vector<vec3f> vv3;
		// plg_blt는 회전할 점 3곳(좌상, 우상, 좌하)
		const std::vector<vec2f> vv = {
			{-src_size.x() / 2, -src_size.y() / 2},
			{src_size.x() / 2, -src_size.y() / 2},
			{-src_size.x() / 2, src_size.y() / 2}
		};

		for (int i = 0; i != 3; i++) {
			vm[i].rotate(angle, point.x(), point.y());	//회전행렬 적용
			vv3[i] = vm[i].mul(vv[i]);	//회전행렬 * 회전할 점
		}

		//타입 변환
		std::vector<POINT> v_point;
		for (int i = 0; i != 3; i++) {
			v_point.push_back({ static_cast<int>(vv3[i].x()), static_cast<int>(vv3[i].y()) });
		}

		assert(PlgBlt(
			dest_dc,
			v_point.data(),
			hdc(),
			(int)src_pos.x(), (int)src_pos.y(),
			(int)src_size.x(), (int)src_size.y(),
			0,
			0, 0));
	}

	void bitmap::plgblt(HDC dest_dc, const vec2f& point, const float angle, const vec2f& src_size) {
		plgblt(dest_dc, point, angle, {}, src_size);
	}



	void bitmap::text_out(const vec2f& p, const tstring& str) {
		assert(TextOut(
			hdc(),
			(int)p.x(),
			(int)p.y(),
			str.c_str(),
			(int)str.size() ));
	}

	void bitmap::rectangle(const rectf& rt) {
		assert(Rectangle(
			hdc(),
			(int)rt.left(),
			(int)rt.top(),
			(int)rt.right(),
			(int)rt.bottom()));
	}

	void bitmap::ellipse(int left, int top, int right, int bottom) {
		assert(Ellipse(hdc(), left, top, right, bottom));
	}

	void bitmap::circle(const circlef& c) {
		ellipse((int)c.origin().x() - (int)c.radius(),
			(int)c.origin().y() - (int)c.radius(),
			(int)c.origin().x() + (int)c.radius(),
			(int)c.origin().y() + (int)c.radius());
	}

	void bitmap::move_to(const vec2f& dot) {
		MoveToEx(hdc(), (int)dot.x(), (int)dot.y(), nullptr);
	}

	void bitmap::line_to(const vec2f& line) {
		LineTo(hdc(), (int)line.x(), (int)line.y());
	}



	bool bitmap::is_valid(const HDC dest_dc) {
		if (&hdc_ == &dest_dc) {
			return false;
		}
		if (nullptr == dest_dc) {
			return false;
		}
		if (nullptr == hdc()) {
			return false;
		}
		return true;
	}


	const HDC bitmap::hdc() const {
		return hdc_;
	}

	const HBITMAP bitmap::bmp() const {
		return bmp_;
	}
	const HBITMAP bitmap::mbmp() const {
		return mbmp_;
	}

	const int bitmap::width() const {
		return width_;
	}
	const int bitmap::height() const {
		return height_;
	}


	void bitmap::set_hdc(const HDC hdc) {
		hdc_ = hdc;
	}

	void bitmap::set_bmp(const HBITMAP hbitmap) {
		bmp_ = hbitmap;
	}
	void bitmap::set_mbmp(const HBITMAP hbitmap) {
		mbmp_ = hbitmap;
	}

	void bitmap::set_width(const int width) {
		width_ = width;
	}
	void bitmap::set_height(const int height) {
		height_ = height;
	}
}