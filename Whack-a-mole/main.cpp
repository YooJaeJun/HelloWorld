// Whack-a-mole.cpp : 애플리케이션에 대한 진입점을 정의합니다.
#include "main.h"
#include "../WinAPICore/math/vec.h"
#include "bitmap/bitmap.h"
#include "game.h"

using namespace yjj;


main& main::get() noexcept {
    static std::unique_ptr<main> main_inst;
    if (!main_inst) {
        main_inst = std::unique_ptr<main>(new main);
    }
    return *main_inst;
}

HWND main::hwnd() const noexcept {
    return (HWND)handle_window_;
}

HINSTANCE main::hinstance() const noexcept {
    return (HINSTANCE)handle_instance_;
}

RECT main::client_rect() const noexcept {
    return client_rect_;
}

void main::set_hwnd(HWND hWnd) noexcept {
    handle_window_ = hWnd;
}

void main::set_hinstance(HINSTANCE hInstance) noexcept {
    handle_instance_ = hInstance;
}

void main::set_client_rect(RECT rect) noexcept {
    client_rect_ = rect;
}



#define MAX_LOADSTRING 100

// 전역 변수:
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


//main game 객체
std::shared_ptr<game> game_inst = std::make_shared<game>();



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WHACKAMOLE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WHACKAMOLE));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            //InvalidateRect(msg.hwnd, nullptr, false);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WHACKAMOLE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WHACKAMOLE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   main::get().set_hinstance(hInstance); // 인스턴스 핸들을 전역 변수에 저장합니다.

   main::get().set_hwnd(CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr));

   if (!main::get().hwnd())
   {
      return FALSE;
   }

   ShowWindow(main::get().hwnd(), nCmdShow);
   UpdateWindow(main::get().hwnd());

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    GetClientRect(hWnd, &main::get().client_rect_);
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(main::get().hwnd(), &ps);
    HDC mem_dc;
    HBITMAP back_bit, old_back_bit;

    switch (message)
    {
    case WM_CREATE:
    {
        game_inst->init();
        game_inst->load(hdc);
        break;
    }
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(main::get().hinstance(), MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        break;
    }
    case WM_LBUTTONDOWN:
    {
        game_inst->mouse_btn_down({ (float)LOWORD(lParam), (float)HIWORD(lParam) });
        break;
    }
    case WM_KEYDOWN:
    {
        game_inst->key_down(wParam);

        switch (wParam)
        {
        case VK_ESCAPE:
            PostMessage(hWnd, WM_DESTROY, 0, 0);
            break;
        }
        break;
    }
    case WM_TIMER: {
        game_inst->update(wParam);
        break;
    }
    case WM_PAINT:
    {
        // 더블 버퍼링 시작 처리
        mem_dc = BeginPaint(hWnd, &ps);
        hdc = CreateCompatibleDC(mem_dc);
        back_bit = CreateCompatibleBitmap(mem_dc, main::get().client_rect().right, main::get().client_rect().bottom);
        old_back_bit = (HBITMAP)SelectObject(hdc, back_bit);
        PatBlt(hdc, 0, 0, main::get().client_rect().right, main::get().client_rect().bottom, BLACKNESS);
        PatBlt(hdc, 0, 0, 55, 25, BLACKNESS);
        bitmap b;
        b.load(hdc, TEXT("assets/dig.bmp"), { 100, 100 });
        b.bitblt(hdc, {});

        //game_inst->render(hdc);

            // 더블 버퍼링 끝 처리
        GetClientRect(hWnd, &main::get().client_rect_);
        BitBlt(mem_dc, 0, 0, 55, main::get().client_rect().bottom, hdc, 0, 0, SRCCOPY);
        SelectObject(hdc, old_back_bit);
        DeleteObject(back_bit);
        DeleteDC(hdc);
        EndPaint(hWnd, &ps);
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}



// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
