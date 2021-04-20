#include "assert.h" 
#include "dlist_f.h"
/****************************************************************************/
/*********************************** TODO ***********************************/
/******************** Start your code in the following **********************/
/****************************************************************************/

/* Ex 5 */
template<class T> void DList<T>::reverse(void){
    node<T>* temp;
    node<T>* next;
    node<T>* current = dummy->getnext();
    int length = this->getlength();
    for (int i=1;i <= length;i++){
        next = current->getnext();
        temp = current->getprevious();
        current->setnext(temp);
        current->setprevious(next);
    }
    return ;

}