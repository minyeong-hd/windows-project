#include <windows.h>
#include <stdio.h>

int main() {
    char letter = 'O';
    int letterX = 10;
    int letterY = 5;
    int isDragging = 0;

    HWND consoleWnd = GetConsoleWindow(); // 콘솔 윈도우 핸들
    POINT mousePos;

    while (1) {
        // 마우스 좌표 얻기 (화면 기준)
        GetCursorPos(&mousePos);
        ScreenToClient(consoleWnd, &mousePos);  // 콘솔 기준으로 변환

        // 마우스 클릭 감지
        SHORT mouseState = GetAsyncKeyState(VK_LBUTTON);

        if (mouseState & 0x8000) {
            // 마우스를 누르고 있으면 드래그 상태로 간주
            isDragging = 1;

            // 화면 기준 → 콘솔 문자 좌표 환산 (가정: 한 문자 너비 약 8px, 높이 약 16px)
            letterX = mousePos.x / 8;
            letterY = mousePos.y / 16;
        } else {
            isDragging = 0;
        }

        // 콘솔 초기화 및 출력
        system("cls");
        printf("알파벳 '%c'을 마우스로 드래그하세요.\n", letter);
        printf("현재 알파벳 위치: (%d, %d)\n", letterX, letterY);

        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){(SHORT)letterX, (SHORT)letterY});
        printf("%c", letter);

        // ESC 키로 종료
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            printf("\n프로그램 종료\n");
            break;
        }

        Sleep(10);
    }

    return 0;
}
