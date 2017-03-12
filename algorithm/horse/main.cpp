/*
 * 马踏棋盘最原始的深度优先算法
 * 利用栈
 */
#include <iostream>
#include <chrono>
#include <stack>
#include <assert.h>
#include <cstring>
using namespace std;
const int chessX = 8;
const int chessY = 8;
static bool chess[chessX][chessY];//棋盘，遍历过的位置进行标记
struct Id{
    int x;
    int y;
    Id(int theX,int theY):x(theX),y(theY) {};
    ~Id() = default;
};
stack<Id> step;//栈，依次存放每次遍历的坐标，回溯的时候出栈
bool run(int,int);
int judge(int,int,int &);//判断路径，返回0-7表示选择的路径，返回则需要回溯
bool isInChess(int,int,int);//判断某个方向的落子是否在棋盘内
bool isNeverRun(int,int,int);//判断落子是否被遍历过
Id next(int,int,int);//返回cnt方向的落子位置
int main()
{
    memset(chess,0x00,sizeof(chess));
    auto start = chrono::system_clock::now();
    run(0,7);
    auto end = chrono::system_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end-start);
    /*
    for(int i=0;i<chessX;++i)
    {
        for(int j = 0;j<chessY;++j)
            cout << chess[i][j];
        cout << endl;
    }*/
    if(step.size()==0)
    {
        cout << "can not complete!" << endl;
        return 0;
    }
    int res[chessX][chessY] = {0};
    for(int i=0;i<chessX*chessY;++i)
    {
        res[step.top().x][step.top().y] = chessX*chessY-i;
        step.pop();
    }
    for(int i=0;i<chessX;++i)
    {
        for(int j = 0;j<chessY;++j)
            cout << res[i][j] << '\t';
        cout << endl;
    }

    cout << double(duration.count())* chrono::microseconds::period::num/
         chrono::microseconds::period::den
         << "秒" << endl;
    return 0;
}

bool run(int x,int y)
{
    int cnt = 0;
    bool finish;
    step.push(Id(x,y));
    chess[x][y] = true;
    if(step.size()>=chessX*chessY)
        return true;
    while(judge(x,y,cnt)<8)
    {
        Id nextId = next(x,y,cnt);
        finish = run(nextId.x,nextId.y);
        if(finish)
            return true;
        else
            ++cnt;
    }
    //finish==false
    step.pop();
    chess[x][y] = false;
    return false;
}

int judge(int x,int y,int &cnt)
{
    while(cnt<8)
    {
        if(isInChess(x,y,cnt)&&isNeverRun(x,y,cnt))
            return cnt;
        else
            ++cnt;
    }
    return cnt;
}

bool isInChess(int x,int y,int cnt)
{
    assert(cnt<8&&x>=0&&x<chessX&&y>=0&&y<chessY);
    switch(cnt)
    {
        case 0:
            return (x+1<chessX)&&(y+2<chessY);
        case 1:
            return (x+2<chessX)&&(y+1<chessY);
        case 2:
            return (x+2<chessX)&&(y-1>=0);
        case 3:
            return (x+1<chessX)&&(y-2>=0);
        case 4:
            return (x-1>=0)&&(y-2>=0);
        case 5:
            return (x-2>=0)&&(y-1>=0);
        case 6:
            return (x-2>=0)&&(y+1<chessY);
        case 7:
            return (x-1>=0)&&(y+2<chessY);
        default:
            cerr << "error:isInChess" << endl;
            return 0;
    }
}

bool isNeverRun(int x, int y, int cnt)
{
    switch (cnt)
    {
        case 0:
            return !chess[x+1][y+2];
        case 1:
            return !chess[x+2][y+1];
        case 2:
            return !chess[x+2][y-1];
        case 3:
            return !chess[x+1][y-2];
        case 4:
            return !chess[x-1][y-2];
        case 5:
            return !chess[x-2][y-1];
        case 6:
            return !chess[x-2][y+1];
        case 7:
            return !chess[x-1][y+2];
        default:
            return false;
    }
}

Id next(int x, int y, int cnt)
{
    switch (cnt)
    {
        case 0:
            return Id(x+1,y+2);
        case 1:
            return Id(x+2,y+1);
        case 2:
            return Id(x+2,y-1);
        case 3:
            return Id(x+1,y-2);
        case 4:
            return Id(x-1,y-2);
        case 5:
            return Id(x-2,y-1);
        case 6:
            return Id(x-2,y+1);
        case 7:
            return Id(x-1,y+2);
        default:
            cerr << "next func error";
            return Id(x,y);
    }
}
