// The code of B+ tree is mainly from handerliu, https://blog.csdn.net/liu1064782986/article/details/7982290
// We add 5 functions in the B+ tree class, to complete the assignment

#ifndef BPLUS_TREE_H
#define BPLUS_TREE_H
 
#include "BPlus_node.h"
#include <vector>
using namespace std;
 
enum COMPARE_OPERATOR{LT, LE, EQ, BE, BT, BETWEEN}; // 比较操作符：<、<=、=、>=、>、<>
const int INVALID_INDEX = -1;
 
struct SelectResult
{
    int keyIndex;
    CLeafNode* targetNode;
};
 
class CBPlusTree{
public:
    CBPlusTree();
    ~CBPlusTree();
    bool insert(KeyType key, const DataType& data);
    bool remove(KeyType key);
    bool update(KeyType oldKey, KeyType newKey);
    // 定值查询，compareOperator可以是LT(<)、LE(<=)、EQ(=)、BE(>=)、BT(>)
    vector<DataType> select(KeyType compareKey, int compareOpeartor);
    // 范围查询，BETWEEN
    vector<DataType> select(KeyType smallKey, KeyType largeKey);
    bool search(KeyType key); // 查找是否存在
    void clear();             // 清空
    void print()const;        // 打印树关键字
    void printData()const;    // 打印数据
    
    // these are the functions required by CS hw8
    KeyType minimum(); // return the minimum key value in the tree
    KeyType maximum(); // return the maximum key value in the tree
    KeyType predecessor(KeyType key); // return the predecessor key value of the given key
    KeyType successor(KeyType key); // return the successor key value of the given key
private:
    void recursive_insert(CNode* parentNode, KeyType key, const DataType& data);
    void recursive_remove(CNode* parentNode, KeyType key);
    void printInConcavo(CNode *pNode, int count)const;
    bool recursive_search(CNode *pNode, KeyType key)const;
    void changeKey(CNode *pNode, KeyType oldKey, KeyType newKey);
    void search(KeyType key, SelectResult& result);
    void recursive_search(CNode* pNode, KeyType key, SelectResult& result);
    void remove(KeyType key, DataType& dataValue);
    void recursive_remove(CNode* parentNode, KeyType key, DataType& dataValue);
    
    CLeafNode *position_key(KeyType key);
private:
    CNode* m_Root;
    CLeafNode* m_DataHead;
    KeyType m_MaxKey;  // B+树中的最大键
};
 
#endif

