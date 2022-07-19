#pragma once
#include "resource.h"
#include "../Core/core/core.h"


namespace yjj {
	class main {
	public:
		// singleton
		static main& get() noexcept;

		// hWnd, hinstance를 전역변수 대신 사용하기 위함.
		HWND hwnd() const noexcept;
		HINSTANCE hinstance() const noexcept;
		RECT client_rect() const noexcept;

		void set_hwnd(HWND hWnd) noexcept;
		void set_hinstance(HINSTANCE hInstance) noexcept;
		void set_client_rect(RECT rect) noexcept;

		RECT client_rect_;

	protected:
		//main() = default;
		//~main() { /* do nothing */ }

	private:
		void* handle_window_;
		void* handle_instance_;
	};
}

