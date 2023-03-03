#include<iostream>
#include<bits/stdc++.h>
using namespace std;
map< char, int> freq;
map<char, string> codes;
string encoding;
struct huffman {
    char data;
    int freq;
    huffman *left, *right;
    
    huffman(char data, int freq)
    {
        this->data=data;
        this->freq=freq;
        left =NULL;
        right=NULL;
    }
};
void calfreq(string str, int len)
{
    for(int i=0;i<len;i++)
    {
        freq[str[i]]++;
    }
}

void assigncodes(huffman *root , string str){
    if (root==NULL)
    return;
    if(root->data !='$')
    codes[root->data]=str;
    assigncodes(root->left, str+"0");
    assigncodes(root->right, str+"1");
}     //to assign the encoded codes

struct compare {
    bool operator()(huffman *left, huffman *right)
    {
        return (left->freq > right->freq);
    }// it tells whether we need to compare or not 
};
priority_queue<huffman*, vector<huffman*>, compare> minHeap;
//compare is a function which helps user to decide the priority according to which 
//element should be arranged in the queue. 
void print_code_with_huffman_string (){
    /*for(auto i:codes){
        for(auto j:i){
            cout<<i<<":"<<j<<endl;
        }
    }*/
    for(auto it:codes)
    cout<<it.first<<":"<<it.second<<endl;
}
void huffmanTree() 
{
    huffman *left,*right, *top;
    /*for(auto i: freq){
        for(auto j:i){
            minHeap.push(new huffman(i,j));
        }
    }*/
    for(auto it:freq)
    {
        minHeap.push(new huffman(it.first,it.second));
    }
    while(minHeap.size()!=1)// until minheap does not contain the one element i.e the root element
    {
        left=minHeap.top();
        minHeap.pop();
        right=minHeap.top();
        minHeap.pop();
        top = new huffman('$',left->freq+right->freq);
        top->left=left;
        top->right=right;
        minHeap.push(top);
    }
    assigncodes(top,"");
}
string encode (string str)
{
    //string encoding;
    for(auto it:str)
    {
        encoding+=codes[it];
    }
    return encoding;
}
string decode( huffman *root, string encoding){
    string ans="";
    huffman *temp = root;
    for(int i=0;i<encoding.size();i++)
    {
        if(encoding[i]=='0')
        temp=temp->left;
        else if(encoding[i]=='1')
        temp=temp->right;
        
        if(temp->left ==NULL && temp->right==NULL){
        ans+=temp->data;
        temp=root;//temp again should point to root coz it has reached to end and from there it can't go anywhere
        }
    }
    return ans+'\0';// so that cursor can go to next line it is like endl
}
int main()
{
    string str;
    cout<<"Enter the text to be compressed"<<endl;
    cin>>str;
    calfreq(str, str.length());
    huffmanTree();
    cout << "Characters in a string With there Frequencies:\n";
    print_code_with_huffman_string();
    cout << "\nHuffman Encoded string:\n";
    cout<<encode(str)<<endl;
    cout << "\nDecoded Huffman Data:\n";
    cout<<decode(minHeap.top(),encoding);
    
}
