
#pragma once
#include "core/core.h"
#include "bitmap/bitmap.h"
#include "shape/collider.h"
#include "object/monster.h"

namespace yjj {
	class monster;

	// 전역 상수 및 enum
	// 상수
	enum class c_var {
		// 게임 변수
		timer_cycle = 1000,	// 시간 표시
		spawn_cycle_1 = 1000,	// 몬1 최초 스폰 주기
		spawn_cycle_2 = 1500,	// 몬2 최초 스폰 주기
		time_limit = 50,	// 제한시간
		kill_remain = 3,	// 단계별 남은 처치 수
		kill_remain_clear = 36,	// 클리어까지 남은 처치 수
		dig_num = 6,		// 몬스터 구멍 개수
		spawn_max = 2,		// 동시 스폰 몬스터 수 (현재 고정)
		timer_index_game = 1,		// 게임 시간 타이머 인덱스 (1초 단위)
		timer_index_monster1 = 2,	// 몬스터1 스폰 타이머 인덱스
		timer_index_monster2 = 3,	// 몬스터2 스폰 타이머 인덱스
		// 이미지 index
		index_background = 0,
		index_dig = 1,
		index_monster_spawn = 2,
		index_monster_die = 3,
	};
	// 좌표
	enum class ecoords {
		// 스폰 위치
		lefttop, middletop, righttop,
		leftmiddle, middlemiddle, rightmiddle,
		dig_max,	// 랜덤범위에 쓰임
		// 타이틀
		title_st, title_st2, title_st3, title_st4, title_st5,
		title_ending_box_lt, title_ending_box_rb,
		// 인게임
		stagebox_lt, stagebox_rb,
		time_st, score_st, stage_st, time_limit_st,
		time_num, score_num, stage_num, time_limit_num,
		kill_remain_clear_st, kill_remain_st, spawn_1_speed_st, spawn_2_speed_st,
		kill_remain_clear_num, kill_remain_num, spawn_1_speed_num, spawn_2_speed_num,
		// 엔딩
		ending_st, ending_st2, time_taken, time_taken_num, score_final, score_final_num,
		// 이미지 사이즈
		back_size, dig_size, monster_spawn_size, monster_die_size,
		max
	};
	const vec2f coords[(int)ecoords::max] = {
		{100, 100}, {300, 100},	{500, 100},
		{100, 300},	{300, 300},	{500, 300},
		{0, 0},
		// 타이틀
		{240, 310}, {234, 290}, {234, 330}, {264, 360}, {294, 380},
		{220, 250}, {480, 450},
		// 인게임
		{230, 470}, {460, 650},
		{240, 480}, {240, 500}, {240, 520}, {240, 540},
		{296, 480}, {296, 500}, {326, 520}, {326, 540},
		{240, 560}, {240, 580}, {240, 600}, {240, 620},
		{410, 560}, {432, 580}, {370, 600}, {370, 620},
		// 엔딩
		{300, 300}, {262, 400}, {290, 340}, {400, 340}, {290, 360}, {340, 360},
		// 이미지 사이즈
		{720, 720}, {100, 100}, {100, 100}, {100, 100},
	};
	// 게임 상태
	enum class game_state {
		title,
		ingame,
		ending,
	};


	/// <summary>
	/// 메인게임 클래스
	/// </summary>
	class game {
	public:
		game();
		~game();

		void init();									// WM_CREATE
		void load(HDC dest_dc);							// WM_CREATE2
		void release();									// WM_DESTROY
		void update(const WPARAM wParam);				// WM_TIMER
		void mouse_btn_down(const vec2f mouse_pos);		// WM_LBUTTONDOWN
		void key_down(const WPARAM wParam);				// WM_KEYDOWN
		void render(HDC dc);							// WM_PAINT

		// 게임 변수들 초기화
		void init_game();
		// 몬스터 충돌
		void intersect_monster(const vec2f& mouse_pos);
		// 씬 전환
		void change_scene();
		// 두더쥐 사망 시 스테이지 변수 변동
		void change_score_and_time();
		// 게임 종료 시 (제한시간 종료, 두더쥐 처치수 만족)
		void go_to_end();


		// 타이머 쓰기 편하게 뺌
		void set_timer(const int index, const int time_cycle);
		void kill_timer(const int index);



	private:
		// 윈도우
		rectf client_rectf_{ 0,0,0,0 };
		float mouse_pos_ = 0;

		// 점수, 시간 등
		int game_state_ = 0;
		int timer_ = 0;
		int score_ = 0;
		int now_stage_ = 0;
		int time_limit_ = 0;
		int kill_remain_ = 0;
		int kill_remain_clear_ = 0;
		const float spawn_coef_ = 0.8f;	// 단계별 더 빠른 스폰 위함. 현재 스폰 주기 * 계수

		// 몬스터
		std::vector<std::shared_ptr<monster>> monsters;
		std::vector<int> spawn_cycle;
		std::shared_ptr<collider> collider_ptr;
		bitmap tmp_bmp;
	};
}