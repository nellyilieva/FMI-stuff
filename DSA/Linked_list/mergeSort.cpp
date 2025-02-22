#include <iostream>
#include <vector>
#include <algorithm>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
 
class MergeSort {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if (!list1 && !list2) {
            return nullptr;
        }

        if (!list1) {
            return list2;
        }

        if (!list2) {
            return list1;
        }

        ListNode* head = nullptr;
        ListNode* curr = nullptr;
        //first node
        if (list1->val < list2->val) {
            head = curr = new ListNode(list1->val);
            list1 = list1->next;
        }
        else {
            head = curr = new ListNode(list2->val);
            list2 = list2->next;
        }

        //we create new nodes
        while (list1 && list2) {
            if (list1->val < list2->val) {
                curr->next = new ListNode(list1->val);
                list1 = list1->next;
            }
            else {
                curr->next = new ListNode(list2->val);
                list2 = list2->next;
            }
            curr = curr->next;
        }

        //here we just make the last pointer point to the rest of the list
        if (list1) {
            curr->next = list1;
        }
        else if (list2) {
            curr->next = list2;
        }

        return head;
    }

    ListNode* getMiddle(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head->next;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }

    ListNode* sortList(ListNode* head) {
        if (!head || !head->next) {
            return head;
        }

        ListNode* mid = getMiddle(head);
        ListNode* second_half = mid->next;
        mid->next = nullptr;

        ListNode* left = sortList(head);
        ListNode* right = sortList(second_half);

        return mergeTwoLists(left, right);
    }
};

ListNode* createLinkedList(const std::vector<int>& values) {
    if (values.empty()) return nullptr;

    ListNode* head = new ListNode(values[0]);
    ListNode* current = head;

    for (size_t i = 1; i < values.size(); i++) {
        current->next = new ListNode(values[i]);
        current = current->next;
    }
    return head;
}

void printLinkedList(ListNode* head) {
    while (head) {
        std::cout << head->val;
        if (head->next) std::cout << " -> ";
        head = head->next;
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> values = { 4, 2, 1, 3 };

    ListNode* head = createLinkedList(values);

    printLinkedList(head);

    MergeSort sort;
    ListNode* sortedHead = sort.sortList(head);

    printLinkedList(sortedHead);
}
