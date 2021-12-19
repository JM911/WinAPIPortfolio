#include "Core.h"
#include "Core/Timer.h"
#include "Scene/SceneManager.h"
#include "Core/CInput.h"
#include "Core/PathManager.h"
#include "Resources/ResourcesManager.h"
#include "Resources/Texture.h"
#include "Core/Camera.h"
#include "Collider/CollisionManager.h"

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
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(395);  // 평소에는 주석 걸어놓고 메모리 누수가 있을 때 활성화하여 메모리 누수를 찾아주기.
							 // 괄호 안에 메모리 블럭 번호를 대입하고 프로그램을 실행해보면 메모리 누수가 생기는 코드로 이동함
							 // 호출 스택에서 전 단계들을 확인하여 원인을 찾아내자.

	// _CRTDBG_ALLOC_MEM_DF: 할당하는 메모리 체크
	// _CRTDBG_LEAK_CHECK_DF: 메모리 누수가 생긴 부분으로 이동(?)
	// 메모리 누수가 있으면 프로그램 종료 시 출력 란에 알려줌 => 여기서 블록 번호를 체크하자
}

Core::~Core()
{
	// TODO: 각종 싱글턴 DESTROY_SINGLE 해주기
	DESTROY_SINGLE(Timer);
	DESTROY_SINGLE(SceneManager);
	DESTROY_SINGLE(CInput);
	DESTROY_SINGLE(PathManager);
	DESTROY_SINGLE(ResourcesManager);
	DESTROY_SINGLE(Camera);
	DESTROY_SINGLE(CollisionManager);

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

	// 월드 맵크기 설정
	m_tWorldRS.iW = 3840;
	m_tWorldRS.iH = 720;

	Create();

	m_hDC = GetDC(m_hWnd);

	// TODO: 각종 싱글턴 Init

	// 타이머 초기화
	if (!GET_SINGLE(Timer)->Init(m_hWnd))
		return false;

	// 경로 매니저 초기화
	if (!GET_SINGLE(PathManager)->Init())
		return false;

	// 인풋 초기화
	if (!GET_SINGLE(CInput)->Init())
		return false;

	// 리소스 매니저 초기화
	if (!GET_SINGLE(ResourcesManager)->Init(m_hInst, m_hDC))
		return false;

	// 카메라 초기화
	if (!GET_SINGLE(Camera)->Init(POSITION(0.f, 0.f), m_tRS, m_tWorldRS))
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
	if (Update(fDeltaTime) == SCENE_CHANGE::CHANGE)
		return;
	if (LateUpdate(fDeltaTime) == SCENE_CHANGE::CHANGE)
		return;
	Collision(fDeltaTime);
	Render(fDeltaTime);
}

void Core::Input(float fDeltaTime)
{
	GET_SINGLE(CInput)->Update(fDeltaTime);
	GET_SINGLE(SceneManager)->Input(fDeltaTime);
	GET_SINGLE(Camera)->Input(fDeltaTime);
}

SCENE_CHANGE Core::Update(float fDeltaTime)
{
	SCENE_CHANGE sc;
	sc = GET_SINGLE(SceneManager)->Update(fDeltaTime);
	GET_SINGLE(Camera)->Update(fDeltaTime);
	return sc;
}

SCENE_CHANGE Core::LateUpdate(float fDeltaTime)
{
	SCENE_CHANGE sc;
	sc = GET_SINGLE(SceneManager)->LateUpdate(fDeltaTime);
	return sc;
}

void Core::Collision(float fDeltaTime)
{
	GET_SINGLE(SceneManager)->Collision(fDeltaTime);
	GET_SINGLE(CollisionManager)->Collision(fDeltaTime);
}

void Core::Render(float fDeltaTime)
{
	Texture* pBackBuffer = GET_SINGLE(ResourcesManager)->GetBackBuffer();
	
	Rectangle(pBackBuffer->GetDC(), 0, 0, m_tRS.iW, m_tRS.iH);	// 나중에 배경 적용하면 지워도됨
	GET_SINGLE(SceneManager)->Render(pBackBuffer->GetDC(), fDeltaTime);

	// 정상적인 Render 흐름: 코어->씬매니저->개별씬->개별레이어->개별오브젝트 (이후 오브젝트에서 직접 그림)
	//GET_SINGLE(SceneManager)->Render(m_hDC, fDeltaTime);
	BitBlt(m_hDC, 0, 0, m_tRS.iW, m_tRS.iH, pBackBuffer->GetDC(), 0, 0, SRCCOPY);

	SAFE_RELEASE(pBackBuffer);
}

