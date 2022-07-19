#include "monster.h"
#include "../../Core/core/random.h"
#include "../image/frame_image.h"

namespace yjj {
	//몬스터 함수
	monster::monster() noexcept {
	}	
	monster::~monster() noexcept {
	}


	void monster::spawn() {
		set_pos(rand_int(0, (int)c_var_monster::dig_num / 2 - 1));
		vec2f lt = coords_monster[pos()];
		vec2f rb = lt + coords_monster[(int)ecoords_monster::monster_spawn_size];
		set_hitbox(lt, rb);
		set_state((int)state::alive);
	}

	void monster::attacked() {
		if (state() == (int)state::alive) {
			set_state((int)state::die);
			//PlaySound("./assets/Hit_Hurt14.wav", nullptr, SND_ASYNC);
		}
	}

	//스폰, 어택 애니 호출
	void monster::render(HDC dest_dc) {
		switch (state())
		{
		case (int)state::alive:
			render_spawn(dest_dc);
			break;
		case (int)state::die:
			render_attacked(dest_dc);
			break;
		}
	}
	
	void monster::render_spawn(HDC dest_dc) const {
		frame_image::get().transparent(
			dest_dc,
			(int)c_var_monster::index_monster_spawn,
			coords_monster[pos()],
			{},
			RGB(195, 195, 195));
	}

	void monster::render_attacked(HDC dest_dc) const {
		frame_image::get().transparent(
			dest_dc,
			(int)c_var_monster::index_monster_die,
			coords_monster[pos()],
			{},
			RGB(195, 195, 195));
	}
	

	int monster::state() const {
		return state_;
	}

	int monster::pos() const {
		return pos_;
	}

	const rectf& monster::hitbox() const {
		return hitbox_;
	}

	void monster::set_state(const int state) {
		state_ = state;
	}

	void monster::set_pos(const int pos) {
		pos_ = pos;
	}

	void monster::set_hitbox(const rectf& rect) {
		hitbox_.set(rect);
	}

	void monster::set_hitbox(const vec2f& lt, const vec2f& rb) {
		hitbox_.set(lt, rb);
	}

	void monster::set_hitbox(const vec2f& lt, const vec2f& lb, const vec2f& rt, const vec2f& rb) {
		hitbox_.set(lt, lb, rt, rb);
	}

	void monster::set_hitbox(const float left, const float top, const float right, const float bottom) {
		hitbox_.set(left, top, right, bottom);
	}
}