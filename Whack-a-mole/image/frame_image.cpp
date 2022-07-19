#include "frame_image.h"
#include <memory>

namespace yjj {

	frame_image& frame_image::get() {
		static std::unique_ptr<frame_image> inst;
		if (!inst) {
			inst = std::unique_ptr<frame_image>(new frame_image());
		}
		return *inst;
	}

	frame_image::frame_image() noexcept {
		bmps_.resize(image_num_);
		bmps_back_.resize(image_num_);
		bmps_back_back_.resize(image_num_);
	}

	//load
	void frame_image::load_frame_image(HDC dest_dc, const int index, const tstring& filename, const vec2f& frame_size) {
		bmps_[index].load(dest_dc, filename, frame_size);
	}

	//render
	void frame_image::bitblt(HDC dest_dc, const int index, const vec2f& dest_pos, const vec2f& src_pos) {
		bmps_[index].bitblt(dest_dc, dest_pos);
	}

	void frame_image::transparent(HDC dest_dc, const int index, const vec2f& dest_pos, const vec2f& src_pos, DWORD transparent_color) {
		bmps_[index].transparentblt(dest_dc, dest_pos, src_pos, transparent_color);
	}

	void frame_image::alphablend(HDC dest_dc, const int index, const vec2f& dest_pos, const vec2f& src_pos, DWORD transparent_color) {
		bmps_[index].transparentblt(bmps_back_[index].hdc(), dest_pos, src_pos, transparent_color);
		bmps_[index].alphablend(dest_dc, dest_pos, 0.5f);
	}


	//plg
	/*
	void frame_image::load_plg(const int index, const tstring& filename, const vec2f& frame_size) {
		images_[index].load_image(filename, frame_size);

		back_dcs[index].set_bitmap({
			//회전할 때 src_pos 밖의 이미지가 자꾸 침범해서 간격을 만듦
			360 * (sizes_[index].x() + sizes_[index].x() * 2),
			sizes_[index].y()
			});

		back_back_dcs[index].set_bitmap(sizes_[index]);
	}

	void frame_image::plg(const vec2f& point, const int index, const float angle) {
		images_[index].plg_blt(back_dcs[index], point, angle, sizes_[index]);
	}

	void frame_image::plg_transparent(HDC dest_dc, const int index, const vec2f& dest_pos, const vec2f& src_pos, DWORD transparent_color) {
		//검정 배경색 없애려고 + 전에 남은 이미지 없애려고 또 다른 백버퍼를 매번 클리어하고 사이즈 세팅하고 그려줌.
		back_back_dcs[index].clear();
		back_back_dcs[index].set_bitmap(sizes_[index]);

		back_dcs[index].transparent_blt(back_back_dcs[index], {}, sizes_[index], src_pos, sizes_[index], transparent_color);
		back_back_dcs[index].transparent_blt(dest_dc, dest_pos, sizes_[index], RGB(0, 0, 0));
	}
	*/
}