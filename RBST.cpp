#include "RBST.hpp"
/***********************************************************/
/******************* PROVIDED FUNCTIONS ********************/
/***********************************************************/

int RBST::add(const Key& key, bool verbose) {
    unsigned int oldSize = m_size;
    m_head = randomAdd(m_head, key);
    if (m_size > oldSize) {
        if (verbose) {
            cout<<"Node "<<key<< " is added into the tree."<<endl;
        }
        return 1;
    } else {
        if (verbose) {
            cout<<"Node "<<key<< " is already in the tree."<<endl;
        }
        return 0;
    }
    if (verbose) cout<<endl;
};

int RBST::del(const Key& key, bool verbose) {
    unsigned oldSize= m_size;
    m_head = del(m_head, key);
    if (m_size < oldSize) {
        if (verbose) {
            cout<<"Node "<<key<< " is deleted from the tree."<<endl;
        }
        return 1;
    } else {
        if (verbose) {
            cout<< "Node "<<key<< " is not in the tree."<<endl;
        }
        return 0;
    }
};

int RBST::find(const Key& key, bool verbose) {
    RBSTNode* ret = find(m_head, key);
    if (ret == NULL) {
        if (verbose) {
            cout<< "Node "<<key<< " is not in the tree."<<endl;
        }
        return 0;
    } else {
        if (verbose) {
            cout<<"Node "<<key<< " is in the tree."<<endl;
        }
        return 1;
    }
};

int RBST::dump(char sep) {
    int ret = dump(m_head, sep);
    cout<<"SIZE: " <<ret<<endl;
    return ret;
};

int RBST::dump(RBSTNode* target, char sep) {
    if (target == NULL) {
        return 0;
    }
    int ret = dump(target->left(), sep);
    cout<< *target<<sep;
    ret ++;
    ret += dump(target->right(), sep);
    return ret;
};



/***********************************************************/
/****************  FUNCTIONS TO BE COMPLETED  ***************/
/***********************************************************/


/////////////////////////////////////////////////////////////
/////////////////////  ADD FUNCTIONS ////////////////////////
/////////////////////////////////////////////////////////////

RBSTNode*  RBST::rightRotate(RBSTNode* target) {
    ////////////// Write your code below  ////////////////////////
    RBSTNode *tempNode = target->left();
    target->setLeft( tempNode->right() );
    tempNode->setRight( target );
    return tempNode;
};

RBSTNode*  RBST::leftRotate(RBSTNode* target) {
    ////////////// Write your code below  ////////////////////////
    RBSTNode *tempNode = target->right();
    target->setRight( tempNode->left() );
    tempNode->setLeft( target );
    return tempNode;
};

RBSTNode* RBST::addRoot(RBSTNode* target, const Key& key) {
    countAdd++;
    ////////////// Write your code below  ////////////////////////
    if ( target == NULL ) {
        ++m_size;
        return new RBSTNode(key);
    }

    if ( key < *target ) {
        target->setLeft( addRoot( target->left(), key ) );
        return rightRotate( target );
    } else {
        target->setRight( addRoot( target->right(), key ) );
        return leftRotate( target );
    }
};


RBSTNode* RBST::randomAdd(RBSTNode* target, const Key& key) {
    countAdd++;
    ////////////// Write your code below  ////////////////////////
    if( target == NULL ) {
        ++m_size;
        return new RBSTNode(key);
    }
    
    int r = rand() % m_size;
    if ( r == 1 ) {
        return addRoot( target, key );
    }
    
    if ( key < *target ) {
        target->setLeft( randomAdd( target->left(), key ) );
    } else {
        target->setRight( randomAdd( target->right(), key ) );
    }
    return target;
};


/////////////////////////////////////////////////////////////
/////////////////////  FIND FUNCTIONS ///////////////////////
/////////////////////////////////////////////////////////////

RBSTNode* RBST::find(RBSTNode* target, const Key& key) {
    countFind++;
    ////////////// Write your code below  ////////////////////////
    if( target == NULL ) {
        return NULL;
    }

    if( key == *target ) {
        return target;
    } else if ( key < *target ) {
        return find( target->left(), key );
    } else {
        return find( target->right(), key );
    }
};


/////////////////////////////////////////////////////////////
/////////////////////  DEL FUNCTIONS ////////////////////////
/////////////////////////////////////////////////////////////


RBSTNode* RBST::del(RBSTNode* target, const Key& key) {
    countDelete++;
    ////////////// Write your code below  ////////////////////////
    if ( target == NULL ) {
        return NULL;
    }
    if ( key == *target) {
        m_size--;
        if ( target->right() == NULL ) {
            return target->left();
        }
        RBSTNode *temp = delHelper(target->right());
        del_store->setLeft( target->left() );
        del_store->setRight( temp );
        return del_store;
    } else if ( key < *target ) {
        target->setLeft( del( target->left(), key ) );
    } else {
        target->setRight( del( target->right(), key ) );
    }
    return target;

};

RBSTNode* RBST::delHelper(RBSTNode* target) {
    if ( target->left() == NULL ) {
        del_store = target;
        return target->right();
    }

    target->setLeft( delHelper( target->left() ) );

    return target;
};