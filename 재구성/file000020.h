#include "application.h"
#include "application_delegates.h"
#include "../win32helper/windows_with_macro.h"
#include "../win32gdi/device_context.h"
#include <zlog/zlog.h>

using namespace zee;

#ifdef UNICODE
	#define ZEE_WINMAIN_NAME wWinMain
#else
	#define ZEE_WINMAIN_NAME WinMain
#endif

class application_win32 : public application {
	friend application& application::get() noexcept;
	friend int
#if defined(_M_CEE_PURE)
		__clrcall
#else
		WINAPI
#endif
		ZEE_WINMAIN_NAME(
			_In_ HINSTANCE hInstance,
			_In_opt_ HINSTANCE hPrevInstance,
			_In_ TCHAR* lpCmdLine,
			_In_ int nShowCmd
		);

	friend LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

public:

	using application::app_config_;
	using application::config_;
	using application::is_started_;

	application_win32() {

	}
};

static std::unique_ptr<application_win32> app_inst;

static void create_app_inst() {
	if (!app_inst) {
		app_inst = std::unique_ptr<application_win32>(new application_win32);
	}
	}

application& application::get() noexcept {
	create_app_inst();
	return *app_inst;
}


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int
#if defined(_M_CEE_PURE)
__clrcall
#else
WINAPI
#endif
ZEE_WINMAIN_NAME(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ TCHAR* lpCmdLine,
	_In_ int nShowCmd
)
{
	create_app_inst();
	const application::config_data& app_config_data = application::get().config();
	
	app_inst->instance_handle_ = hInstance;
	WNDCLASS WndClass;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.lpszClassName = app_config_data.app_name.c_str();
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WNDCLASSEX dd;
	RegisterClass(&WndClass);

	app_inst->window_handle_ = 
	CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		app_config_data.app_name.c_str(),
		app_config_data.app_name.c_str(),
		WS_OVERLAPPEDWINDOW ,
		0, 0, 0, 0,
		NULL, (HMENU)NULL, app_inst->instance_handle<HINSTANCE>(), NULL
	);
	
	WINDOWPLACEMENT pl;
	memset(&pl, 0, sizeof(pl));

	shape::recti rc;
	rc.data[1] = app_config_data.window_size;
	rc += app_config_data.window_position;

	pl.length = sizeof(pl);
	pl.showCmd = SW_NORMAL;
	pl.rcNormalPosition.left   = rc.get_left  <LONG>();
	pl.rcNormalPosition.top    = rc.get_top   <LONG>();
	pl.rcNormalPosition.right  = rc.get_right <LONG>();
	pl.rcNormalPosition.bottom = rc.get_bottom<LONG>();

	SetWindowPlacement(app_inst->window_handle<HWND>(), &pl);

	int d = 0;
	MSG Message;
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	app_inst->app_config_().save();
	app_inst.reset();
	return Message.wParam;
}





//이하 왼쪽 값이 오른쪽 값을 포함 등등 할 경우
//점 vs 선
const shape::collide_type intersect(const math::vec2f& begin, const math::vec2f& end, const math::vec2f& pt) noexcept {	//접점찾기.
	if (pt.x >= begin.x && pt.x <= end.x
		&& pt.y >= begin.y && pt.y <= end.y) {
		return shape::collide_type::intersect;
	}
	return shape::collide_type::none;
}
//점 vs 사각형
const shape::collide_type intersect(const shape::rectf& rect, const math::vec2f& pt) noexcept {
	if ((pt.x >= rect.left && pt.x <= rect.right)
		&& (pt.y <= rect.bottom && pt.y >= rect.top)) {
		return shape::collide_type::intersect;
	}
	return shape::collide_type::none;
}
//점 vs 원형
const shape::collide_type intersect(const shape::circlef& circle, const math::vec2f& pt) noexcept {
	if (circle.origin.distance_sq(pt) <= circle.radius * circle.radius) {
		return shape::collide_type::intersect;
	}
	return shape::collide_type::none;
}
//선 vs 선 1. 외적 벡터 이용 방법
const int comparator(const math::vec2f& l, const math::vec2f& r) {
	//operator< > 함수 필요
	int ret;
	if (l.x == r.x) {
		ret = (l.y <= r.y);
	}
	else {
		ret = (l.x <= r.x);
	}
	return ret;
}
void swap(math::vec2f& l, math::vec2f& r) {
	math::vec2f tmp = l;
	l = r;
	r = tmp;
}
const shape::collide_type intersect_with_vector(math::vec2f begin1, math::vec2f end1, math::vec2f begin2, math::vec2f end2) noexcept {
	//외적 양수 반시계, 외적 음수 시계, 외적 0 평행		==> 좌표계가 y축반전이라 반대인듯
	//(x1, y1) 외적 (x2, y2) == (x1*y2) - (x2*y1).	
	//각 선분의 begin에서 다른 선분의 begin까지, end까지 외적이 하나는 양수, 하나는 음수로 나와야 함. 다른 선의 begin도 반복.

	//두 선분이 한 직선 위에 있거나, 끝점이 겹치는 경우
	if (begin1.ccw(begin2) * begin1.ccw(end2) == 0 && begin2.ccw(begin1) * begin2.ccw(end1) == 0) {
		//공식 참고. 원리 이해는 못함
		if (comparator(end1, begin1)) {
			swap(begin1, end1);
		}
		if (comparator(end2, begin2)) {
			swap(begin2, end2);
		}
		//포함
		if (comparator(begin2, end1) && comparator(begin1, end2)) {
			//완전 포함
			if (begin1.x <= begin2.x && begin1.y <= begin2.y && end1.x >= end2.x && end1.y >= end2.y) {	//operator < > 필요
				return shape::collide_type::contain;	//포함된다고 정의
			}
			return shape::collide_type::intersect;
		}
	}
	//중간점이 겹치는 경우
	else if (begin1.ccw(begin2) * begin1.ccw(end2) <= 0 && begin2.ccw(begin1) * begin2.ccw(end1) <= 0) {
		return shape::collide_type::intersect;
	}
	return shape::collide_type::none;
}
//선 vs 선 2.1. 방정식 pt대입 버전 
const shape::collide_type intersect(const math::vec2f& begin1, const math::vec2f& end1, const math::vec2f& begin2, const math::vec2f& end2, math::vec2f& out_pt) noexcept {
	float t;
	float s;
	//직선의 방정식 공식 참고 1
	float under = (end2.y - begin2.y) * (end1.x - begin1.x) - (end2.x - begin2.x) * (end1.y - begin1.y);
	if (under == 0) {
		//완전 내접: 좌변 선이 우변 선을 완전히 포함할 경우
		if (begin1.x <= begin2.x && begin1.y <= begin2.y && end1.x >= end2.x && end1.y >= end2.y) {	//operator < > 필요
			return shape::collide_type::contain;	//포함된다고 정의
		}
		//일부 내접
		else if (begin1.x <= begin2.x && end1.x >= begin1.x) {
			return shape::collide_type::intersect;
		}
		//평행, 만나지 않음
		else {
			return shape::collide_type::none;
		}
	}
	//직선의 방정식 공식 참고 2
	float t_ = (end2.x - begin2.x) * (begin1.y - begin2.y) - (end2.y - begin2.y) * (begin1.x - begin2.x);
	float s_ = (end1.x - begin1.x) * (begin1.y - begin2.y) - (end1.y - begin1.y) * (begin1.x - begin2.x);
	t = t_ / under;
	s = s_ / under;
	//공식에선 t와 s가 0과 1 사이여야 교차 판단.
	if (t < 0.0 || t > 1.0 || s < 0.0 || s > 1.0) {
		return shape::collide_type::none;
	}
	//교차
	out_pt = begin1 + t * (end1 - begin1);
	return shape::collide_type::intersect;
}
//선 vs 선. 2.2. 방정식 pt대입 버전 활용
const shape::collide_type intersect(const math::vec2f& begin1, const math::vec2f& end1, const math::vec2f& begin2, const math::vec2f& end2) noexcept {
	math::vec2f tmp = { -10000, -10000 };	//교차점에 의미 없는 값 선 세팅
	return intersect(begin1, end1, begin2, end2, tmp);
}

//선 vs 사각형 (사각형이 선을 포함하는가)
const shape::collide_type intersect(const shape::rectf rect, const math::vec2f begin, const math::vec2f end) noexcept {
	math::vec2f lt = { rect.left, rect.top };
	math::vec2f lb = { rect.left, rect.bottom };
	math::vec2f rt = { rect.right, rect.top };
	math::vec2f rb = { rect.right, rect.bottom };

	if (intersect(rect, begin) == shape::collide_type::intersect
		&& intersect(rect, end) == shape::collide_type::intersect) {
		return shape::collide_type::contain;
	}
	else if (intersect(begin, end, lt, lb) == shape::collide_type::intersect
		|| intersect(begin, end, lb, rb) == shape::collide_type::intersect
		|| intersect(begin, end, rb, rt) == shape::collide_type::intersect
		|| intersect(begin, end, rt, lt) == shape::collide_type::intersect) {
		return shape::collide_type::intersect;
	}
	return shape::collide_type::none;
}
//선 vs 원형 (원형이 선을 포함하는가)
const shape::collide_type intersect(const shape::circlef& circle, const math::vec2f& begin, const math::vec2f& end) noexcept {
	//이하 코드는 구글링 후 조건만 좀 변경함.
	const math::vec2f& origin_to_begin = begin - circle.origin;
	const math::vec2f& origin_to_end = end - circle.origin;
	float c_begin = origin_to_begin.dot(origin_to_begin) - circle.radius * circle.radius;
	float c_end = origin_to_end.dot(origin_to_end) - circle.radius * circle.radius;
	
	//선분의 시작점부터 구의 중심까지의 거리가 구의 반지름보다 크지 않다면,
	//선분의 시작점이 구의 안에 있으므로 교차함.
	//선분의 시작점도, 끝점도 구 안에 있다면 포함
	if (c_begin <= 0.0f && c_end <= 0.0f) {
		return shape::collide_type::contain;
	}
	else if (c_begin <= 0.0f || c_end <= 0.0f) {
		return shape::collide_type::intersect;
	}

	const math::vec2f dir = end - begin;
	float length = dir.length();
	if (length == 0.0f) {
		return shape::collide_type::none;
	}
	const math::vec2f normalized_dir = dir / length;
	float b_prime = origin_to_begin.dot(normalized_dir);

	//선분의 시작점이 구의 밖에 있고, 구의 중심에서 선분의 시작점을 향하는 벡터와 선분의 방향
	//벡터가 이루는 각이 90도 미만이라면 교차하지 않음
	if (b_prime > 0.0f) {
		return shape::collide_type::none;
	}

	//원래는 b' * b' - a * c를 사용해야 함. 그런데 선분의 방향 벡터가 단위 벡터면,
	//a는 normalized_dir.dot(normalized_dir) = 1
	//이므로, a를 생략 가능.
	float square_root_of_discriminant = sqrt(b_prime * b_prime - c_begin);	//discriminant == 판별식

	float t1 = -b_prime + square_root_of_discriminant;
	if (t1 >= 0.0f && t1 <= length) {
		return shape::collide_type::intersect;
	}
	float t2 = -b_prime + square_root_of_discriminant;
	if (t2 >= 0.0f && t2 <= length) {
		return shape::collide_type::intersect;
	}
	return shape::collide_type::none;
}
const shape::collide_type intersect2(const shape::circlef& circle, const math::vec2f& begin, const math::vec2f& end) noexcept {
	float d_cb = circle.origin.distance(begin);	//선분 시작점과 원 중심 사이 거리
	float d_ce = circle.origin.distance(end);
	//포함
	if (d_ce < circle.radius && d_cb < circle.radius) {
		return shape::collide_type::contain;
	}
	//교차: 선분 한 점이 원 안에
	else if ((d_cb < circle.radius && d_ce > circle.radius) || (d_cb > circle.radius && d_ce < circle.radius)) {
		return shape::collide_type::intersect;
	}
	else {
		return shape::collide_type::none;
	}
}
//사각형 vs 사각형
const shape::collide_type intersect(const shape::rectf& rect1, const shape::rectf& rect2) {
	const shape::rectf collision_rect = {
		math::max(rect1.get_left(), rect2.get_left()),
		math::max(rect1.get_top(), rect2.get_top()),
		math::min(rect1.get_right(), rect2.get_right()),
		math::min(rect1.get_bottom(), rect2.get_bottom())
	};
	if (collision_rect.width() != 0 || collision_rect.height() != 0) {	//collision_rect는 충돌되는 범위
		if (collision_rect == rect1 || collision_rect == rect2) {
			return shape::collide_type::contain;
		}
		//contain 아닐 때 조건으로 변경
		else if (!(rect1.get_right() < rect2.get_left()
			|| rect1.get_left() > rect2.get_right()
			|| rect1.get_bottom() < rect2.get_top()
			|| rect1.get_top() > rect2.get_bottom()
			)) {
			return shape::collide_type::intersect;
		}
	}
	return shape::collide_type::none;
}
//원형 vs 원형
const shape::collide_type intersect(const shape::circlef& circle1, const shape::circlef& circle2) {
	const float rad_minus = math::abs(circle1.radius - circle2.radius);
	const float rad_plus = circle1.radius + circle2.radius;
	const float dist_sq = circle1.origin.distance_sq(circle2.origin);
	//1 두 점 접, 2 한 점 외접, 3 한 점 내접
	if (dist_sq >= rad_minus * rad_minus && dist_sq <= rad_plus * rad_plus) {
		return shape::collide_type::intersect;
	}
	//4 만나지 않는 경우
	if (dist_sq > rad_plus * rad_plus) {
		return shape::collide_type::none;
	}
	//5 작은 원이 큰 원 안에 있으면서 만나지 않는 경우, 큰 원이 매개변수 좌측이면 포함, 아니면 none
	if (dist_sq < rad_minus * rad_minus && circle1.radius > circle2.radius) {
		return shape::collide_type::contain;
	}
	//6 두 원의 중심이 같고 반지름이 다른 경우, 큰 원이 매개변수 좌측이면 포함, 아니면 none
	if (dist_sq == 0 && circle1.radius > circle2.radius) {
		return shape::collide_type::contain;
	}
	return shape::collide_type::none;
}
//사각형 vs 원형
const shape::collide_type intersect(const shape::rectf& rect, const shape::circlef& circle) {
	math::vec2f lt = { rect.left, rect.top };
	math::vec2f lb = { rect.left, rect.bottom };
	math::vec2f rt = { rect.right, rect.top };
	math::vec2f rb = { rect.right, rect.bottom };
	//교차: 네 선 중 하나라도 겹침
	if (intersect(circle, lt, lb) == shape::collide_type::intersect
		|| intersect(circle, lb, rb) == shape::collide_type::intersect
		|| intersect(circle, rb, rt) == shape::collide_type::intersect
		|| intersect(circle, rt, lt) == shape::collide_type::intersect) {
		return shape::collide_type::intersect;
	}
	//포함
	else if (circle.origin.x > rect.left && circle.origin.x < rect.right
		&& circle.origin.y > rect.top && circle.origin.y < rect.bottom
		&& circle.radius * 2 <= rect.width() && circle.radius * 2 <= rect.height()) {
		return shape::collide_type::contain;
	}
	return shape::collide_type::none;
}
//원형 vs 사각형
const shape::collide_type intersect(const shape::circlef& circle, const shape::rectf& rect) {
	math::vec2f lt = { rect.left, rect.top };
	math::vec2f lb = { rect.left, rect.bottom };
	math::vec2f rt = { rect.right, rect.top };
	math::vec2f rb = { rect.right, rect.bottom };
	//교차: 네 선 중 하나라도 겹침
	if (intersect(circle, lt, lb) == shape::collide_type::intersect
		|| intersect(circle, lb, rb) == shape::collide_type::intersect
		|| intersect(circle, rb, rt) == shape::collide_type::intersect
		|| intersect(circle, rt, lt) == shape::collide_type::intersect) {
		return shape::collide_type::intersect;
	}
	//포함 : 네 선 모두 포함
	else if (intersect(circle, lt, lb) == shape::collide_type::contain
		&& intersect(circle, lb, rb) == shape::collide_type::contain
		&& intersect(circle, rb, rt) == shape::collide_type::contain
		&& intersect(circle, rt, lt) == shape::collide_type::contain) {
		return shape::collide_type::contain;
	}
	//아래 코드도 작동하지만, 이미 작성한 선 vs 원형 코드 활용
	/*
	else if (rect.left > circle.origin.x - circle.radius
		&& rect.right < circle.origin.x + circle.radius
		&& rect.bottom < circle.origin.x + circle.radius
		&& rect.top > circle.origin.x - circle.radius) {
		return shape::collide_type::contain;
	}
	*/
	return shape::collide_type::none;
}






LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	//https://docs.microsoft.com/en-us/windows/win32/winmsg/window-notifications
	static math::vec2i mouse_position;
	switch (iMessage) {
	//https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-move
	case WM_MOVE:
	{
		auto& position = app_inst->config_().window_position;
		position.x = (int32)(short)LOWORD(lParam);   // horizontal position 
		position.y = (int32)(short)HIWORD(lParam);   // vertical position
		return 0;
	}
	case WM_MOUSEMOVE:
	{
		mouse_position.x = (int32)(short)LOWORD(lParam);
		mouse_position.y = (int32)(short)HIWORD(lParam);
		//ZEE_LOG(normal, TEXT("app"), TEXT("mouse moved [%s]"), to_tstring(mouse_position).c_str());
		//마우스 이동.
		return 0;
	}

	case WM_LBUTTONDOWN: //마우스 클릭
	{
		InvalidateRect(hWnd, nullptr, TRUE);
		return 0;
	}
	case WM_CREATE:
	{
		app_inst->is_started_ = true;
		application_delegates::on_started().broadcast(application::get());
		win32gdi::device_context_auto temp_dc(hWnd, win32gdi::device_context_auto_type::temp);

		return 0;
	}
	case WM_SIZE:
	{
		auto& app = application::get();
		int d = 0;
		return 0;
	}
	case WM_CHAR:
	{
		InvalidateRect(hWnd, NULL, FALSE);
		return 0;
	}
	case WM_PAINT:
	{
		/*
		//여러가지 함수들을 또 래핑해놨는데 temp_dc.
		//ZEE_LOG(normal, TEXT("paint"), TEXT("log test. %s %d"), TEXT("test"), 10);

		//이런 DeviceContext요놈은 거기서도 gdi (그래픽 디바이스 인터페이스)에 속해있는 핸들인데
		//간단하게 말해서 그림그리게 도와주는 객체임.
		//래핑을 해서 이렇게 귀찮게 뭐 지워야되고 하는 그런 부분은 없앴음. 굿
		//세팅
		//cc.origin = mouse_position; //+application::get().app_config().data().window_size / 2;
		temp_dc.ellipse(300, 300, 600, 900);//타원
		*/
		/*
		//디버그
		win32gdi::device_context_auto temp_dc(hWnd, win32gdi::device_context_auto_type::paint);
		
		shape::rectf rc1(100, 100, 200, 200);
		shape::rectf rc2(200, 200, 250, 250);
		//rc1.data[1] = mouse_position;
		temp_dc.rectangle(rc1);
		temp_dc.rectangle(rc2);

		shape::circlef cc1;
		shape::circlef cc2;
		cc1.origin = mouse_position;
		//cc1.origin = { 500, 500 };
		cc1.radius = 200;
		cc2.origin = { 500, 500 };
		cc2.radius = 50;
		temp_dc.circle(cc1);
		temp_dc.circle(cc2);
		
		//사각형 vs 사각형
		if (intersect(rc1, rc2) == shape::collide_type::intersect) {
			ZEE_LOG(normal, TEXT("paint"), TEXT("1-- rc1 inter rc2"));
		}
		if (intersect(rc1, rc2) == shape::collide_type::contain) {
			ZEE_LOG(normal, TEXT("paint"), TEXT("2-- rc1 con rc2"));
		}
		//원형 vs 원형
		if (intersect(cc1, cc2) == shape::collide_type::intersect) {
			ZEE_LOG(normal, TEXT("paint"), TEXT("3-- cc1 inter cc2"));
		}
		if (intersect(cc1, cc2) == shape::collide_type::contain) {
			ZEE_LOG(normal, TEXT("paint"), TEXT("4-- cc1 con cc2"));
		}
		//사각형 vs 원형
		if (intersect(rc1, cc1) == shape::collide_type::intersect) {
			ZEE_LOG(normal, TEXT("paint"), TEXT("5-- rc1 inter cc1"));
		}
		if (intersect(rc1, cc1) == shape::collide_type::contain) {
			ZEE_LOG(normal, TEXT("paint"), TEXT("6-- rc1 con cc1"));
		}
		//원형 vs 사각형
		if (intersect(cc1, rc1) == shape::collide_type::intersect) {
			ZEE_LOG(normal, TEXT("paint"), TEXT("7-- cc1 inter rc1"));
		}
		if (intersect(cc1, rc1) == shape::collide_type::contain) {
			ZEE_LOG(normal, TEXT("paint"), TEXT("8-- cc1 con rc1"));
		}
		*/

		return 0;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}


