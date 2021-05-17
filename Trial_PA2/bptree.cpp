/*
*    BPlusTree.h
*
*    By: Alex Ruth
*    Github: AlexanderRuth
*
*    Templated C++ implementation of a B+ Tree
*    View documentation at https://github.com/AlexanderRuth/BPlusTree
*/

#include "bptree.h"

// constructor
template <class K, class T> OverflowBlock<K,T>::OverflowBlock(int blocksize) {
    num = 0;
    size = blocksize;
    key = new K[size];
    record = new T[size];
}

template <class K, class T> void OverflowBlock<K,T>::insert(K k, T rcd) {
    // we assume the overflow block is not full
    key[num] = k;
    record[num] = rcd;
    num++;
}





//Default constructor
//
//Use a default block size
template <class K, class T>
BTree<K,T>::BTree()
    : m_block_size(BLOCK_SIZE),
      m_max_entries(50), // you can alter this to change the number of data in every block
      m_depth(0)
{
    m_root = new DataNode(m_max_entries, true);
}

//Specific Constructor
//
//Use the specified block size
template <class K, class T>
BTree<K,T>::BTree(int block_size)
    : m_block_size(block_size),
      m_max_entries(block_size / sizeof(data_entry)),
      m_depth(0)
{
    m_root = new DataNode(m_max_entries, true);
}

//~BTree()
//
//Deconstructor
template <class K, class T>
BTree<K,T>::~BTree()
{
    //If root is not a leaf, then start traversing the left of the tree
    if(!m_root->m_is_leaf)
        delete_recursive(get<0>(m_root->m_entries.at(0)));

    delete m_root;
}

//delete_recursive()
//
//Recursive deletion, used by deconstructor
template <class K, class T>
void BTree<K,T>::delete_recursive(DataNode* curr)
{
    DataNode* tmp;    //Loop over data right nodes

    //If not leaf, keep going
    if(!curr->m_is_leaf)
        delete_recursive(get<0>(curr->m_entries.at(0)));

    //Delete the current level
    while(curr->m_right){
        tmp = curr->m_right;
        curr->m_entries.clear();
        delete curr;
        curr=tmp;
    }

    curr->m_entries.clear();
    delete curr;
}

//inorder()
//
//Print the contents of the tree
template <class K, class T>
void BTree<K,T>::inorder(int min)
{
    DataNode* curr;        //Current node
    DataNode* right;    //Node to the right
    int i = 0;        //Loop counter

    //Start a root
    curr = m_root;
    
    //Output depth along the way
    cout << "\nDEPTH=0" << endl << endl;
    curr->inorder();

    //While not at leaf
    while(curr->next(min)){

        //Output current level
        i++;
        curr = curr->next(0);
        cout << "\nDEPTH=" << i << endl << endl;
        curr->inorder();

        //Move along the right
        right = curr->m_right;
        while(right){
            right->inorder();
            right = right->m_right;
        }
    }
            
    cout << endl;
}

//insert()
//
//Insert the given data based on the key
template <class K, class T>
bool BTree<K,T>::insert(K key, const T &data)
{
    data_entry new_entry; //The entry to add
    
    //Set up the entry to add
    get<1>(new_entry)=key;
    get<2>(new_entry)=data;


    //If split propagates to the top of the tree,
    //make a new root
    if(insert_recursive(m_root, key, data, new_entry)){
        m_root = new DataNode(m_max_entries, false);
        m_root->insert(new_entry);

        m_depth++;

        return true;
    }
    return true;
}

//insert_recursive()
//
//Private. Recursive portion of the insert method
template <class K, class T>
bool BTree<K,T>::insert_recursive(DataNode *curr, K key, const T &data,
                    data_entry &entry)
{
    
    //If not at leaf, keep recursing
    if(curr->next(key)){
    
        //If split propagates up, insert entry and
        //split again as needed
        if(insert_recursive(curr->next(key), key, data, entry)){

            if(curr->is_full()){
                split(curr, false, entry);
                return true;
            }
            else{
                curr->insert(entry);
                
                return false;
            }
        }

        //Otherwise, did not split
        return false;
    }
    
    else{
        //At a leaf node, insert a new entry
        //If full, split, otherwise,
        //simply insert
        if(curr->is_full()){
            split(curr, true, entry);
            return true;
        }

        else{
            //curr->insert(entry);
            // insert the data into the overflow block first
            curr->overflow_block->insert(get<1>(entry), get<2>(entry));
            
            // if the overflow block is full, or the leaf node is full, sort and merge
            if ((curr->overflow_block->num == curr->overflow_block->size) || (curr->overflow_block->num+curr->m_num_entries == curr->m_max_entries)) {
                
                // sort the overflow block, using insertion sort
                for (int i = 0; i < curr->overflow_block->num-1; i++) {
                    K min = curr->overflow_block->key[i];
                    int pos = i;
                    for (int j = i+1; j < curr->overflow_block->num; j++) {
                        if (min > curr->overflow_block->key[j]) {
                            min = curr->overflow_block->key[j];
                            pos = j;
                        }
                    }
                    T rcd = curr->overflow_block->record[pos];
                    curr->overflow_block->key[pos] = curr->overflow_block->key[i];
                    curr->overflow_block->record[pos] = curr->overflow_block->record[i];
                    curr->overflow_block->key[i] = min;
                    curr->overflow_block->record[i] = rcd;
                }
                
                // merge the overflow block and the block
                int index = 0; // index is the cursor in the main block
                for (int i = 0; i < curr->overflow_block->num; i++) {
                    while (index < curr->m_num_entries) {
                        if (curr->overflow_block->key[i] <= get<1>(curr->m_entries.at(index))) {
                            break;
                        }
                        index++;
                    }
                    get<1>(entry) = curr->overflow_block->key[i];
                    get<2>(entry) = curr->overflow_block->record[i];
                    //Insert the entry at the given index
                    curr->m_num_entries++;
                    curr->m_entries.insert(curr->m_entries.begin()+index, entry);
                    //Update the pointers to the left and
                    //right entries, if they exist
                    /*if(index != 0) {
                        get<3>(curr->m_entries.at(index-1)) = get<0>(entry);
                    }
                    if(index != curr->m_num_entries-1) {
                        get<0>(curr->m_entries.at(index+1)) = get<3>(entry);
                    }*/
                }
                //clear the overflow block
                curr->overflow_block->num = 0;
            }
            return false;
        }
    }
}

//remove()
//
//Remove from the B+ Tree based on the key.
//Currently does not perform coalescing
//(may implement this later)
template <class K, class T>
bool BTree<K,T>::remove(K key, T &storage)
{
    //Traverse to the leaf node
    DataNode* curr = m_root;

    while(curr->next(key))
        curr = curr->next(key);

    //Remove the entry
    return curr->remove(key, storage);
}

//retrieve()
//
//Public wrapper around retrieve. Returns a pointer
//to the desired entry, or NULL if it does not exist
template <class K, class T>
bool BTree<K,T>::retrieve(K key, T &storage)
{
    //Start at root
    return retrieve_recursive(key, m_root, storage);
}

//retrieve_recursive()
//
//Recursive retrieve function
template <class K, class T>
bool BTree<K,T>::retrieve_recursive(K key, DataNode* curr, T &storage)
{
    //Keep going until at leaf, then retrieve
    //based on the given key
    if(!curr->next(key))
        return curr->retrieve(key, storage);
    else
        return retrieve_recursive(key, curr->next(key), storage);
}

//split()
//
//Split the passed DataNode into two, and set new_entry to the upwards
//propagated data entry
template <class K, class T>
void  BTree<K,T>::split(DataNode* to_split, bool is_leaf, data_entry &new_entry)
{
    int half_size = (m_max_entries) / 2;        //Half the size of
                            //DataNode
                            
    K mid_key;                    //The key in the middle

    DataNode* right_node =
        new DataNode(m_max_entries, is_leaf);    //Allocate a new node

    
    //Get the middle key
    mid_key = get<1>(to_split->m_entries.at(half_size));

    //Make the new node the right of the two, and fill its entries
    //If this is not the leaf node, ditch the middle key
    right_node->m_entries = vector<data_entry>(
        to_split->m_entries.begin() + half_size + (is_leaf ? 0 : 1),
        to_split->m_entries.begin() + m_max_entries
    );

    //Set proper member variables
    right_node->m_num_entries = right_node->m_entries.size();
    right_node->m_entries.resize(m_max_entries);
    right_node->m_right = to_split->m_right;

    //Make the original node the left of the two, and fill its entries
    to_split->m_entries = vector<data_entry>(
        to_split->m_entries.begin(),
        to_split->m_entries.begin() + half_size
    );

    //Set proper member variables
    to_split->m_num_entries = to_split->m_entries.size();
    to_split->m_entries.resize(m_max_entries);
    to_split->m_right = right_node;

    //Insert the new entry in the proper node of the two
    if(mid_key < get<1>(new_entry))
        right_node->insert(new_entry);
    else
        to_split->insert(new_entry);

    //Set up the new entry to propagate upwards.
    //It points to the two split nodes, and its
    //key was the middle key of the original node
    get<0>(new_entry)=to_split;
    get<1>(new_entry)=mid_key;
    get<3>(new_entry)=right_node;
}

//depth()
//
//Return the depth of the tree
template <class K, class T>
int BTree<K,T>::depth() {return m_depth;}
