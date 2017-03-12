/**
 * 马踏棋盘优化：
 * 1.DFS，对原有的结构进行改进
 * 2.选择下一步的方式采取贪婪算法，即考察每一个备选落子下一步的可落子位置数，
 * 位置数少的优先落子。
 */
#include <iostream>
#include <chrono>
#include <map>
#include <assert.h>
#include <vector>

using namespace std;

const int chessX = 8;
const int chessY = 8;
int chess[chessX][chessY] = {0};
int cnt = 0;//表示深度，表示走的步数
int fx[8] = {1,2,2,1,-1,-2,-2,-1};
int fy[8] = {2,1,-1,-2,-2,-1,1,2};
typedef int Direct;//定义新的数据类型，方便表示，0-8表示8个落子方向
typedef multimap<int,Direct> nextMap;//存放每个位置下一个落子优先级的数据
typedef nextMap::iterator nIter;//定义迭代器类型
bool run(int,int);//递归主函数
nextMap judge(int,int,int&,int&);//返回下一个落子位置的优先级,并且在keyvmin里存放key值的非0最小值
bool isOk(int,int,Direct);//判断坐标是否可用：1.没遍历过2.没有超出棋盘
int main()
{
    int x,y;
    vector<int> iveco;

    cout << "请输入初始坐标x：" << "(x>=0&&x<" << chessX << ")" << endl;
    cin >> x;
    assert(x>=0&&x<chessX);
    cout << "请输入初始坐标y: " << "(y>=0&&y<" << chessY << ")" <<endl;
    cin >> y;
    assert(y>=0&&y<chessY);
    auto start = chrono::system_clock::now();
    run(x,y);
    auto end = chrono::system_clock::now();
    auto duration = chrono::
    duration_cast<chrono::microseconds>(end-start);
    for(int i = 0;i<chessX;++i)
    {
        for(int j=0;j<chessY;++j)
            cout << chess[i][j] << '\t';
        cout << endl;
    }
    cout << double(duration.count())* chrono::microseconds::period::num
            /chrono::microseconds::period::den
         << "秒" <<endl;
    return 0;
}

bool run(int x, int y)
{
    int keyMin = 8;
    int keyMax = 0;
    bool finish;
    chess[x][y] = ++cnt;
    if(cnt>=chessX*chessY)
        return true;
    nextMap next = judge(x,y,keyMin,keyMax);
    for (int i = keyMin; i <= keyMax ; ++i)
    {
        if(next.count(i)!=0)
        {
            nIter beg = next.lower_bound(i);
            nIter end = next.upper_bound(i);
            for(nIter j = beg;j!=end;++j)
            {
                finish = run(x+fx[j->second],y+fy[j->second]);
                if(finish)
                    return true;
            }
        }
    }
    chess[x][y] = 0;
    --cnt;
    return false;
}

nextMap judge(int x, int y,int &keyMin,int &keyMax)
{
    nextMap res;
    keyMin = 8;
    keyMax = 0;
    for(int i=0;i<8;++i)
    {
        if(isOk(x,y,i))
        {
            int xx = x + fx[i];
            int yy = y + fy[i];
            int cnt = 0;
            for(int j=0;j<8;++j)
            {
                if(isOk(xx,yy,j))
                    ++cnt;
            }
            res.insert(make_pair(cnt,i));
            if(keyMin>cnt)
                keyMin = cnt;
            if(keyMax<cnt)
                keyMax = cnt;
        }
    }
    return res;
}

bool isOk(int x1, int y1,Direct direct)
{
    int x = x1+fx[direct];
    int y = y1+fy[direct];
    return chess[x][y] == 0 && x >= 0 && x < chessX && y >= 0 && y < chessY;
}
