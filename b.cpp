#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
using namespace std;
priority_queue<int> Q; // 优先队列，用于快速取出度为1的最小结点
const int maxn = 105;
set<int> S[maxn]; // 存放每一个结点的相连结点
int n = 0;        // 结点总数
int floors;       // 当前结点所在的层数
void init()
{
    for (int i = 0; i < maxn; i++)
        S[i].clear();
    while (!Q.empty())
        Q.pop();
    n = 0;
    floors = 0;
}
int main()
{
    char str;
    int t[maxn]; // 记录每一层当前的编号（遇到同层结点则被覆盖）
    while (scanf("%c", &str) != EOF)
    {
        init();
        // 处理输入
        while (str != '\n')
        {
            if (str == '(')
                floors++; // 左右括号决定树层数的增减
            else if (str == ')')
                floors--;
            else if (str >= '0' && str <= '9')
            {
                int a = str - '0'; // 结点编号
                while (true)
                {
                    scanf("%c", &str);
                    if (str >= '0' && str <= '9')
                        a = a * 10 + str - '0';
                    else
                        break;
                }
                n++;
                t[floors] = a; // 将当前层数的结点编号覆盖
                if (floors > 1)
                { // 若层数大于1，则与上一次的结点构成边
                    S[a].insert(t[floors - 1]);
                    S[t[floors - 1]].insert(a);
                }
                continue;
            }
            scanf("%c", &str);
        }

        // 将度为1的结点入队
        for (int i = 1; i <= n; i++)
        {
            if (S[i].size() == 1)
                Q.push(-i);
            // 将所有度为1的结点入队，由于我采用的是最大堆优先队列，为了能构成最小堆效果，故将编号的相反数入库
        }

        // 开始计算Prufer序列
        for (int k = 1; k < n; k++)
        {
            int now = -Q.top();
            Q.pop();
            int b = *S[now].begin(); // 由于只有一个元素，则不使用迭代器，可直接利用begin找到元素所在位置
            S[b].erase(now);         // 将结点b里的now元素删除

            cout << b;
            if (k < n - 1)
                cout << " ";

            if (S[b].size() == 1)
                Q.push(-b); // 若度为1，入队
        }
        cout << endl;
    }
    return 0;
}
