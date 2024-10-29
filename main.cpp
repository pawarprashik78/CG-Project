//COMPUTER GRAPHICS MINI-PROJECT
//KISHOR SURWADE -62
//PRASHIK PAWAR  -77
//SYCOMP 
//DIV-A
//BATCH -A3
#include <graphics.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>

void drawBird(int x, int y) {
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, YELLOW);
    fillellipse(x, y, 15, 10);

    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    fillellipse(x - 5, y, 8, 5);

    setcolor(RED);
    setfillstyle(SOLID_FILL, RED);
    int beak[] = {x + 15, y, x + 20, y - 5, x + 20, y + 5};
    fillpoly(3, beak);

    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    fillellipse(x + 5, y - 3, 2, 2);
}

void drawBackground(int ground) {
    setcolor(LIGHTBLUE);
    setfillstyle(SOLID_FILL, LIGHTBLUE);
    bar(0, 0, getmaxx(), ground - 50);

    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    fillellipse(100, 50, 30, 15);
    fillellipse(130, 50, 40, 20);
    fillellipse(160, 50, 30, 15);
    fillellipse(300, 100, 25, 12);
    fillellipse(325, 100, 35, 18);
    fillellipse(355, 100, 25, 12);

    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);
    bar(0, ground - 50, getmaxx(), ground);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    bool playAgain = true;

    while (playAgain) {
        int birdX = 100, birdY = 200;
        int gravity = 1;
        int jump = -12;
        int velocity = 0;
        int ground = getmaxy();
        int pipeX = getmaxx();
        int pipeGap = 120;
        int pipeWidth = 30;
        int pipeSpeed = 3;
        int score = 0;
        bool isGameOver = false;

        srand(time(0));
        int upperPipeHeight = rand() % (ground - pipeGap);

        while (!isGameOver) {
            cleardevice();
            drawBackground(ground);
            drawBird(birdX, birdY);

            setcolor(GREEN);
            setfillstyle(SOLID_FILL, GREEN);
            bar(pipeX, 0, pipeX + pipeWidth, upperPipeHeight);
            int lowerPipeY = upperPipeHeight + pipeGap;
            bar(pipeX, lowerPipeY, pipeX + pipeWidth, ground);

            setcolor(WHITE);
            settextstyle(SIMPLEX_FONT, HORIZ_DIR, 2);
            char scoreText[10];
            sprintf(scoreText, "Score: %d", score);
            outtextxy(10, 10, scoreText);

            bool hitPipe = (birdX + 15 > pipeX && birdX - 15 < pipeX + pipeWidth && (birdY - 10 < upperPipeHeight || birdY + 10 > lowerPipeY));
            bool hitGround = (birdY + 10 >= ground - 50);

            if (hitPipe || hitGround) {
                isGameOver = true;
            }

            velocity += gravity;
            birdY += velocity;
            pipeX -= pipeSpeed;

            if (pipeX + pipeWidth < 0) {
                pipeX = getmaxx();
                upperPipeHeight = rand() % (ground - pipeGap);
                score++;
            }

            if (kbhit()) {
                char ch = getch();
                if (ch == ' ') {
                    velocity = jump;
                }
            }

            delay(30);
        }

        cleardevice();
        setcolor(RED);
        settextstyle(SIMPLEX_FONT, HORIZ_DIR, 4);
        outtextxy(getmaxx() / 2 - 100, getmaxy() / 2 - 20, "GAME OVER");

        char finalScore[10];
        sprintf(finalScore, "Score: %d", score);
        settextstyle(SIMPLEX_FONT, HORIZ_DIR, 2);
        outtextxy(getmaxx() / 2 - 50, getmaxy() / 2 + 40, finalScore);

        outtextxy(getmaxx() / 2 - 150, getmaxy() / 2 + 80, "Press 'R' to Retry or 'Q' to Quit");

        bool validInput = false;
        while (!validInput) {
            char ch = getch();
            if (ch == 'r' || ch == 'R') {
                playAgain = true;
                validInput = true;
            } else if (ch == 'q' || ch == 'Q') {
                playAgain = false;
                validInput = true;
            }
        }
    }

    closegraph();
    return 0;
}