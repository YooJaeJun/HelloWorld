#include "main.h"
#include "game.h"
#include "image/frame_image.h"
#include "math/vec.h"
//#include "object/monster.h"

namespace yjj {
	game::game() {
		collider_ptr = std::make_shared<collider>();
	}
	game::~game() {
	}

	void game::init() {
		set_timer((int)c_var::timer_index_game,
			(int)c_var::timer_cycle);

		init_game();
	}

	void game::load(HDC dest_dc) {
		frame_image::get().load_frame_image(dest_dc, (int)c_var::index_background,
			TEXT("/assets/back.bmp"),
			coords[(int)ecoords::back_size]);

		frame_image::get().load_frame_image(dest_dc, (int)c_var::index_dig,
			TEXT("/assets/dig.bmp"),
			coords[(int)ecoords::dig_size]);

		frame_image::get().load_frame_image(dest_dc, (int)c_var::index_monster_spawn,
			TEXT("/assets/monster_spawn.bmp"),
			coords[(int)ecoords::monster_spawn_size]);

		frame_image::get().load_frame_image(dest_dc, (int)c_var::index_monster_die,
			TEXT("/assets/monster_die.bmp"),
			coords[(int)ecoords::monster_die_size]);
	}

	void game::release() {
		kill_timer((int)c_var::timer_index_game);
		kill_timer((int)c_var::timer_index_monster1);
		kill_timer((int)c_var::timer_index_monster2);
		PostQuitMessage(0);
	}

	void game::update(const WPARAM wParam) {
		switch (wParam)
		{
		case 1:
			if (timer_ >= time_limit_) {
				go_to_end();
			}
			else {
				timer_++;
			}
			break;
		case 2:

			break;
		case 3:

			break;
		}
	}

	void game::mouse_btn_down(const vec2f mouse_pos) {
		intersect_monster(mouse_pos);
	}

	void game::key_down(const WPARAM wParam) {
		// �ƹ� Ű�� ������ ó��
		change_scene();
	}


	void game::render(HDC dest_dc) {
		// �׸��� ����
		// ����
		bitmap tmp_bmp;

		frame_image::get().bitblt(dest_dc, (int)c_var::index_background, {}, {});

		// Ÿ��Ʋ
		switch (game_state_) {
		case (int)game_state::title: {
			rectf tmp_rect(coords[(int)ecoords::title_ending_box_lt], coords[(int)ecoords::title_ending_box_rb]);
			tmp_bmp.rectangle(tmp_rect);
			tmp_bmp.text_out(coords[(int)ecoords::title_st], TEXT("| ���� �δ��� ��� ������ >_< |"));
			tmp_bmp.text_out(coords[(int)ecoords::title_st2], TEXT("��-------------------------------------------------��"));
			tmp_bmp.text_out(coords[(int)ecoords::title_st3], TEXT("��-------------------------------------------------��"));
			tmp_bmp.text_out(coords[(int)ecoords::title_st4], TEXT("---�ƹ� Ű�� ���� ����---"));
			tmp_bmp.text_out(coords[(int)ecoords::title_st5], TEXT("���� ��: ������"));
			break;
		}

		// ����
		case (int)game_state::ending: {
			rectf tmp_rect(coords[(int)ecoords::title_ending_box_lt], coords[(int)ecoords::title_ending_box_rb]);
			tmp_bmp.rectangle(tmp_rect);
			tmp_bmp.text_out(coords[(int)ecoords::ending_st], TEXT("�� ���߾��!"));
			tmp_bmp.text_out(coords[(int)ecoords::time_taken], TEXT("�ɸ� �ð�(��): "));
			tmp_bmp.text_out(coords[(int)ecoords::score_final], TEXT("����: "));
			tmp_bmp.text_out(coords[(int)ecoords::ending_st2], TEXT("---�ƹ� Ű�� ���� �����---"));
			//tmp_bmp.text_out(coords[(int)ecoords::time_taken_num], std::to_string((timer_));
			//tmp_bmp.text_out(coords[(int)ecoords::score_final_num], std::to_string(score_));
			break;
		}

		// �ΰ���
		case (int)game_state::ingame: {
			rectf tmp_rect(coords[(int)ecoords::title_ending_box_lt], coords[(int)ecoords::title_ending_box_rb]);
			tmp_bmp.rectangle(tmp_rect);
			tmp_bmp.text_out(coords[(int)ecoords::stage_st], TEXT("�������� : "));
			tmp_bmp.text_out(coords[(int)ecoords::time_limit_st], TEXT("���ѽð� : "));
			tmp_bmp.text_out(coords[(int)ecoords::kill_remain_clear_st], TEXT("Ŭ������� ���� óġ : "));
			tmp_bmp.text_out(coords[(int)ecoords::kill_remain_st], TEXT("���� �ܰ���� ���� óġ : "));
			tmp_bmp.text_out(coords[(int)ecoords::time_st], TEXT("�ð� : "));
			tmp_bmp.text_out(coords[(int)ecoords::score_st], TEXT("���� : "));
			tmp_bmp.text_out(coords[(int)ecoords::spawn_1_speed_st], TEXT("�ʴ� �δ���1 �� : "));
			tmp_bmp.text_out(coords[(int)ecoords::spawn_2_speed_st], TEXT("�ʴ� �δ���2 �� : "));

			for (int i = 0; i != (int)c_var::dig_num; i++) {
				frame_image::get().transparent(tmp_bmp.hdc(), (int)c_var::index_dig, coords[i * 2], {}, RGB(195, 195, 195));
			}

			//tmp_bmp.text_out(coords[(int)ecoords::stage_num], std::to_string(now_stage_));
			//tmp_bmp.text_out(coords[(int)ecoords::time_limit_num], std::to_string(time_limit_));
			//tmp_bmp.text_out(coords[(int)ecoords::kill_remain_num], std::to_string(kill_remain_));
			//tmp_bmp.text_out(coords[(int)ecoords::kill_remain_clear_num], std::to_string(kill_remain_clear_));
			//tmp_bmp.text_out(coords[(int)ecoords::time_num], std::to_string(timer_));
			//tmp_bmp.text_out(coords[(int)ecoords::score_num], std::to_string(score_));

			//�ʴ� �δ��� 1,2 �� ������ "�ٸ� ��ġ"�� ǥ���ϱ� ���� �Լ��� �� ��. 1000 / �ֱ�
			//tmp_bmp.text_out(coords[(int)ecoords::spawn_1_speed_num], std::to_string(1000 / spawn_cycle[0]));
			//tmp_bmp.text_out(coords[(int)ecoords::spawn_2_speed_num], std::to_string(1000 / spawn_cycle[1]));

			//���� �� ��Ʈ �ִ�
			for (auto& mon : monsters) {
				mon->render(tmp_bmp.hdc());
			}
			break;
		}

		}//switch


		// ������۸� �Ϸ�.
		frame_image::get().bitblt(dest_dc, 0, {}, {});
		//tmp_bmp.bit_blt(dest_dc, {}, { client_rectf_.right(), client_rectf_.bottom() });
	}



	void game::init_game() {
		game_state_ = (int)game_state::title;
		monsters.resize((int)c_var::spawn_max);
		spawn_cycle.resize((int)c_var::spawn_max);
		spawn_cycle[0] = (int)c_var::spawn_cycle_1;
		spawn_cycle[1] = (int)c_var::spawn_cycle_2;
		now_stage_ = 1;
		timer_ = 0;
		score_ = 0;
		kill_remain_ = kill_remain_;
		kill_remain_clear_ = kill_remain_clear_;
		time_limit_ = time_limit_;
		for (auto& mon : monsters) {
			monsters.pop_back();
		}
	}


	void game::change_scene() {
		switch (game_state_) {
		case (int)game_state::title: {
			set_timer((int)c_var::timer_index_monster1, spawn_cycle[0]);
			set_timer((int)c_var::timer_index_monster2, spawn_cycle[1]);
			game_state_ = (int)game_state::ingame;
			break;
		}
		case (int)game_state::ending: {
			game_state_ = (int)game_state::title;
		}

		}//switch
	}

	void game::intersect_monster(const vec2f& mouse_pos) {
		for (auto& mon : monsters) {
			if (collider_ptr->intersect(mon->hitbox(), mouse_pos) != collide_type::none) {
				mon->attacked();
				change_score_and_time();
			}
		}

	}

	void game::change_score_and_time() {
		score_++;
		kill_remain_--;
		kill_remain_clear_--;
		if (kill_remain_clear_ <= 0) {
			go_to_end();
		}
		else if (kill_remain_ <= 0) {
			now_stage_++;
			kill_remain_ = kill_remain_ * now_stage_;
			// �������� ��� �� : ���� ����Ŭ * ���
			for (int i = 0; i != (int)c_var::spawn_max; i++) {
				if (spawn_cycle[i] * (int)spawn_coef_ > 0) {
					spawn_cycle[i] *= (int)spawn_coef_;
				}
			}

			// ���� ���� �ð� �����ؼ� ����
			kill_timer((int)c_var::timer_index_monster1);
			kill_timer((int)c_var::timer_index_monster2);
			set_timer((int)c_var::timer_index_monster1, spawn_cycle[0]);
			set_timer((int)c_var::timer_index_monster2, spawn_cycle[1]);
		}
	}

	void game::go_to_end() {

		game_state_ = (int)game_state::ending;

		for (auto& mon : monsters) {
			mon->set_hitbox(-2000, -2000, -2000, -2000);
		}

		kill_timer((int)c_var::timer_index_game);
		kill_timer((int)c_var::timer_index_monster1);
		kill_timer((int)c_var::timer_index_monster2);
	}



	void game::set_timer(const int index, const int time_cycle) {
		SetTimer(main::get().hwnd(), index, time_cycle, nullptr);
	}
	void game::kill_timer(const int index) {
		KillTimer(main::get().hwnd(), index);
	}

}