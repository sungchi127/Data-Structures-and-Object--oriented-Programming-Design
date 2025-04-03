#include <deque>
#include <string>
#include <unordered_map>
#include <map>
#include<algorithm>
#include<iostream>
#include <queue>
using namespace std;
int sum;
string str;
class Node {
public:
    char val;
    int freq;
    Node* lchild;
    Node* rchild;

    Node(char _val, int _freq, Node* _lchild, Node* _rchild) {
        val = _val;
        freq = _freq;
        lchild = _lchild;
        rchild = _rchild;
    }
};
// 提供給sort函數使用

struct WTF_IS_THIS {
    bool operator() (const Node *child, const Node *parent) const {
        return child->freq > parent->freq;
    }
};

// bool operator > (const Node &lhs, const Node &rhs) {
//     return lhs.freq > rhs.freq;
// }

unordered_map<char, int> freq;  // 統計各個字元的出現次數
priority_queue<Node,deque<Node>,greater<Node>> q1;        // 儲存各節點之指標
priority_queue<Node*,deque<Node*>,WTF_IS_THIS> q;        // 儲存各節點之指標
map<char, string> dic;
string encode_result = "";

void planCode(Node *ptr, string s) {
    if(ptr->lchild == nullptr || ptr->rchild == nullptr) {
        //printf("'%c' (freq = %d) --> %s\n", ptr->val, freq[ptr->val], s.c_str());
        dic[ptr->val] = s;
        sum+=freq[ptr->val]*s.length();
        return;
    }

    // cout << (int)ptr.val << " " << ptr.freq << " > " << (int)ptr.lchild->val << "," << (int)ptr.rchild->val << "\n";

    if(ptr->lchild) planCode(ptr->lchild, string(s + "0"));
    if(ptr->rchild) planCode(ptr->rchild, string(s + "1"));
    
}

void encoding(string str){
    for(auto ch:str){
        encode_result += dic[ch];
        cout<<dic[ch];
    }
    cout<<endl;
}

void decoding(Node *ptr,int run){
        if(run==(int)encode_result.length()){
            return ;
        }
        //printf("%c\n" , [run]);
        if(ptr->lchild == nullptr || ptr->rchild == nullptr){
            // cout << run << endl;
            printf("%c", ptr->val);
            decoding(q.top(),run);
            return ;
        }
        if(encode_result[run] =='0') decoding(ptr->lchild,run+1);
        if(encode_result[run] =='1') decoding(ptr->rchild,run+1);
}
/*void decode() {
    Node *tmp = forest.front();
    string s;
    //cout << encode_result << endl;
    for(int i = 0; i < (int)encode_result.size(); i ++) {
        if(encode_result[i] == '0') {
            tmp = tmp->lchild;
        }
        if(encode_result[i] == '1') {
            tmp = tmp->rchild;
        }
        if(tmp->val != '\n'){
            printf("%c",tmp->val);
            tmp = forest.front();
            continue;
        }
    }
}*/

int main() {
    //統計各字元的出現頻率
    char c;
    cout<<"Enter characters:";
    while((c = getchar()) != EOF) {
        if(c == '\n') continue;
        if(freq.count(c)) freq[c]++;
        else freq[c] = 1;
        str+=c;
    }
    
    // 製作節點，並儲存到q之中
    for(auto it = freq.begin(); it != freq.end(); it++)
        q.push(new Node((*it).first, (*it).second, nullptr, nullptr));

    // 按照字元出現頻率排序q中的節點，取出出現頻率最小的兩個節點，將其合併，
    // 再儲存回q之中
    for(int i = 0; i < (int)freq.size()-1; i++) {
        Node *ptr1 = q.top(); q.pop(); //cout << (int)ptr1->val << " " << ptr1->freq << "\n";
        Node *ptr2 = q.top(); q.pop(); //cout << (int)ptr2->val << " " << ptr2->freq << "\n";
        Node *parentNode = new Node('\n', ptr1->freq + ptr2->freq, ptr1, ptr2);
        q.push(parentNode);
    }

    planCode(q.top(), string(""));

    printf("encoding result:");
    encoding(str);

    printf("code list{\n");
    for(auto it : dic){
        printf("%c: %s\n", it.first, it.second.c_str());
    }
    printf("}\n");    

    printf("WPL=%d\n",sum);

    cout<<"decoding result:";
    decoding(q.top(),0);
    //decode();
    cout<<endl;
    return 0;
}

//aaaaaaabbccdddeeeeeeeeeeeffgghhhhhhiiiiiijkllllmmmnnnnnnnoooooooooppqrrrrrrssssssttttttttuuuuvwwxyyz
//aabbbcccccccdddddddddddddddd
//iaaaaaaamhhhhannnnddsssomeeeee
//howwwarrreyooou