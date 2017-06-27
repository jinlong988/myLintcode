#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_
#include <iostream>
#include <limits.h>

template<class T>
class ListNode {
    public :
        T data;
        ListNode *next;
        ListNode(T val) : data(val), next(NULL) {};
};

template<class T>
class LinkedList {
    private :
        ListNode<T> *head;
        void reverse(ListNode<T> *, ListNode<T> *);
        void insertionSort();
        void insertionSortRecursion(ListNode<T> *, ListNode<T> *);
        void selectionSort();
        void selectionSortRecursion(ListNode<T> *, ListNode<T> *);
        void bubbleSort();
        void bubbleSortRecursion(ListNode<T> *);
        ListNode<T> *merge(ListNode<T> *, ListNode<T> *);
        ListNode<T> *mergeSortRecursion(ListNode<T> *);
        void quickSortRecursion(ListNode<T> *, ListNode<T> *);
        ListNode<T> *partition(ListNode<T> *, ListNode<T> *);
        void split(ListNode<T> *, ListNode<T> **, ListNode<T> **);  
    public :    
        LinkedList();
        //LinkedList(std::istream &);
        ~LinkedList();

        LinkedList(const LinkedList &);
        void push(T);
        void pop();
        void swap(ListNode<T> **, ListNode<T> **);
        void append(T);
        void printList();
        void reverse();
        void reverse(ListNode<T> *);
        void reverse(int m, int n);
        void selectionSort(bool);
        void insertionSort(bool);
        void bubbleSort(bool recursive = true);
        void mergeSort();
        void quickSort();
        void setListHead(const ListNode<T> *p) { head = const_cast<ListNode<T> *> (p) ;}
        ListNode<T> * getListHead() { return head; }
};

template<class T> LinkedList<T>::LinkedList() : head(NULL) {
    std::cout << "creating linkedlist ... " << std::endl;
    T i;
    while (std::cin >> i) {
        append(i);
    }
    std::cin.clear(); 
}

template<class T> void LinkedList<T>::pop() {
    ListNode<T> *tmp = head;
    head = head->next;
    delete tmp;
}

template<class T> void LinkedList<T>::swap(ListNode<T> **left, ListNode<T> **right) {
    ListNode<T> *tmp = *left;
    *left = *right;
    *right = tmp;
}

template<class T> void LinkedList<T>::selectionSort() {
   push(0);
   ListNode<T> *prev = head;
   ListNode<T> *cur = head->next;
   while (cur != NULL) {
       ListNode<T> *index = cur->next;
       ListNode<T> *prev_index = cur; 
       ListNode<T> *min = cur;
       ListNode<T> *prev_min = prev;
       T min_val = cur->data;
       while (index != NULL) {
           if (index->data < min_val) {
               min_val = index->data;
               min = index;
               prev_min = prev_index;
           }
           index = index->next;
           prev_index = prev_index->next;
       }
       swap(&prev->next, &prev_min->next);
       swap(&cur->next, &min->next);
       swap(&cur, &min);
       cur = cur->next;
       prev = prev->next;
   } 
   pop();
}

template<class T> void LinkedList<T>::selectionSortRecursion(ListNode<T> *start, ListNode<T> *prev) {
    if (start == NULL) {
        return;
    }

    T min = start->data;
    ListNode<T> *min_idx = start;
    ListNode<T> *min_prev = prev;

    ListNode<T> *idx = start;
    ListNode<T> *idx_prev = prev;
    while (idx != NULL) {
        if (min > idx->data) {
            min = idx->data;
            min_idx = idx;
            min_prev = idx_prev;
        }
        idx= idx->next;
        idx_prev = idx_prev->next;
    }
    
    swap(&prev->next, &min_prev->next);
    swap(&start->next, &min_idx->next);
    swap(&start, &min_idx);

    selectionSortRecursion(start->next, prev->next);
}

template<class T> void LinkedList<T>::insertionSort() {
    if (head != NULL && head->next != NULL) {
        ListNode<T> *unsorted = head->next->next;
        ListNode<T> *unsorted_prev = head->next;

        while (unsorted != NULL) {
            ListNode<T> *sorted = head->next;
            ListNode<T> *sorted_prev = head;
            bool flag = true;
            while (sorted != unsorted) {
                if (sorted->data > unsorted->data) {
                    sorted_prev->next = unsorted;
                    unsorted_prev->next = unsorted->next;
                    unsorted->next= sorted; 
                    unsorted = unsorted_prev->next;
                    flag = false;
                    break;
                }
                sorted = sorted->next;
                sorted_prev = sorted_prev->next;
            }
            if (flag) {
                unsorted= unsorted->next;
                unsorted_prev = unsorted_prev->next;
            }
        }
    }
}


template<class T> void LinkedList<T>::selectionSort(bool recursive) {
    push(0);
    if (recursive) {
        selectionSortRecursion(head->next, head);
    } else { 
        selectionSort();
    }
    pop();
}

template<class T> void LinkedList<T>::insertionSort(bool recursive) {
    push(0);
    if (recursive) {
        insertionSortRecursion(head->next, head);
    } else {
        insertionSort();
    }
    pop();
}

template<class T> void LinkedList<T>::insertionSortRecursion(ListNode<T> *start, ListNode<T> *prev){
    if (start == NULL) {
       return ;
    } 
    ListNode<T> *idx_prev = head;
    ListNode<T> *idx = head->next;
    while (idx != start) {
        if (idx->data > start->data) {
            prev->next= start->next;
            idx_prev->next = start;
            start->next = idx;
            start = prev->next;
            insertionSortRecursion(start, prev);
            return;
        }
        idx = idx->next;
        idx_prev = idx_prev->next;
    }
    insertionSortRecursion(start->next,prev->next);
}

template<class T> void LinkedList<T>::bubbleSort(bool recursive) {
    push(0);
    if (recursive) {
        bubbleSortRecursion(NULL);
    }
    pop();
}

template<class T> void LinkedList<T>::bubbleSortRecursion(ListNode<T> *end) {
    if (head->next == end) {
        return;
    }
    ListNode<T> *idx = head->next;
    ListNode<T> *idx_prev = head;
    while (idx->next != end) {
        if (idx->data > idx->next->data) {
            ListNode<T> *tmp = idx->next;
            swap(&idx_prev->next, &idx->next);
            swap(&idx->next, &tmp->next);
            idx_prev = idx_prev->next;
        } else {
            idx = idx->next;
            idx_prev = idx_prev->next;
        }
    }   
    bubbleSortRecursion(idx);
}

template<class T> void LinkedList<T>::reverse() {
    ListNode<T> *prev = NULL;
    ListNode<T> *cur = head;
    while (cur != NULL) {
        ListNode<T> *tmp = cur->next;
        cur->next = prev;
        prev = cur;
        cur = tmp;
    }
    head = prev;
}

template<class T> void LinkedList<T>::reverse(ListNode<T> *p) {
   if (p->next == NULL) {
       head = p;
       return ;
   } 
   reverse(p->next);
   p->next->next = p;
   p->next = NULL;
}

template<class T> void LinkedList<T>::reverse(ListNode<T> *left, ListNode<T> *right) {
    if (left == right) {
        return;
    }
    reverse(left->next, right);
    left->next->next = left;
    left->next = NULL; 
}

template<class T> void LinkedList<T>::reverse(int m, int n) {
    ListNode<T> *m_prev = NULL;
    ListNode<T> *m_cur = NULL;
    ListNode<T> *n_cur = NULL;
    ListNode<T> *n_next = NULL;
    push(0);
    int count = 1;
    m_prev = head;
    m_cur = head->next;
    while (count != m) {
        m_prev = m_prev->next;
        m_cur = m_cur->next;
        count++; 
    }
    count = 1;
    n_cur = head->next;
    n_next = n_cur->next;
    while (count != n) {
        n_cur = n_cur->next;
        n_next = n_next->next;
        count++;
    }

    reverse(m_cur, n_cur);
    m_prev->next = n_cur;
    m_cur->next = n_next;

    pop();
}


template<class T> LinkedList<T>::LinkedList(const LinkedList<T> &l) {
    if (l.head == NULL) {
        head == NULL;
        return;
    }
    ListNode<T> *lnode = l.head;
    head = new ListNode<T>(lnode->data);
    ListNode<T> *node = head;
    lnode = lnode->next;
    while (lnode != NULL) {
        node->next = new ListNode<T>(lnode->data);
        node = node->next;
        lnode = lnode->next;
    }
}       
            
template<class T> LinkedList<T>::~LinkedList() {
    std::cout << "destroying LinkedList ..." << std::endl;
    while (head != NULL) {
        ListNode<T> *node = head;
        head = head->next;
        delete node;
    }    
    std::cout << "LinkedList destroied !" << std::endl;
}


template<class T> void LinkedList<T>::push(T ival) {
    ListNode<T> *new_node = new ListNode<T>(ival);
    if (head != NULL) {
        new_node->next = head;
        head = new_node;
    } else {
        new_node->next = NULL;
        head = new_node;
    }
}

template<class T> void LinkedList<T>::append(T ival) {
    ListNode<T> *last = head;
    ListNode<T> *new_node = new ListNode<T>(ival);
    if (head == NULL) {
       head = new_node;
       return;
    } 
    while(last->next != NULL) {
        last = last->next;
    }
    last->next = new_node;
    return;
}

template<class T> void LinkedList<T>::printList() {
    ListNode<T> *node = head;
    std::cout << "printing LinkedList ..." << std::endl;
    while (node != NULL) {
        std::cout << node->data << ", " ;
        node = node->next;
    }
    std::cout << std::endl;
}

<<<<<<< HEAD
template<class T>
=======
template<class T> void LinkedList<T>::mergeSort() {
    if (head == NULL || head->next == NULL) {
        return ;
    }
    head = mergeSortRecursion(head);
}

template<class T> ListNode<T> *LinkedList<T>::mergeSortRecursion(ListNode<T> *index) {
    if(index == NULL || index->next == NULL) {
        return index;
    } 
    ListNode<T> *left = NULL;
    ListNode<T> *right = NULL;
    split(index, &left, &right); 
    ListNode<T> *leftRes = mergeSortRecursion(left);
    ListNode<T> *rightRes = mergeSortRecursion(right);
    return merge(leftRes, rightRes); 
}
>>>>>>> 03263497d66c3231dff47b18d7baa6837f4faee2

template<class T> void LinkedList<T>::split(ListNode<T> *source, ListNode<T> **left, ListNode<T> **right) {
    if ( source == NULL || source->next == NULL) {
        *left = source;
        *right = NULL;
    } 
    ListNode<T> *slow = source;
    ListNode<T> *fast = source->next;
    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;
        slow = slow->next;
    }
    *left = source;
    *right = slow->next;
    slow->next = NULL;
}

template<class T> ListNode<T> *LinkedList<T>::merge(ListNode<T> *left, ListNode<T> *right) {
    if (left == NULL) {
        return right;
    }
    if (right == NULL) {
        return left;
    }
    ListNode<T> *result = new ListNode<T>(0);
    ListNode<T> *index = result;

    while (left != NULL && right != NULL) {
        if (left->data <= right->data) {
            index->next = left;
            left = left->next;
            index = index->next;
        } else {
            index->next = right;
            right = right->next;
            index = index->next;
        }
    }

    while (left != NULL) {
        index->next = left;
        left = left->next;
        index = index->next;
    }

    while (right != NULL) {
        index->next = right;
        right = right->next;
        index = index->next;
    }
    
    ListNode<T> *tmp = result;
    result = result->next;
    delete tmp;
    return result;
}

template<class T> void LinkedList<T>::quickSort() {
    push(0);
    quickSortRecursion(head->next, NULL);
    pop();    
}

template<class T> void LinkedList<T>::quickSortRecursion(ListNode<T> *left, ListNode<T> *right) {
    if (left == right || left->next == right) {
        return;
    }
    
    ListNode<T> *pivot = partition(left, right);
    quickSortRecursion(left, pivot);
    quickSortRecursion(pivot->next, right); 
}

template<class T> ListNode<T> *LinkedList<T>::partition(ListNode<T> *left, ListNode<T> *right) {
    T key = left->data;
    ListNode<T> *less_key_prev = NULL;
    ListNode<T> *less_key = left;
    ListNode<T> *index = left->next;
    ListNode<T> *index_prev = left;
    while (index != right) {
        if (index->data < key) {
            less_key_prev = less_key;
            less_key = less_key->next;
            swap(&less_key_prev->next, &index_prev->next);
            swap(&less_key->next, &index->next); 
            swap(&less_key, &index);
            if (index == index_prev) {
                index_prev = less_key;
            }
        } 
        index = index->next;
        index_prev = index_prev->next;
    }
    T tmp = left->data;
    left->data = less_key->data;
    less_key->data = tmp;

    return less_key;
}
#endif
