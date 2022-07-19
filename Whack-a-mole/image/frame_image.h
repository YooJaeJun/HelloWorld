#pragma once
#include <vector>
#include "../../Core/core/core.h"
#include "../../Core/math/vec.h"
#include "../bitmap/bitmap.h"

namespace yjj {
	class frame_image {
	public:
		static frame_image& get();

		void load_frame_image(HDC dest_dc, const int index, const tstring& filename, const vec2f& frame_size);

		void bitblt(HDC dest_dc, const int index, const vec2f& dest_pos, const vec2f& src_pos);
		void transparent(HDC dest_dc, const int index, const vec2f& dest_pos, const vec2f& src_pos, DWORD transparent_color);
		void alphablend(HDC dest_dc, const int index, const vec2f& dest_pos, const vec2f& src_pos, DWORD transparent_color);

		/*
		void load_plg(const int index, const tstring& filename, const vec2f& frame_size);
		void plg(const vec2f& point, const int index, const float angle);
		void plg_transparent(HDC dest_dc, const int index, const vec2f& dest_pos, const vec2f& src_pos, DWORD transparent_color);
		*/

	private:
		frame_image() noexcept;
		frame_image(const frame_image&) = delete;
		frame_image& operator=(const frame_image&) = delete;

		std::vector<bitmap> bmps_back_;
		std::vector<bitmap> bmps_back_back_;
		std::vector<bitmap> bmps_;

		/// <summary>
		/// 이미지 개수
		/// </summary>
		const int image_num_ = 4;
	};
}