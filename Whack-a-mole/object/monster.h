#pragma once
#include <vector>
#include "../../Core/shape/rect.h"

namespace yjj {
	enum class state {
		none,
		spawn,
		alive,
		die
	};
	enum class c_var_monster {
		dig_num = 6,		// 두더지 구멍 개수
		// 이미지 index
		index_background = 0,
		index_dig = 1,
		index_monster_spawn = 2,
		index_monster_die = 3,
	};
	enum class ecoords_monster {
		lefttop, middletop, righttop,
		leftmiddle, middlemiddle, rightmiddle,
		dig_max,	// 랜덤범위에 쓰임
		// 이미지 사이즈
		monster_spawn_size, monster_die_size,
		coords_monster_max
	};
	const vec2f coords_monster[(int)ecoords_monster::coords_monster_max] = {
		{100, 100},	{300, 100},	{500, 100},
		{100, 300},	{300, 300},	{500, 300},
		{100, 100}, {100, 100},
	};



	class monster {
	public:
		monster() noexcept;
		virtual ~monster() noexcept;

		void spawn();
		void attacked();
		void render(HDC dest_dc);
		
		void render_spawn(HDC dest_dc) const;
		void render_attacked(HDC dest_dc) const;

		int state() const;
		int pos() const;
		const rectf& hitbox() const;

		void set_state(const int state);
		void set_pos(const int pos);
		void set_hitbox(const rectf& rect);
		void set_hitbox(const vec2f& lt, const vec2f& rb);
		void set_hitbox(const vec2f& lt, const vec2f& lb, const vec2f& rt, const vec2f& rb);
		void set_hitbox(const float left, const float top, const float right, const float bottom);


	private:
		int state_ = (int)state::none;
		int pos_ = 0;
		rectf hitbox_{ -2000, -2000, -2000, -2000 };
	};
}
