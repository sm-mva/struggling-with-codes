#include <cstdlib>
#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;

bool gameOver;
const int wifield = 20;
const int hefield = 20;
int x, y, appleX, appleY, score;
int tailX[100], tailY[100];
int ctail;
enum emove {LEFT, RIGHT, UP, DOWN, STOP=0};
emove step;

void Settings() {
gameOver = false;
step = STOP;
x = wifield / 4;
y = hefield / 4;
appleX = rand() % wifield;
appleY = rand() % hefield;
score = 0;
}
void Karta() {

system ("cls");
for (int i=0; i<wifield + 1; i++)
cout« "#";
cout « endl;
for (int i=0; i<hefield; i++) {
for (int j=0; j<wifield; j++) {
if (j == 0 ||j==wifield -1)
cout« "#";
if (i==y && j==x)
cout« "*";
else if (i==appleY && j==appleX)
cout« "@";
else {
bool draw = false;
for (int l=0; l<ctail; l++){
if(tailX[l]==j && tailY[l]==i){
draw = true;
cout«"+";
}
}
if (!draw)
cout« " ";
}
}
cout« endl;

}

for (int i=0; i<wifield + 1; i++)
cout« "#";
cout « endl;
cout« "Score: "« score « endl;
}

void Tracking() {

if (_kbhit()){
switch (_getch()) {
case '1':
step = LEFT;
break;
case '3':
step = RIGHT;
break;
case '5':
step = UP;
break;
case '2':
step = DOWN;
break;
case '0':
gameOver = true;
break;}
}
}
void BrainGame() {
int firstX = tailX[0];
int firstY = tailY[0];
int secondX, secondY;
tailX[0]=x;
tailY[0]=y;
for (int i=1; i<ctail; i++){
secondX = tailX[i];
secondY = tailY[i];
tailX[i] = firstX;
tailY[i] = firstY;
firstX = secondX;
firstY = secondY;
}
switch (step) {
case LEFT:
x--;
break;
case RIGHT:
x++;
break;
case UP:
y--;
break;
case DOWN:
y++;
break;
}
if (x > wifield || x < 0 || y > hefield || y < 0)
gameOver = true;
for (int i=0; i<ctail; i++){
if (tailX[i]==x && tailY[i]==y)
gameOver = true;
}

if (x==appleX && y==appleY){
score += 5;
appleX = rand() % wifield;
appleY = rand() % hefield;
ctail++;
}
}

int main() {
Settings();
while(!gameOver) {
Karta();
Tracking();
BrainGame();
Sleep(900);
}
return 0;
}
