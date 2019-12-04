/*
1. Given the head of a Singly LinkedList, reverse the LinkedList. 
    Write a function to return the new head of the reversed LinkedList.

2. Given the head of a LinkedList and two positions ‘p’ and ‘q’, 
reverse the LinkedList from position ‘p’ to ‘q’.

Solution: 
 - Skip the first p-1 nodes, to reach the node at position p.
 - Remember the node at position p-1 to be used later to connect with the reversed sub-list.
 - Next, reverse the nodes from p to q using the same approach discussed in Reverse a LinkedList.
 - Connect the p-1 and q+1 nodes to the reversed sub-list.

Similar Problems: 
Problem 1: Reverse the first ‘k’ elements of a given LinkedList.
Solution: This problem can be easily converted to our parent problem; to reverse the first ‘k’ nodes of the list, we need to pass p=1 and q=k.

Problem 2: Given a LinkedList with ‘n’ nodes, reverse it based on its size in the following way:
Solution: 
If ‘n’ is even, reverse the list in a group of n/2 nodes.
If n is odd, keep the middle node as it is, reverse the first ‘n/2’ nodes and reverse the last ‘n/2’ nodes.
Solution: When ‘n’ is even we can perform the following steps:

Reverse first ‘n/2’ nodes: head = reverse(head, 1, n/2)
Reverse last ‘n/2’ nodes: head = reverse(head, n/2 + 1, n)
When ‘n’ is odd, our algorithm will look like:

head = reverse(head, 1, n/2)
head = reverse(head, n/2 + 2, n)
Please note the function call in the second step. We’re skipping two elements as we will be skipping the middle element.


3. Given the head of a LinkedList and a number ‘k’, reverse every ‘k’ sized sub-list starting from the head.
If, in the end, you are left with a sub-list with less than ‘k’ elements, reverse it too.
Soultion:
The problem follows the In-place Reversal of a LinkedList pattern and is quite similar to Reverse a Sub-list. 
The only difference is that we have to reverse all the sub-lists.
 We can use the same approach, starting with the first sub-list (i.e. p=1, q=k) and keep reversing all the sublists of size ‘k’.


4. Given the head of a LinkedList and a number ‘k’, reverse every alternating ‘k’ sized sub-list starting from the head.
If, in the end, you are left with a sub-list with less than ‘k’ elements, reverse it too.
Solution: 
The problem follows the In-place Reversal of a LinkedList pattern and is quite similar to Reverse every K-element Sub-list.
The only difference is that we have to skip ‘k’ alternating elements. We can follow a similar approach, 
and in each iteration after reversing ‘k’ elements, we will skip the next ‘k’ elements.


5. Given the head of a Singly LinkedList and a number ‘k’, rotate the LinkedList to the right by ‘k’ nodes.
Another way of defining the rotation is to take the sub-list of ‘k’ ending nodes of the LinkedList and connect them to the beginning. 
Other than that we have to do three more things:
    - Connect the last node of the LinkedList to the head, because the list will have a different tail after the rotation.
    - The new head of the LinkedList will be the node at the beginning of the sublist.
    - The node right before the start of sub-list will be the new tail of the rotated LinkedList.

*/


#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using std::vector;
using std::cout;
using std::endl;
using std::numeric_limits;
using std::min;
using std::string;
using std::unordered_map;


class ListNode {
 public:
  int value = 0;
  ListNode *next;

  ListNode(int value) {
    this->value = value;
    next = nullptr;
  }
};

//-----------------------//
class ReverseLinkedList {
 public:
  static ListNode *reverse(ListNode *head) {
    if (head == nullptr || head->next == nullptr) {
      return head;
    }

    ListNode *current = head;      // current node that we will be processing
    ListNode *previous = nullptr;  // previous node that we have processed
    ListNode *next = nullptr;      // will be used to temporarily store the next node

    while (current != nullptr) {
      next = current->next;      // temporarily store the next node
      current->next = previous;  // reverse the current node
      previous = current;  // before we move to the next node, point previous to the current node
      current = next;      // move on the next node
    }
    // after the loop current will be pointing to 'null' and 'previous' will be the new head
    return previous;
  }
};


int main_reverseList(int argc, char *argv[]) {
  ListNode *head = new ListNode(2);
  head->next = new ListNode(4);
  head->next->next = new ListNode(6);
  head->next->next->next = new ListNode(8);
  head->next->next->next->next = new ListNode(10);

  ListNode *result = ReverseLinkedList::reverse(head);
  cout << "Nodes of the reversed LinkedList are: ";
  while (result != nullptr) {
    cout << result->value << " ";
    result = result->next;
  }
 
  return 0;
}

//-----------------------//
/*
Given the head of a LinkedList and two positions ‘p’ and ‘q’, reverse the LinkedList from position ‘p’ to ‘q’.
*/

class ReverseSubList {
 public:
  static ListNode *reverse(ListNode *head, int p, int q) {
    if (p == q) {
      return head;
    }

    // after skipping 'p-1' nodes, current will point to 'p'th node
    ListNode *current = head, *previous = nullptr;
    for (int i = 0; current != nullptr && i < p - 1; ++i) {
      previous = current;
      current = current->next;
    }

    // we are interested in three parts of the LinkedList, part before index 'p', part between 'p'
    // and 'q', and the part after index 'q'
    ListNode *lastNodeOfFirstPart = previous;  // points to the node at index 'p-1'

    // after reversing the LinkedList 'current' will become the last node of the sub-list
    ListNode *lastNodeOfSubList = current;
    ListNode *next = nullptr;  // will be used to temporarily store the next node

    // reverse nodes between 'p' and 'q'
    for (int i = 0; current != nullptr && i < q - p + 1; i++) {
      next = current->next;
      current->next = previous;
      previous = current;
      current = next;
    }

    // connect with the first part
    if (lastNodeOfFirstPart != nullptr) {
      lastNodeOfFirstPart->next = previous;  // 'previous' is now the first node of the sub-list
    } else {  // this means p == 1 i.e., we are changing the first node (head) of the LinkedList
      head = previous;
    }

    // connect with the last part
    lastNodeOfSubList->next = current;

    return head;
  }
};

int main_reverseSubList(int argc, char *argv[]) {
  ListNode *head = new ListNode(1);
  head->next = new ListNode(2);
  head->next->next = new ListNode(3);
  head->next->next->next = new ListNode(4);
  head->next->next->next->next = new ListNode(5);

  ListNode *result = ReverseSubList::reverse(head, 2, 4);
  cout << "Nodes of the reversed (sub)LinkedList are: ";
  while (result != nullptr) {
    cout << result->value << " ";
    result = result->next;
  }
  return 0;
}

//-----------------------//

class ReverseEveryKElements {
 public:
  static ListNode *reverse(ListNode *head, int k) {
    if (k <= 1 || head == nullptr) {
      return head;
    }

    ListNode *current = head, *previous = nullptr;
    while (true) {
      ListNode *lastNodeOfPreviousPart = previous;
      // after reversing the LinkedList 'current' will become the last node of the sub-list
      ListNode *lastNodeOfSubList = current;
      ListNode *next = nullptr;  // will be used to temporarily store the next node
      // reverse 'k' nodes
      for (int i = 0; current != nullptr && i < k; i++) {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
      }

      // connect with the previous part
      if (lastNodeOfPreviousPart != nullptr) {
        lastNodeOfPreviousPart->next =
            previous;  // 'previous' is now the first node of the sub-list
      } else {         // this means we are changing the first node (head) of the LinkedList
        head = previous;
      }

      // connect with the next part
      lastNodeOfSubList->next = current;

      if (current == nullptr) {  // break, if we've reached the end of the LinkedList
        break;
      }
      // prepare for the next sub-list
      previous = lastNodeOfSubList;
    }

    return head;
  }
};

int main_reverse_every_k_element_subarray(int argc, char *argv[]) {
  ListNode *head = new ListNode(1);
  head->next = new ListNode(2);
  head->next->next = new ListNode(3);
  head->next->next->next = new ListNode(4);
  head->next->next->next->next = new ListNode(5);
  head->next->next->next->next->next = new ListNode(6);
  head->next->next->next->next->next->next = new ListNode(7);
  head->next->next->next->next->next->next->next = new ListNode(8);

  ListNode *result = ReverseEveryKElements::reverse(head, 3);
  cout << "Nodes of the reversed LinkedList are: ";
  while (result != nullptr) {
    cout << result->value << " ";
    result = result->next;
  }
  return 0;
}
//-----------------------//
// Reverse alternating K-element Sub-list (medium)
class ReverseAlternatingKElements {
 public:
  static ListNode *reverse(ListNode *head, int k) {
    if (k <= 1 || head == nullptr) {
      return head;
    }

    ListNode *current = head, *previous = nullptr;
    while (true) {
      ListNode *lastNodeOfPreviousPart = previous;
      // after reversing the LinkedList 'current' will become the last node of the sub-list
      ListNode *lastNodeOfSubList = current;
      ListNode *next = nullptr;  // will be used to temporarily store the next node
      // reverse 'k' nodes
      for (int i = 0; current != nullptr && i < k; i++) {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
      }

      // connect with the previous part
      if (lastNodeOfPreviousPart != nullptr) {
        lastNodeOfPreviousPart->next =
            previous;  // 'previous' is now the first node of the sub-list
      } else {         // this means we are changing the first node (head) of the LinkedList
        head = previous;
      }

      // connect with the next part
      lastNodeOfSubList->next = current;

      // skip 'k' nodes
      for (int i = 0; current != nullptr && i < k; ++i) {
        previous = current;
        current = current->next;
      }

      if (current == nullptr) {  // if we've reached the end of the list
        break;
      }
    }

    return head;
  }
};

int main_reverse_alt_k_element_subarray(int argc, char *argv[]) {
  ListNode *head = new ListNode(1);
  head->next = new ListNode(2);
  head->next->next = new ListNode(3);
  head->next->next->next = new ListNode(4);
  head->next->next->next->next = new ListNode(5);
  head->next->next->next->next->next = new ListNode(6);
  head->next->next->next->next->next->next = new ListNode(7);
  head->next->next->next->next->next->next->next = new ListNode(8);

  ListNode *result = ReverseAlternatingKElements::reverse(head, 2);
  cout << "Nodes of the reversed LinkedList are: ";
  while (result != nullptr) {
    cout << result->value << " ";
    result = result->next;
  }
  return 0;
}

// Rotate a LinkedList (medium)
class RotateList {
 public:
  static ListNode *rotate(ListNode *head, int rotations) {
    if (head == nullptr || head->next == nullptr || rotations <= 0) {
      return head;
    }

    // find the length and the last node of the list
    ListNode *lastNode = head;
    int listLength = 1;
    while (lastNode->next != nullptr) {
      lastNode = lastNode->next;
      listLength++;
    }

    lastNode->next = head;    // connect the last node with the head to make it a circular list
    rotations %= listLength;  // no need to do rotations more than the length of the list
    int skipLength = listLength - rotations;
    ListNode *lastNodeOfRotatedList = head;
    for (int i = 0; i < skipLength - 1; i++) {
      lastNodeOfRotatedList = lastNodeOfRotatedList->next;
    }

    // 'lastNodeOfRotatedList.next' is pointing to the sub-list of 'k' ending nodes
    head = lastNodeOfRotatedList->next;
    lastNodeOfRotatedList->next = nullptr;
    return head;
  }
};

int main(int argc, char *argv[]) {
  ListNode *head = new ListNode(1);
  head->next = new ListNode(2);
  head->next->next = new ListNode(3);
  head->next->next->next = new ListNode(4);
  head->next->next->next->next = new ListNode(5);
  head->next->next->next->next->next = new ListNode(6);

  ListNode *result = RotateList::rotate(head, 2);
  cout << "Nodes of the reversed LinkedList are: ";
  while (result != nullptr) {
    cout << result->value << " ";
    result = result->next;
  }
  return 0;
}

