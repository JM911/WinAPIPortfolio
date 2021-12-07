#include "Core.h"
#include "Core/Timer.h"
#include "Scene/SceneManager.h"

DEFINITION_SINGLE(Core)
bool Core::m_bLoop = true;

LRESULT Core::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
		EndPaint(hWnd, &ps);
	}
		break;
	case WM_DESTROY:
		m_bLoop = false;
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

Core::Core()
{
}

Core::~Core()
{
	// TODO: 각종 싱글턴 DESTROY_SINGLE 해주기
	DESTROY_SINGLE(Timer);
	DESTROY_SINGLE(SceneManager);

	ReleaseDC(m_hWnd, m_hDC);
}

BOOL Core::Create()
{
	m_hWnd = CreateWindowW(L"WinAPIGame", L"GameTitle", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
		nullptr, nullptr, m_hInst, nullptr);

	if (!m_hWnd)
		return FALSE;

	RECT rc = { 0, 0, (LONG)m_tRS.iW, (LONG)m_tRS.iH };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	SetWindowPos(m_hWnd, HWND_TOPMOST, 400, 100, rc.right - rc.left, rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return TRUE;
}

ATOM Core::MyRegisterClass()
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = Core::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInst;
	wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL; // MAKEINTRESOURCEW(IDC_WINAPIGAME);
	wcex.lpszClassName = L"WinAPIGame";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

	return RegisterClassExW(&wcex);
}

bool Core::Init(HINSTANCE hInst)
{
	m_hInst = hInst;

	MyRegisterClass();

	// 해상도 설정
	m_tRS.iW = 1280;
	m_tRS.iH = 720;

	Create();

	m_hDC = GetDC(m_hWnd);

	// TODO: 각종 싱글턴 Init

	// 타이머 초기화
	if (!GET_SINGLE(Timer)->Init(m_hWnd))
		return false;

	// 씬매니저 초기화
	if (!GET_SINGLE(SceneManager)->Init())
		return false;

	return TRUE;
}

int Core::Run()
{
	MSG msg;

	while (m_bLoop)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		else
		{
			Logic();
		}
	}

	return (int)msg.wParam;
}

void Core::Logic()
{
	GET_SINGLE(Timer)->Update();

	float fDeltaTime = GET_SINGLE(Timer)->GetDeltaTime();

	// TODO: 씬이 바뀔때 Update와 LateUpdate의 return 처리
	Input(fDeltaTime);
	Update(fDeltaTime);
	LateUpdate(fDeltaTime);
	Collision(fDeltaTime);
	Render(fDeltaTime);
}

void Core::Input(float fDeltaTime)
{
	// TODO: Input 클래스의 Update & SceneManager, Camera 클래스의 Input 실행
	GET_SINGLE(SceneManager)->Input(fDeltaTime);
}

int Core::Update(float fDeltaTime)
{
	// TODO: SceneManager, Camera 클래스의 Update 실행
	GET_SINGLE(SceneManager)->Update(fDeltaTime);
	return 0;
}

int Core::LateUpdate(float fDeltaTime)
{
	// TODO: SceneManager 클래스의 LateUpdate 실행
	GET_SINGLE(SceneManager)->LateUpdate(fDeltaTime);
	return 0;
}

void Core::Collision(float fDeltaTime)
{
	// TODO: SceneManager, CollisionManager 클래스의 Collision 실행
	GET_SINGLE(SceneManager)->Collision(fDeltaTime);
}

void Core::Render(float fDeltaTime)
{
	// TODO: 더블버퍼링 적용(ResourceManager, SceneManager)
	// TODO: SceneManager의 Render(DC값은 더블버퍼링 적용 전은 m_hDC, 적용 후는 백버퍼의 DC)

	// 정상적인 Render 흐름: 코어->씬매니저->개별씬->개별레이어->개별오브젝트 (이후 오브젝트에서 직접 그림)
	GET_SINGLE(SceneManager)->Render(m_hDC, fDeltaTime);
}

