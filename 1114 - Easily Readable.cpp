#include <bits/stdc++.h>
using namespace std;

struct Node {
    int count;
    map<char, Node*> nodeMap;

    Node()
    {
        count = 0;
    }
} * root;

int trie_search(string str)
{
    int len = str.size();

    vector<char> tokens;

    for (int i = 1; i < len - 1; i++)
        tokens.push_back(str[i]);

    sort(tokens.begin(), tokens.end());

    for (int i = 1; i < len - 1; i++)
        str[i] = tokens[i - 1];

    tokens.clear();
    Node* currentNode = root;

    for (int i = 0; i < len; i++) {

        map<char, Node*>::iterator iter = currentNode->nodeMap.find(str[i]);
        if (iter == currentNode->nodeMap.end()) {
            return 0;
        }

        currentNode = currentNode->nodeMap[str[i]];
    }

    return currentNode->count;
}

void del(Node* cur)
{

    if (cur->nodeMap.empty() != true) {

        map<char, Node*>::iterator iter;

        for (iter = cur->nodeMap.begin(); iter != cur->nodeMap.end(); iter++) {

            del(iter->second);
        }
    }

    delete (cur);
}

int main(void)
{

    int T, N, M, caseno = 0;

    scanf("%d\n", &T);
    char str[200 + 5];

    while (T--) {

        root = new Node();
        scanf("%d\n", &N);

        for (int i = 0; i < N; i++) {
            scanf("%s", str);

            vector<char> tokens;
            int len = strlen(str);

            for (int j = 1; j < len - 1; j++)
                tokens.push_back(str[j]);

            sort(tokens.begin(), tokens.end());

            for (int j = 1; j < len - 1; j++)
                str[j] = tokens[j - 1];

            tokens.clear();

            Node* currentNode = root;

            for (int i = 0; i < len; i++) {
                if (currentNode->nodeMap.find(str[i]) == currentNode->nodeMap.end()) {

                    currentNode->nodeMap[str[i]] = new Node();
                }
                currentNode = currentNode->nodeMap[str[i]];
            }
            currentNode->count++;
        }

        scanf("%d\n", &M);
        printf("Case %d:\n", ++caseno);

        char big_str[100000 + 5];

        for (int i = 0; i < M; i++) {
            gets(big_str);

            int len = strlen(big_str);
            int mult = 1;
            string temp = "";

            for (int j = 0; j < len; j++) {
                if (big_str[j] == ' ')
                    continue;

                temp += char(big_str[j]);

                if (big_str[j + 1] == ' ' || j + 1 == len) {
                    if (temp != "")
                        mult *= trie_search(temp);
                    temp = "";
                    j++;
                }
            }

            printf("%d\n", mult);
        }

        del(root);
    }

    return 0;
}