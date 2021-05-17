/*
*    BPlusTree.h
*
*    By: Alex Ruth
*    Github: AlexanderRuth
*
*    Templated C++ implementation of a B+ Tree
*    View documentation at https://github.com/AlexanderRuth/BPlusTree
*/

#ifndef BTREE_H
#define BTREE_H

#include <vector>
#include <tuple>
#include <iostream>

#define BLOCK_SIZE 4096 //Block size in bytes

using namespace std;

template <class K, class T> class OverflowBlock;

template <class K, class T>
class BTree {
    public:
        template<class Y, class Z> friend class OverflowBlock;
        struct DataNode_t; //Forward declare

        //This is the meat of each node. Each node is a vector of
        //data_entry's.
        //
        // 0 = Pointer to left node
        // 1 = Key for the given entry
        // 2 = Pointer to actual data (only for leaf nodes)
        // 3 = Pointer to right node
        typedef tuple<struct DataNode_t*, K, T, struct DataNode_t*>
            data_entry;
        
        //A struct that holds a vector of data entries
        //Local to the given templated version of the BTree

        struct DataNode_t{
            vector< data_entry > m_entries; //List of data_entry's

            int m_num_entries;        //Number of
                            //valid entries
            
            struct DataNode_t* m_right;    //Pointer to its
                            //right neighbor
                        
            int m_max_entries;        //Max number of
                            //possible entries

            bool m_is_leaf;            //Is the node a leaf?
            OverflowBlock<K,T> *overflow_block; // the inserted data first in the overflow block

            //Constructor
            //
            //Takes max number of entries,
            //and sets values to default
            DataNode_t(int max_entries, bool is_leaf)
                : m_num_entries(0),
                  m_right(NULL),
                  m_is_leaf(is_leaf)
            {
                m_entries.resize(max_entries);
                m_max_entries = max_entries;
                // the size of the overflow block is 1/5 of the main block
                overflow_block = new OverflowBlock<K,T>(5);
            }

            //next()
            //
            //Get a pointer to the next level of nodes
            //based on the key
            //NOTE: Returns NULL if at a leaf
            struct DataNode_t* next(K key)
            {
                int i;        //Loop counter
                K cur_key;    //Current key being checked
            
                //If there are no entries,
                //then the tree is empty and this is the root
                if(m_num_entries == 0)
                    return NULL;

                //Find the pointer in the middle of two keys
                for(i = 0; i < m_num_entries; i++){
                    cur_key = get<1>(m_entries.at(i));
                    
                    if(cur_key > key)
                        return get<0>(m_entries.at(i));
                    if(cur_key == key)
                        return get<3>(m_entries.at(i));
                }

                //If greater than every key,
                //return rightmost pointer
                i--;
                return get<3>(m_entries.at(i));
            }

            //retrieve()
            //
            //Retrieve a T pointer if it exists in the given node
            //NOTE: Should only be used on leaf nodes
            bool retrieve(K key, T &storage)
            {
                int i;
                
                if(m_num_entries == 0)
                    return false;
                    
                for(i = 0; i < m_num_entries; i++)
                    if(key == get<1>(m_entries.at(i))){
                        storage = get<2>(m_entries.at(i));
                        return true;
                    }
                
                // check the overflow block as well
                for(i = 0; i < this->overflow_block->num; i++) {
                    if (key == this->overflow_block->key[i]) {
                        storage = this->overflow_block->record[i];
                        return true;
                    }
                }
                
                return false;
            }

            //insert()
            //
            //Insert an entry, returns true if succesful,
            //false otherwise
            bool insert(data_entry entry)
            {
                int i;        //Loop counter
                K cur_key;    //Current node key
                int index;    //Found index

                //If there are no entries, insert at index 0
                if(!m_num_entries){
                    index = 0;
                }

                //Otherwise, find correct location
                else{
            
                    //Search for index
                    for(i = 0; i < m_num_entries; i++){
                        cur_key =
                            get<1>(m_entries.at(i));
                    
                        if(get<1>(entry) <= cur_key)
                            break;
                    }

                    index = i;
                }

                //Insert the entry at the given index
                m_num_entries++;
                m_entries.insert(m_entries.begin()+index,
                            entry);

                //Update the pointers to the left and
                //right entries, if they exist
                if(index != 0)
                    get<3>(m_entries.at(index-1)) =
                        get<0>(entry);
                if(index != m_num_entries-1)
                    get<0>(m_entries.at(index+1)) =
                        get<3>(entry);

                //Insert successful!
                return true;
            }

            //remove()
            //
            //Remove a leaf entry based on a key
            bool remove(K key, T &storage)
            {
                int i;        //Loop counter
                K cur_key;    //Current node key

                //If not a leaf node, do not delete
                //(Since no coalescing)
                if(!m_num_entries || !m_is_leaf)
                    return false;

                //Find a matching key
                for(i = 0; i < m_num_entries; i++){
                    cur_key = get<1>(m_entries.at(i));
                    
                    if(cur_key == key){
                    
                        //Get the stored data
                        storage = get<2>(m_entries.at(i));

                        //Erase the entry
                        m_entries.erase(
                            m_entries.begin() + i);
                        
                        m_num_entries--;

                        return true;
                    }
                }
                
                // check the overflow block as well
                for(i = 0; i < this->overflow_block->num; i++) {
                    cur_key = this->overflow_block->key[i];
                    if(cur_key == key) {
                        storage = this->overflow_block->record[i];
                        for(int j = i; j < this->overflow_block->num-1; j++) {
                            this->overflow_block->key[j] = this->overflow_block->key[j+1];
                            this->overflow_block->record[j] = this->overflow_block->record[j+1];
                        }
                        this->overflow_block->num--;
                        return true;
                    }
                }

                //No match found
                return false;
            }

            //mid_entry()
            //
            //Returns he middle entry of the data node
            data_entry mid_entry()
            {
                return m_entries.at(m_num_entries / 2 + 1);
            }

            //is_full()
            //
            //Is the data node full?
            bool is_full() {return m_num_entries >= m_max_entries;}

            //inorder()
            //
            //Print the entries in the node in sorted order
            void inorder()
            {
                for(int i = 0; i < m_num_entries; i++)
                    cout << "[i=" << i << " k="
                    << get<1>(m_entries.at(i)) << "]";
                cout << endl;
            }

        };
        typedef struct DataNode_t DataNode;

        //Public methods

        BTree();            //Default Constructor
        BTree(int);            //Constructor with user
                        //defined block size
        bool insert(K, const T&);    //Insert into the B+ Tree
        bool remove(K, T&);        //Remove from the B+ Tree
        void inorder(int);        //Print contents of the B+ Tree
        bool retrieve(K, T&);        //Get a given entry
        int depth();            //Return the depth of the tree
        ~BTree();            //Deconstructor

    private:
        
        //Members

        DataNode *m_root;        //Root of the tree
        const int m_block_size;        //Block size for each node
        const int m_max_entries;    //Max entries for each node
        int m_depth;            //Current depth (starts at 0)

        //Super secret methods

        bool insert_recursive(DataNode*, K, const T &, data_entry&);
        bool retrieve_recursive(K, DataNode*, T&);
        void split(DataNode*, bool, data_entry&);
        void delete_recursive(DataNode*);
};






template <class K, class T> class OverflowBlock {
    template<class X,class Y> friend class BTree;
public:
    OverflowBlock(int blocksize = 10);
    void insert(K k, T rcd);
    int size;
    int num;
private:
    K *key;
    T *record;
};


#endif
