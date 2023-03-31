/*
Sample Input
(2 (6 (7)) (3) (5 (1) (4)) (8))
(1 (2 (3)))
(6 (1 (4)) (2 (3) (5)))
Sample Output
5 2 5 2 6 2 8
2 3
2 1 6 2 6
*/

#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <string>
#include <string.h>
#include <set>
using namespace std;
vector<set<int>> vec(100); // 邻接表
priority_queue<int, vector<int>, greater<int>> leafs;

void init(string s)
{
    for (int i = 0; i < 55; i++)
    {
        vec[i].clear();
    }
    while (!leafs.empty())
    {
        leafs.pop();
    }
    stack<int> stk;
    int i = 0;
    while (i < s.size())
    {
        if (s[i] == '(')
        {
            i++;
            int num = 0;
            while (s[i] != ' ' && s[i] != ')') // 读取父节点的标号
            {
                num = num * 10 + s[i] - '0';
                i++;
            }
            stk.push(num); // 将父节点的标号压入栈中
        }
        else if (s[i] == ')')
        {
            int num1 = stk.top();
            stk.pop();
            if (vec[num1].size() == 0) // 叶子节点
                leafs.push(num1);
            if (stk.empty())
            {
                break;
            }
            int num2 = stk.top(); // 注意这里没有pop
            vec[num2].insert(num1);
            vec[num1].insert(num2);
            i++;
        }
        else
            i++;
    }
    if (vec[s[1] - '0'].size() == 1) // 特殊判断一下第一个节点
        leafs.push(s[1] - '0');
}

int main()
{
    string s;
    while (getline(cin, s))
    {
        // if (s.size() == 0)
        //     continue;
        init(s);
        if (leafs.size() <= 1 || s.size() == 0)
        {
            cout << endl;
            continue;
        }
        // 统计节点数
        int cnt = 0;
        for (int i = 0; i < 55; i++)
        {
            if (vec[i].size() > 0)
                cnt++;
        }
        do
        {
            int num1 = leafs.top(); // 最小编号的叶子节点
            leafs.pop();
            int num2 = *vec[num1].begin();
            cout << num2;
            cnt--;
            if (cnt > 1)
                cout << " ";
            vec[num2].erase(num1);
            if (vec[num2].size() == 1) // 叶子节点
                leafs.push(num2);
        } while (leafs.size() > 1);
        cout << endl;
        leafs.pop();
    }
}