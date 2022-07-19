
#pragma once
#include "core/core.h"
#include "bitmap/bitmap.h"
#include "shape/collider.h"
#include "object/monster.h"

namespace yjj {
	class monster;

	// ���� ��� �� enum
	// ���
	enum class c_var {
		// ���� ����
		timer_cycle = 1000,	// �ð� ǥ��
		spawn_cycle_1 = 1000,	// ��1 ���� ���� �ֱ�
		spawn_cycle_2 = 1500,	// ��2 ���� ���� �ֱ�
		time_limit = 50,	// ���ѽð�
		kill_remain = 3,	// �ܰ躰 ���� óġ ��
		kill_remain_clear = 36,	// Ŭ������� ���� óġ ��
		dig_num = 6,		// ���� ���� ����
		spawn_max = 2,		// ���� ���� ���� �� (���� ����)
		timer_index_game = 1,		// ���� �ð� Ÿ�̸� �ε��� (1�� ����)
		timer_index_monster1 = 2,	// ����1 ���� Ÿ�̸� �ε���
		timer_index_monster2 = 3,	// ����2 ���� Ÿ�̸� �ε���
		// �̹��� index
		index_background = 0,
		index_dig = 1,
		index_monster_spawn = 2,
		index_monster_die = 3,
	};
	// ��ǥ
	enum class ecoords {
		// ���� ��ġ
		lefttop, middletop, righttop,
		leftmiddle, middlemiddle, rightmiddle,
		dig_max,	// ���������� ����
		// Ÿ��Ʋ
		title_st, title_st2, title_st3, title_st4, title_st5,
		title_ending_box_lt, title_ending_box_rb,
		// �ΰ���
		stagebox_lt, stagebox_rb,
		time_st, score_st, stage_st, time_limit_st,
		time_num, score_num, stage_num, time_limit_num,
		kill_remain_clear_st, kill_remain_st, spawn_1_speed_st, spawn_2_speed_st,
		kill_remain_clear_num, kill_remain_num, spawn_1_speed_num, spawn_2_speed_num,
		// ����
		ending_st, ending_st2, time_taken, time_taken_num, score_final, score_final_num,
		// �̹��� ������
		back_size, dig_size, monster_spawn_size, monster_die_size,
		max
	};
	const vec2f coords[(int)ecoords::max] = {
		{100, 100}, {300, 100},	{500, 100},
		{100, 300},	{300, 300},	{500, 300},
		{0, 0},
		// Ÿ��Ʋ
		{240, 310}, {234, 290}, {234, 330}, {264, 360}, {294, 380},
		{220, 250}, {480, 450},
		// �ΰ���
		{230, 470}, {460, 650},
		{240, 480}, {240, 500}, {240, 520}, {240, 540},
		{296, 480}, {296, 500}, {326, 520}, {326, 540},
		{240, 560}, {240, 580}, {240, 600}, {240, 620},
		{410, 560}, {432, 580}, {370, 600}, {370, 620},
		// ����
		{300, 300}, {262, 400}, {290, 340}, {400, 340}, {290, 360}, {340, 360},
		// �̹��� ������
		{720, 720}, {100, 100}, {100, 100}, {100, 100},
	};
	// ���� ����
	enum class game_state {
		title,
		ingame,
		ending,
	};


	/// <summary>
	/// ���ΰ��� Ŭ����
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

		// ���� ������ �ʱ�ȭ
		void init_game();
		// ���� �浹
		void intersect_monster(const vec2f& mouse_pos);
		// �� ��ȯ
		void change_scene();
		// �δ��� ��� �� �������� ���� ����
		void change_score_and_time();
		// ���� ���� �� (���ѽð� ����, �δ��� óġ�� ����)
		void go_to_end();


		// Ÿ�̸� ���� ���ϰ� ��
		void set_timer(const int index, const int time_cycle);
		void kill_timer(const int index);



	private:
		// ������
		rectf client_rectf_{ 0,0,0,0 };
		float mouse_pos_ = 0;

		// ����, �ð� ��
		int game_state_ = 0;
		int timer_ = 0;
		int score_ = 0;
		int now_stage_ = 0;
		int time_limit_ = 0;
		int kill_remain_ = 0;
		int kill_remain_clear_ = 0;
		const float spawn_coef_ = 0.8f;	// �ܰ躰 �� ���� ���� ����. ���� ���� �ֱ� * ���

		// ����
		std::vector<std::shared_ptr<monster>> monsters;
		std::vector<int> spawn_cycle;
		std::shared_ptr<collider> collider_ptr;
		bitmap tmp_bmp;
	};
}