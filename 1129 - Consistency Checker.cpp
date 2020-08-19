/*Skynet094*/
#include <bits/stdc++.h>
#define MAX 10000
#define dll long long int
#define REP(i, a, b) for (int i = a; i < b; i++)
using namespace std;

struct node {
    node* next[9 + 1];

    node()
    {
        for (int i = 0; i < 10; i++)
            next[i] = NULL;
    }
} * root;

void insert_to_trie(string str)
{
    node* curr = root;
    int len = str.size();

    for (int i = 0; i < len; i++) {
        int label = str[i] - '0';

        if (curr->next[label] == NULL)
            curr->next[label] = new node;

        curr = curr->next[label];
    }
}

bool search_in_trie(string str)
{
    node* curr = root;

    int len = str.size();

    for (int i = 0; i < len; i++) {
        int label = str[i] - '0';
        if (curr->next[label] == NULL)
            return false;

        curr = curr->next[label];
    }

    return true;
}

void del(node* curr)
{
    for (int i = 0; i < 10; i++) {
        if (curr->next[i])
            del(curr->next[i]);
    }
    delete (curr);
}

int main(void)
{
    string phone_numbers[MAX];
    string s;

    int testcase, n, caseno = 0;
    cin >> testcase;

    while (testcase--) {
        root = new node();
        cin >> n;

        REP(i, 0, n)
        cin >> phone_numbers[i];

        sort(phone_numbers, phone_numbers + n);
        reverse(phone_numbers, phone_numbers + n);
        insert_to_trie(phone_numbers[0]);

        int flag = 0;
        REP(i, 1, n)
        {
            if (search_in_trie(phone_numbers[i])) {
                flag = 1;
                break;
            }
            else
                insert_to_trie(phone_numbers[i]);
        }

        if (flag)
            cout << "Case " << ++caseno << ": "
                 << "NO\n";
        else
            cout << "Case " << ++caseno << ": "
                 << "YES\n";

        del(root);
    }

    return 0;
}
