#include<bits/stdc++.h>
using namespace std;
 
struct Node {
 
    int count;
    map<char, Node*> MAP;
 
    Node(){
        count = 0;
    }
} * root;
 
 
int trie_search(string str){
 
    int LEN = str.size();
 
    vector<char> Tokens;
 
    for(int i=1; i<LEN-1; i++ )
            Tokens.push_back(str[i]);
 
    sort(Tokens.begin(), Tokens.end());
 
    for(int i=1; i<LEN-1; i++ )
            str[i] = Tokens[i-1];
 
    Tokens.clear();
    Node * currentNode= root;
 
    for(int i=0; i< LEN; i++){
 
        map<char, Node*> ::iterator iter = currentNode->MAP.find(str[i]);
        if(iter == currentNode->MAP.end()){
            return 0;
        }
 
        currentNode = currentNode->MAP[str[i]];
    }
 
    return currentNode->count;
}
 
void del(Node * cur){
 
    if(cur->MAP.empty() != true ){
 
            map<char, Node*> :: iterator iter;
 
            for(iter = cur->MAP.begin(); iter != cur->MAP.end(); iter++){
 
                del(iter->second);
            }
    }
 
    delete(cur);
 
}
 
 
 
int main(void){
 
    int T, N , M , caseno=0;
 
    scanf("%d\n",&T);
    char str[200+5];
 
 
    while(T--){
 
        root = new Node();
        scanf("%d\n",&N);
 
        for(int i=0; i< N ; i++){
 
            scanf("%s",str);
 
            vector<char> Tokens;
            int len = strlen(str);
 
            for(int j=1; j<len-1; j++)
                    Tokens.push_back(str[j]);
 
 
 
            sort(Tokens.begin(), Tokens.end());
 
            for(int j=1; j<len-1; j++)
                    str[j] = Tokens[j-1];
 
 
            Tokens.clear();
 
            Node* currentNode = root;
 
            for(int i=0; i< len; i++){
 
                if(currentNode->MAP.find(str[i]) == currentNode->MAP.end() ){
 
                    currentNode->MAP[str[i]]  = new Node();
                }
 
                currentNode = currentNode->MAP[str[i]];
 
            }
 
            currentNode->count++;
        }
 
 
     scanf("%d\n",&M);
 
     printf("Case %d:\n",++caseno);
 
 
    char big_str[100000 + 5];
 
        for(int i=0; i<M; i++){
 
            gets(big_str);
 
            int len = strlen(big_str);
            int mult = 1;
            string temp = "";
 
            for(int j=0; j<len; j++){
 
                if(big_str[j] == ' ' )
                    continue;
 
                temp+=char(big_str[j]);
 
                if(big_str[j+1] ==' ' || j+1 == len){
                       if(temp != "")
                            mult *= trie_search(temp);
                        temp="";
                        j++;
                }
 
            }
 
            printf("%d\n", mult);
        }
 
        del(root);
    }
 
    return 0;
}