#include "SkipList.hpp"
/***********************************************************/
/********************** PROVIDED FUNCTIONS *****************/
/***********************************************************/
void SkipList::init(int maxHeight) {
    m_maxHeight = maxHeight;
    m_head = new SkipListNode("", m_maxHeight);
}

SkipList::~SkipList() {
    while (m_head != NULL) {
        SkipListNode* head = m_head;
        m_head = m_head->nextAtLevel(0);
        delete head;
    }
}

int SkipList::add(const Key& key, bool verbose) {
    if (find(key, false) != 0) {
        if (verbose) {
            cout<<"Node "<<key<<" is already in the list."<<endl;
        }
        return 0;
    }

    SkipListNode* newNode = new SkipListNode(key, randHeight());
    if (verbose) {
        cout<<"Add new node "<<*newNode<<" with height "<<newNode->height()<<endl;
    }
    int ret = add (m_head, newNode, m_maxHeight-1);
    if (ret == 0 ) {
        return ret;
    }
    return 1;
}

int SkipList::find(const Key &key, bool verbose) {
    SkipListNode* ret =find (m_head, key, m_maxHeight-1) ;
    if (ret == NULL) {
        if (verbose) {
            cout<< "Node "<<key<<" is not in the list"<<endl;
        }
        return 0;
    } else {
        if (verbose) {
            cout<< "Node "<<key<<" is in the list"<<endl;
        }
        return 1;
    }

}
int SkipList::del(const Key& key, bool verbose) {
    if (key.length() == 0){
      return 1;
    }
    SkipListNode* toBeDeleted  = del(m_head, key, m_maxHeight-1);

    if (toBeDeleted == NULL) {
        if (verbose) {
            cout<< "Node "<<key<<" is not in the list"<<endl;
        }
    } else {
        delete toBeDeleted;
        if (verbose) {
            cout<< "Node "<<key<<" is deleted from the list"<<endl;
        }
    }
    return 1;
}

void SkipList::dump(char sep) {
    int length = -1;
    cout<<"Current List: ";
    for ( SkipListNode* iter = m_head; (iter != NULL); iter=iter->nextAtLevel(0)) {
        length++;
        cout << string(*iter)<<" ";
        cout <<"("<< iter->height() <<":";
        unsigned int i;
        for (i=0; i< iter->height(); i++) {
            if (iter->nextAtLevel(i)) {
                cout<<" "<<i<<":"<<*(iter->nextAtLevel(i));
                cout.flush();
            }
        }
        cout<<")"<<sep;
    }
    cout<<length<<" nodes in total."<<endl;
}


/***********************************************************/
/***************  FUNCTIONS TO BE COMPLETED  ****************/
/***********************************************************/

/////////////////////////////////////////////////////////////
/////////////////////  ADD FUNCTIONS ////////////////////////
/////////////////////////////////////////////////////////////

unsigned int SkipList::randHeight() {
    ////////////// Write your code below  ////////////////////////
    int t = rand();
    unsigned int i;
    int j;
    for ( i = 1, j = 2; i < m_maxHeight; ++i, j+=j ) {
        if ( t > RAND_MAX/j ) {
            break;
        }
    }
    return i;
}


int SkipList::add(SkipListNode* target, SkipListNode* newNode, unsigned int level) {
    if (target->nextAtLevel(level) != NULL &&
            (*target->nextAtLevel(level)) < *newNode) {
        countAdd++;
    }
    ////////////// Write your code below  ////////////////////////
    SkipListNode *tempNode = target->nextAtLevel(level);
    if ( tempNode == NULL || *newNode < *tempNode ) {
        if (level < newNode->height()) {
            newNode->setNextAtLevel(level, tempNode);
            target->setNextAtLevel(level, newNode);
        }
        if (level > 0) {
            add( target, newNode, level - 1 );
        }
        return 1;
    }
    /*if ( level < 0 ) {
        return 0; 
    }*/
    return add( tempNode, newNode, level );
}

/////////////////////////////////////////////////////////////
/////////////////////  FIND FUNCTION ////////////////////////
/////////////////////////////////////////////////////////////
SkipListNode* SkipList::find(SkipListNode* target, const Key& key, unsigned int level) {
    if (target->nextAtLevel(level) != NULL && *(target->nextAtLevel(level)) < key) {
        countFind++;
    }
    ////////////// Write your code below  ////////////////////////
    /*if ( target == NULL ) {
        return NULL;
    }*/
    if ( *target == key ) {
        return target;
    }
    SkipListNode *tempNode = target->nextAtLevel(level);
    if ( tempNode == NULL || key < *tempNode ) {
        if ( level == 0 ) {
            return NULL;
        }
        return find( target, key, level - 1 );
    }
    return find( tempNode, key, level );
}


/////////////////////////////////////////////////////////////
/////////////////////  DEL FUNCTION ////////////////////////
/////////////////////////////////////////////////////////////
SkipListNode* SkipList::del(SkipListNode* target, const Key& key, unsigned int level) {
    if (target->nextAtLevel(level) != NULL && *(target->nextAtLevel(level)) < key) {
        countDelete++;
    }
    ////////////// Write your code below  ////////////////////////
    /*if ( find( key, false ) != 1 ) {
        return NULL;
    }*/

    SkipListNode *tempNode = target->nextAtLevel( level );
    if ( tempNode == NULL || key < *tempNode ) {
        if ( level == 0 ) {
            return NULL;
        }
        return del( target, key, level - 1);
    }
    if ( key == *tempNode ) {
        target->setNextAtLevel( level, tempNode->nextAtLevel( level ) );
        if ( level > 0 ) {
            del( target, key, level - 1);
        }
        return tempNode;
    }
    return del ( tempNode, key, level );
}
