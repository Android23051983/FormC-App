// FormC++App.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "FormC++App.h"

#define MAX_LOADSTRING 100
int width = 500;
int height = 500;
int x = 100;
int y = 100;
int Wx = 0;
int Wy = 0;


// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

int l, r, m, ld, rd, md;
// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

RECT rect;
POINT koord;

void SetTitle(void)
{
    wsprintf(szTitle, _T("l=%d, r=%d, m=%d, ld=%d, rd=%d, md=%d"), l, r, m, ld, rd, md);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_FORMCAPP, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FORMCAPP));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FORMCAPP));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_FORMCAPP);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
       x, y, width, height, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    WCHAR str[50];
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

    case WM_LBUTTONDOWN:
        l++;
        SetTitle();
        SetWindowText(hWnd, szTitle);
        Wx = LOWORD(lParam);
        Wy = HIWORD(lParam);
        wsprintf(szTitle, TEXT("X=%d, Y=%d"),Wx, Wy);
        SetWindowText(hWnd, szTitle);
        break;

    case WM_RBUTTONDOWN:
        r++;
        SetTitle();
        SetWindowText(hWnd, szTitle);
        GetWindowRect(hWnd, &rect);
        width = rect.right - rect.left;
        height = rect.bottom - rect.top;
        wsprintf(szTitle, TEXT("w=%d h=%d"), width, height);
        SetWindowText(hWnd, szTitle);
        break;
    
    case WM_MBUTTONDOWN:
        m++;
        SetTitle();
        SetWindowText(hWnd, szTitle);
        break;

    case WM_LBUTTONDBLCLK:
        ld++;
        SetTitle();
        SetWindowText(hWnd, szTitle);
        break;

    case WM_RBUTTONDBLCLK:
        rd++;
        SetTitle();
        SetWindowText(hWnd, szTitle);
        break;
    case WM_MBUTTONDBLCLK:
        md++;
        SetTitle();
        SetWindowText(hWnd, szTitle);
        break;
    case WM_MOUSEMOVE:
      /*  wsprintf(szTitle, TEXT("X=%d Y=%d"), LOWORD(lParam), HIWORD(lParam));
        SetWindowText(hWnd, szTitle);*/
        break;
   /* case WM_CHAR:
        wsprintf(str, TEXT("Нажата клавиша %c"),(WCHAR)wParam);
        MessageBox(0, str, TEXT("WM_CHAR"), MB_OK | MB_ICONINFORMATION);
        break;*/
    case WM_KEYDOWN:
        if ((WCHAR)wParam == VK_RETURN)
        {
            //wsprintf(str, TEXT("Нажата клавиша Enter %c"), (WCHAR)wParam); //Формирование сообщения
            //MessageBox(0, str, TEXT("WM_CHAR"), MB_OK | MB_ICONINFORMATION); //Принятие сообщение в MessageBox и вывод MessageBox 
            MoveWindow(hWnd, 0, 0, 300, 300, TRUE);
        }
        break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
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
