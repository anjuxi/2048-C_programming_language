/**
 * 2048 游戏 - EGE 图形界面版本
 * 编译命令（64位 MinGW）：
 * g++ 2048.cpp -o 2048.exe -lgraphics64 -lgdi32 -lgdiplus -limm32 -lmsimg32 -lole32 -loleaut32 -lwinmm -luuid
 * 
 * 需要先安装 EGE 图形库
 */

#include <graphics.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>

const int GRID_SIZE = 100;
const int GRID_COUNT = 4;
const int WIN_SIZE = GRID_SIZE * GRID_COUNT;
const int MARGIN = 10;
const int CELL_SIZE = GRID_SIZE - MARGIN * 2;

int board[4][4] = {0};
int score = 0;
bool gameOver = false;
bool gameWin = false;

color_t getNumberColor(int num) {
    switch(num) {
        case 0:     return EGERGB(205, 193, 180);
        case 2:     return EGERGB(238, 228, 218);
        case 4:     return EGERGB(237, 224, 200);
        case 8:     return EGERGB(242, 177, 121);
        case 16:    return EGERGB(245, 149, 99);
        case 32:    return EGERGB(246, 124, 95);
        case 64:    return EGERGB(246, 94, 59);
        case 128:   return EGERGB(237, 207, 114);
        case 256:   return EGERGB(237, 204, 97);
        case 512:   return EGERGB(237, 200, 80);
        case 1024:  return EGERGB(237, 197, 63);
        case 2048:  return EGERGB(237, 194, 46);
        default:    return EGERGB(60, 58, 50);
    }
}

void initGame() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            board[i][j] = 0;
    score = 0;
    gameOver = false;
    gameWin = false;
    
    srand((unsigned)time(NULL));
    
    int x1 = rand() % 4;
    int y1 = rand() % 4;
    board[x1][y1] = (rand() % 10 == 0) ? 4 : 2;
    
    int x2, y2;
    do {
        x2 = rand() % 4;
        y2 = rand() % 4;
    } while (x2 == x1 && y2 == y1);
    board[x2][y2] = (rand() % 10 == 0) ? 4 : 2;
}

int countEmpty() {
    int cnt = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (board[i][j] == 0) cnt++;
    return cnt;
}

void addRandomNumber() {
    int empty = countEmpty();
    if (empty == 0) return;
    
    int target = rand() % empty + 1;
    int cnt = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0) {
                cnt++;
                if (cnt == target) {
                    board[i][j] = (rand() % 10 == 0) ? 4 : 2;
                    return;
                }
            }
        }
    }
}

void mergeAndMoveLeft(int arr[4]) {
    int temp[4] = {0};
    int idx = 0;
    for (int i = 0; i < 4; i++) {
        if (arr[i] != 0) {
            temp[idx++] = arr[i];
        }
    }
    
    for (int i = 0; i < 3; i++) {
        if (temp[i] != 0 && temp[i] == temp[i + 1]) {
            temp[i] *= 2;
            score += temp[i];
            if (temp[i] == 2048) gameWin = true;
            for (int j = i + 1; j < 3; j++) {
                temp[j] = temp[j + 1];
            }
            temp[3] = 0;
        }
    }
    
    for (int i = 0; i < 4; i++) {
        arr[i] = temp[i];
    }
}

int backup[4][4];

void backupBoard() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            backup[i][j] = board[i][j];
}

bool boardChanged() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (board[i][j] != backup[i][j])
                return true;
    return false;
}

void reverseRow(int arr[4]) {
    int temp[4];
    for (int i = 0; i < 4; i++) temp[i] = arr[3 - i];
    for (int i = 0; i < 4; i++) arr[i] = temp[i];
}

void moveLeft() {
    for (int i = 0; i < 4; i++) {
        mergeAndMoveLeft(board[i]);
    }
}

void moveRight() {
    for (int i = 0; i < 4; i++) {
        reverseRow(board[i]);
        mergeAndMoveLeft(board[i]);
        reverseRow(board[i]);
    }
}

void transpose() {
    int temp[4][4];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            temp[i][j] = board[j][i];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            board[i][j] = temp[i][j];
}

void moveUp() {
    transpose();
    moveLeft();
    transpose();
}

void moveDown() {
    transpose();
    moveRight();
    transpose();
}

bool checkGameOver() {
    if (countEmpty() > 0) return false;
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == board[i][j + 1])
                return false;
        }
    }
    
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 3; i++) {
            if (board[i][j] == board[i + 1][j])
                return false;
        }
    }
    
    return true;
}

void drawGame() {
    cleardevice();
    
    setbkcolor(EGERGB(187, 173, 160));
    cleardevice();
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int x = j * GRID_SIZE + MARGIN;
            int y = i * GRID_SIZE + MARGIN;
            int num = board[i][j];
            
            setfillcolor(getNumberColor(num));
            setcolor(getNumberColor(num));
            bar(x, y, x + CELL_SIZE, y + CELL_SIZE);
            
            if (num != 0) {
                char str[10];
                sprintf(str, "%d", num);
                
                if (num < 100) setfont(40, 0, "宋体");
                else if (num < 1000) setfont(36, 0, "宋体");
                else setfont(32, 0, "宋体");
                
                setcolor(EGERGB(0, 0, 0));
                int textW = textwidth(str);
                int textH = textheight(str);
                outtextxy(x + (CELL_SIZE - textW) / 2, 
                          y + (CELL_SIZE - textH) / 2, str);
            }
        }
    }
    
    setfont(20, 0, "宋体");
    setcolor(WHITE);
    char scoreStr[50];
    sprintf(scoreStr, "Score: %d", score);
    outtextxy(10, WIN_SIZE + 10, scoreStr);
    
    if (gameWin) {
        setfont(30, 0, "宋体");
        setcolor(EGERGB(255, 215, 0));
        outtextxy(WIN_SIZE/2 - 80, WIN_SIZE/2 - 20, "YOU WIN!");
        setfont(20, 0, "宋体");
        setcolor(WHITE);
        outtextxy(WIN_SIZE/2 - 100, WIN_SIZE/2 + 30, "Press R to restart");
    } else if (gameOver) {
        setfont(30, 0, "宋体");
        setcolor(EGERGB(255, 100, 100));
        outtextxy(WIN_SIZE/2 - 90, WIN_SIZE/2 - 20, "GAME OVER");
        setfont(20, 0, "宋体");
        setcolor(WHITE);
        outtextxy(WIN_SIZE/2 - 100, WIN_SIZE/2 + 30, "Press R to restart");
    }
    
    delay_fps(60);
}

int main() {
    initgraph(WIN_SIZE, WIN_SIZE + 60);
    setcaption("2048 Game");
    
    initGame();
    
    while (is_run()) {
        drawGame();
        
        if (gameOver || gameWin) {
            if (GetAsyncKeyState('R') & 0x8000) {
                initGame();
                delay_ms(200);
            }
            continue;
        }
        
        backupBoard();
        
        bool moved = false;
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            moveLeft();
            moved = true;
            delay_ms(130);
        }
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            moveRight();
            moved = true;
            delay_ms(130);
        }
        if (GetAsyncKeyState(VK_UP) & 0x8000) {
            moveUp();
            moved = true;
            delay_ms(130);
        }
        if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
            moveDown();
            moved = true;
            delay_ms(130);
        }
        
        if (moved && boardChanged()) {
            addRandomNumber();
            gameOver = checkGameOver();
        }
        
        if (GetAsyncKeyState('R') & 0x8000) {
            initGame();
            delay_ms(200);
        }
    }
    
    closegraph();
    return 0;
}