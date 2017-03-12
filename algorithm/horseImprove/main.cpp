/**
 * ��̤�����Ż���
 * 1.DFS����ԭ�еĽṹ���иĽ�
 * 2.ѡ����һ���ķ�ʽ��ȡ̰���㷨��������ÿһ����ѡ������һ���Ŀ�����λ������
 * λ�����ٵ��������ӡ�
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
int cnt = 0;//��ʾ��ȣ���ʾ�ߵĲ���
int fx[8] = {1,2,2,1,-1,-2,-2,-1};
int fy[8] = {2,1,-1,-2,-2,-1,1,2};
typedef int Direct;//�����µ��������ͣ������ʾ��0-8��ʾ8�����ӷ���
typedef multimap<int,Direct> nextMap;//���ÿ��λ����һ���������ȼ�������
typedef nextMap::iterator nIter;//�������������
bool run(int,int);//�ݹ�������
nextMap judge(int,int,int&,int&);//������һ������λ�õ����ȼ�,������keyvmin����keyֵ�ķ�0��Сֵ
bool isOk(int,int,Direct);//�ж������Ƿ���ã�1.û������2.û�г�������
int main()
{
    int x,y;
    vector<int> iveco;

    cout << "�������ʼ����x��" << "(x>=0&&x<" << chessX << ")" << endl;
    cin >> x;
    assert(x>=0&&x<chessX);
    cout << "�������ʼ����y: " << "(y>=0&&y<" << chessY << ")" <<endl;
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
         << "��" <<endl;
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
