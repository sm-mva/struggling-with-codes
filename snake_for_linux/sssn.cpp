    #include <iostream>
    #include <cstdlib>
    #include <ncurses.h>
    #include <sys/select.h>
    #include <termios.h>
    #include <sys/ioctl.h>
    #include <stropts.h>
    #include <stdlib.h>
    #define NANO_SECOND_MULTIPLIER  1000000  // 1 millisecond = 1,000,000 Nanoseconds

    using namespace std;
    const long INTERVAL_MS = 900*NANO_SECOND_MULTIPLIER;
    bool gameOver, gameWin;
    const int wifield = 20;
    const int hefield = 20;
    int x, y, appleX, appleY, score;
    int tailX[100], tailY[100];
    int ctail;
    enum emove {LEFT, RIGHT, UP, DOWN, STOP=0};
    emove step;

    int _kbhit() {
    static const int STDIN = 0;
    static bool initialized = false;

    if (! initialized) {
    termios term;
    tcgetattr(STDIN, &term);
    term.c_lflag &= ~ICANON;
    tcsetattr(STDIN, TCSANOW, &term);
    setbuf(stdin, NULL);
    initialized = true;
    }

    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
    }

    void Settings() {
    gameOver = false;
    gameWin = false;
    step = STOP;
    x = wifield / 2;
    y = hefield / 2;
    appleX = rand() % wifield;
    appleY = rand() % hefield;
    score = 0;
    }
    void Karta() {

    system ("clear");
    for (int i=0; i<wifield + 1; i++)
    cout<<"#";
    cout<< endl;
    for (int i=0; i<hefield; i++) {
    for (int j=0; j<wifield; j++) {
    if (j == 0 ||j==wifield -1)
    cout<< "#";
    if (i==y && j==x)
    cout<< "*";
    else if (i==appleY && j==appleX)
    cout<< "@";
    else {
    bool draw = false;
    for (int l=0; l<ctail; l++){
    if(tailX[l]==j && tailY[l]==i){
    draw = true;
    cout<<"+";
    }
    }
    if (!draw)
    cout<< " ";
    }
    }
    cout<< endl;

    }

    for (int i=0; i<wifield + 1; i++)
    cout<< "#";
    cout << endl;
    cout<< "Score: "<<score<<endl;
    }

    void Tracking() {
    initscr();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
    if (_kbhit()){
    switch (getch()) {
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
    endwin();
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
    score +=5;
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
    timespec sleepValue = {0};
    sleepValue.tv_nsec = INTERVAL_MS;
    nanosleep(&sleepValue, NULL);
    }
    if (score == 35 ) {
    cout << "\nYou won!\n";
    }
    else {
    cout << "\nhahah! You lose!\n";
    cin >> gameOver;
    }

    return 0;
    }


