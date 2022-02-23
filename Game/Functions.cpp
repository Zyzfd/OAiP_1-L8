#include "Functions.h"

#define N 10
#define M 15

int a[N][M] = {
{ 3, 0, 1, 0, 0,   0, 0, 0, 0, 0,   0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0,   0, 0, 0, 0, 0,   0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 2,   0, 0, 0, 0, 0,   0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 2,   0, 0, 0, 0, 0,   0, 2, 0, 0, 0 },
{ 0, 0, 0, 0, 2,   2, 2, 2, 2, 2,   0, 2, 0, 0, 0 },

{ 0, 0, 0, 0, 0,   0, 0, 0, 0, 2,   0, 2, 0, 0, 0 },
{ 0, 0, 1, 0, 0,   0, 0, 0, 0, 2,   0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0,   0, 1, 0, 0, 0,   0, 2, 0, 0, 0 },
{ 0, 0, 0, 0, 0,   0, 0, 0, 0, 0,   0, 2, 0, 0, 0 },
{ 0, 0, 1, 0, 1,   0, 0, 0, 0, 0,   0, 2, 0, 0, 0 }
};

int steps = 0;
int gold = 0;

void moveToLeft() {
    int i, j;
    i = 0;
    while (i < N) {
        j = 1;
        while (j < M) {
            if (a[i][j] == 3) {
                if (a[i][j - 1] == 0) {
                    a[i][j - 1] = 3;
                    a[i][j] = 0;
                    steps++;
                }
                else if (a[i][j - 1] == 1) {
                    a[i][j - 1] = 3;
                    a[i][j] = 0;
                    steps++;
                    gold++;
                }
            }
            j++;
        }
        i++;
    }
}

void moveToRight() {
    int i = 0;
    while (i < N) {
        int j = M - 2;
        while (j >= 0) {
            if (a[i][j] == 3) {
                if (a[i][j + 1] == 0) {
                    a[i][j + 1] = 3;
                    a[i][j] = 0;
                    steps++;
                }
                else if (a[i][j + 1] == 1) {
                    a[i][j + 1] = 3;
                    a[i][j] = 0;
                    steps++;
                    gold++;
                }
            }
            j--;
        }
        i++;
    }
}

void moveUp() {
    int i = 1;
    while (i < N) {
        int j = 0;
        while (j < M) {
            if (a[i][j] == 3) {
                if (a[i - 1][j] == 0) {
                    a[i - 1][j] = 3;
                    a[i][j] = 0;
                    steps++;
                }
                else if (a[i - 1][j] == 1) {
                    a[i - 1][j] = 3;
                    a[i][j] = 0;
                    steps++;
                    gold++;
                }
            }
            j++;
        }
        i++;
    }
}

void moveDown() {
    int i = N - 2;
    while (i >= 0) {
        int j = 0;
        while (j < M) {
            if (a[i][j] == 3) {
                if (a[i + 1][j] == 0) {
                    a[i + 1][j] = 3;
                    a[i][j] = 0;
                    steps++;
                }
                else if (a[i + 1][j] == 1) {
                    a[i + 1][j] = 3;
                    a[i][j] = 0;
                    steps++;
                    gold++;
                }
            }
            j++;
        }
        i--;
    }
}

int sizeX = 36;
int sizeY = 30;

void DrawField(HDC hdc) {

    HBRUSH hBrushEmptyCell; //создаём кисть для пустого поля
    hBrushEmptyCell = CreateSolidBrush(RGB(200, 200, 200)); // серый

    HBRUSH hBrushGold; //создаём кисть для поля с золотом
    hBrushGold = CreateSolidBrush(RGB(255, 255, 0)); // желтый

    HBRUSH hBrushWall; //создаём кисть для стены
    hBrushWall = CreateSolidBrush(RGB(0, 0, 0)); // черный

    HBRUSH hBrushMan; //создаём кисть для игрока
    hBrushMan = CreateSolidBrush(RGB(0, 0, 255)); // синий

    int i, j;
    i = 0;
    while (i < N) {
        j = 0;
        while (j < M) {
            RECT rect = { j * sizeX,i * sizeY,  (j + 1) * sizeX,(i + 1) * sizeY };
            if (a[i][j] == 0) {
                FillRect(hdc, &rect, hBrushEmptyCell);
            }
            else if (a[i][j] == 1) {
                FillRect(hdc, &rect, hBrushGold);
            }
            else if (a[i][j] == 2) {
                FillRect(hdc, &rect, hBrushWall);
            }
            else if (a[i][j] == 3) {
                FillRect(hdc, &rect, hBrushMan);
            }
            else {
                // тут никогда не должны оказаться
            }
            j++;
        }
        i++;
    }

    HFONT hFont;
    hFont = CreateFont(20,
        0, 0, 0, 0, 0, 0, 0,
        DEFAULT_CHARSET,
        0, 0, 0, 0,
        L"Courier New"
    );
    SelectObject(hdc, hFont);
    SetTextColor(hdc, RGB(0, 128, 128));

    TCHAR  string1[] = _T("сделано ходов:");
    TCHAR  string2[] = _T("собрано золота:");
    TextOut(hdc, 10, sizeY * (N + 1), (LPCWSTR)string1, _tcslen(string1));
    TextOut(hdc, 10, sizeY * (N + 1) + 20, (LPCWSTR)string2, _tcslen(string2));

    char sSteps[5];
    TCHAR  tsSteps[5];
    sprintf(sSteps, "%d", steps);
    OemToChar(sSteps, tsSteps);
    TextOut(hdc, 220, sizeY * (N + 1), (LPCWSTR)tsSteps, _tcslen(tsSteps));

    char sGold[5];
    TCHAR  tsGold[5];
    sprintf(sGold, "%d", gold);
    OemToChar(sGold, tsGold);
    TextOut(hdc, 220, sizeY * (N + 1) + 20, (LPCWSTR)tsGold, _tcslen(tsGold));

    DeleteObject(hFont);
    DeleteObject(hBrushEmptyCell);
    DeleteObject(hBrushGold);
    DeleteObject(hBrushWall);
    DeleteObject(hBrushMan);

} // конец функции void DrawField(HDC hdc) 


void newWallLeft() {
    int i = 0;
    while (i < N) {
        int j = 0;
        while (j < M) {
            if (a[i][j] == 3) {
                if (j != 0) {
                    a[i][j - 1] = 2;
                }
            }
            j++;
        }
        i++;
    }
}

void newWallRight() {
    int i = 0;
    while (i < N) {
        int j = 0;
        while (j < M) {
            if (a[i][j] == 3) {
                if (j != M - 1) {
                    a[i][j + 1] = 2;
                }
            }
            j++;
        }
        i++;
    }
}

void newWallUp() {
    int i = 0;
    while (i < N) {
        int j = 0;
        while (j < M) {
            if (a[i][j] == 3) {
                if (i != 0) {
                    a[i - 1][j] = 2;
                }
            }
            j++;
        }
        i++;
    }
}

void newWallDown() {
    int i = 0;
    while (i < N) {
        int j = 0;
        while (j < M) {
            if (a[i][j] == 3) {
                if (i != N - 1) {
                    a[i + 1][j] = 2;
                }
            }
            j++;
        }
        i++;
    }
}

void destroyWallRight() {
    int i = 0;
    while (i < N) {
        int j = 0;
        while (j < M) {
            if (a[i][j] == 3) {
                j++;
                while (j < M) {
                    if (a[i][j] == 2) {
                        a[i][j] = 0;
                    }
                    j++;
                }
            }
            j++;
        }
        i++;
    }
}

void destroyWallLeft() {
    int i = 0;
    while (i < N) {
        int j = 0;
        while (j < M) {
            if (a[i][j] == 3) {
                j--;
                while (j >= 0) {
                    if (a[i][j] == 2) {
                        a[i][j] = 0;
                    }
                    j--;
                }
                break;
            }
            j++;
        }
        i++;
    }
}

void destroyWallAround() {
    int i = 0;
    while (i < N) {
        int j = 0;
        while (j < M) {
            if (a[i][j] == 3) {
                if (i - 1 < 0 and j - 1 < 0) {
                    if (a[i + 1][j] == 2) {
                        a[i + 1][j] = 0;
                    }
                    if (a[i + 1][j + 1] == 2) {
                        a[i + 1][j + 1] = 0;
                    }
                    if (a[i][j + 1] == 2) {
                        a[i][j + 1] = 0;
                    }
                }

                else if (i - 1 < 0 and j + 1 > M - 1) {
                    if (a[i + 1][j] == 2) {
                        a[i + 1][j] = 0;
                    }
                    if (a[i + 1][j - 1] == 2) {
                        a[i + 1][j - 1] = 0;
                    }
                    if (a[i][j - 1] == 2) {
                        a[i][j - 1] = 0;
                    }
                }

                else if (i + 1 > N - 1 and j - 1 < 0) {
                    if (a[i - 1][j] == 2) {
                        a[i - 1][j] = 0;
                    }
                    if (a[i - 1][j + 1] == 2) {
                        a[i - 1][j + 1] = 0;
                    }
                    if (a[i][j + 1] == 2) {
                        a[i][j + 1] = 0;
                    }
                }

                else if (i + 1 > N - 1 and j + 1 > M - 1) {
                    if (a[i - 1][j] == 2) {
                        a[i - 1][j] = 0;
                    }
                    if (a[i - 1][j - 1] == 2) {
                        a[i - 1][j - 1] = 0;
                    }
                    if (a[i][j - 1] == 2) {
                        a[i][j - 1] = 0;
                    }
                }

                else if (i - 1 < 0) {
                    if (a[i + 1][j] == 2) {
                        a[i + 1][j] = 0;
                    }
                    if (a[i + 1][j + 1] == 2) {
                        a[i + 1][j + 1] = 0;
                    }
                    if (a[i][j + 1] == 2) {
                        a[i][j + 1] = 0;
                    }
                    if (a[i + 1][j - 1] == 2) {
                        a[i + 1][j - 1] = 0;
                    }
                    if (a[i][j - 1] == 2) {
                        a[i][j - 1] = 0;
                    }
                }

                else if (i + 1 > N - 1) {
                    if (a[i - 1][j] == 2) {
                        a[i - 1][j] = 0;
                    }
                    if (a[i - 1][j + 1] == 2) {
                        a[i - 1][j + 1] = 0;
                    }
                    if (a[i][j + 1] == 2) {
                        a[i][j + 1] = 0;
                    }
                    if (a[i - 1][j - 1] == 2) {
                        a[i - 1][j - 1] = 0;
                    }
                    if (a[i][j - 1] == 2) {
                        a[i][j - 1] = 0;
                    }
                }

                else if (j - 1 < 0) {
                    if (a[i - 1][j] == 2) {
                        a[i - 1][j] = 0;
                    }
                    if (a[i - 1][j + 1] == 2) {
                        a[i - 1][j + 1] = 0;
                    }
                    if (a[i][j + 1] == 2) {
                        a[i][j + 1] = 0;
                    }
                    if (a[i + 1][j + 1] == 2) {
                        a[i + 1][j + 1] = 0;
                    }
                    if (a[i + 1][j] == 2) {
                        a[i + 1][j] = 0;
                    }
                }

                else if (j + 1 > M - 1) {
                    if (a[i - 1][j] == 2) {
                        a[i - 1][j] = 0;
                    }
                    if (a[i - 1][j - 1] == 2) {
                        a[i - 1][j - 1] = 0;
                    }
                    if (a[i][j - 1] == 2) {
                        a[i][j - 1] = 0;
                    }
                    if (a[i + 1][j - 1] == 2) {
                        a[i + 1][j - 1] = 0;
                    }
                    if (a[i + 1][j] == 2) {
                        a[i + 1][j] = 0;
                    }
                }

                else {
                    if (a[i - 1][j] == 2) {
                        a[i - 1][j] = 0;
                    }
                    if (a[i - 1][j + 1] == 2) {
                        a[i - 1][j + 1] = 0;
                    }
                    if (a[i][j + 1] == 2) {
                        a[i][j + 1] = 0;
                    }
                    if (a[i + 1][j + 1] == 2) {
                        a[i + 1][j + 1] = 0;
                    }
                    if (a[i + 1][j] == 2) {
                        a[i + 1][j] = 0;
                    }
                    if (a[i - 1][j - 1] == 2) {
                        a[i - 1][j - 1] = 0;
                    }
                    if (a[i][j - 1] == 2) {
                        a[i][j - 1] = 0;
                    }
                    if (a[i + 1][j - 1] == 2) {
                        a[i + 1][j - 1] = 0;
                    }
                }
            }
            j++;
        }
        i++;
    }
}