#include <iostream>
#include <vector>
using namespace std;



class Node {
private:
    int val;
    Node* next;

public:
    Node(int value) : next(nullptr), val(value) {}

    void setVal(int value) {val = value;}

    void setNext(Node* nx) {next = nx;}

    int getVal() {return val;}

    Node* getNext() {return next;}
};




class SLinkedList {
private:
    Node* head;
    Node* tail;
    int size;

public:
    SLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    Node* get_head() {return head;}

    Node* get_tail() {return tail;}

    int get_size() {return size;}

    void add_front(int data) {
        Node* new_node = new Node(data);
        if (head == nullptr) {
            head = new_node;
            tail = new_node;
        }
        else {
            new_node->setNext(head);
            head = new_node;
        }
        size++;
    }

    void remove_front() {
        if (head == nullptr) return;
        Node* temp = head;
        head = head->getNext();
        delete temp;
        size--;
        if (head == nullptr) {
            tail = nullptr;
        }
    }

    void add_end(int data) {
        Node* new_node = new Node(data);
        if (head == nullptr) {
            head = new_node;
            tail = new_node;
        }
        else {
            tail->setNext(new_node);
            tail = new_node;
        }
        size++;
    }

};




class Stack {
private:
    SLinkedList list;
    int current_size;
public:
    Stack(int s) : current_size(s) {}

    int get_size() {
        return list.get_size();
    }

    int peek() {
        if (list.get_size() == 0) {
            cout << "Stack is empty" << endl;
            return -1;
        }
        return list.get_head()->getVal();
    }

    void push(int data) {
        if (list.get_size() >= current_size) {
            cout << "Stack Overflow" << endl;
            return;
        }
        list.add_front(data);
    }

    int pop() {
        if (list.get_size() == 0) {
            cout << "Stack Underflow" << endl;
            return -1;
        }
        int val = list.get_head()->getVal();
        list.remove_front();
        return val;
    }

    void copy_stack(Stack& other) {
        Stack temp(current_size);
        Node* cur = other.list.get_head();
        while (cur != nullptr) {
            temp.push(cur->getVal());
            cur = cur->getNext();
        }
        while (temp.get_size() > 0) {
            this->push(temp.pop());
        }
    }

    Stack merge_sort_stack(Stack s) {
        if (s.get_size() <= 1) {
            return s;
        }
        int mid = s.get_size() / 2;
        Stack left(current_size);
        Stack right(current_size);
        for (int i = 0; i < mid; i++) {
            left.push(s.pop());
        }
        while (s.get_size() > 0) {
            right.push(s.pop());
        }
        left = merge_sort_stack(left);
        right = merge_sort_stack(right);
        return merge(left, right);
    }

    Stack merge(Stack& left, Stack& right) {
        Stack result(current_size);
        while (left.get_size() > 0 && right.get_size() > 0) {
            if (left.peek() <= right.peek()) {
                result.push(left.pop());
            }
            else {
                result.push(right.pop());
            }
        }
        while (left.get_size() > 0) {
            result.push(left.pop());
        }
        while (right.get_size() > 0) {
            result.push(right.pop());
        }
        Stack final_stack(current_size);
        while (result.get_size() > 0) {
            final_stack.push(result.pop());
        }
        return final_stack;
    }

    void print_stack() {
        Stack temp(current_size);
        temp.copy_stack(*this);
        while (temp.get_size() > 0) {
            cout << temp.pop() << " ";
        }
        cout << endl;
    }
};



class Queue {
private:
    SLinkedList list;

public:
    Queue() {}

    int get_size() {
        return list.get_size();
    }

    void enqueue(int data) {
        list.add_end(data);
    }

    int dequeue() {
        if (list.get_size() == 0) {
            cout << "Queue Underflow" << endl;
            return -1;
        }
        int val = list.get_head()->getVal();
        list.remove_front();
        return val;
    }

};




class car {
private:
    int car_number;

public:
    car(int number) : car_number(number) {}

    int get_car_number() {return car_number;}
};



class parking {
    vector<Stack> parking_lots;
    Queue waiting_queue;
    int number_of_lots;   //n
    int lot_capacity;   //m

public:
    parking(int num_lots, int lot_cap) : number_of_lots(num_lots), lot_capacity(lot_cap) {
        for (int i = 0; i < number_of_lots; i++) {
            Stack lot(lot_capacity);
            parking_lots.push_back(lot);
        }
    }

    void car_arrival(car c) {
        waiting_queue.enqueue(c.get_car_number());
    }

    void park_car(int lot_index = -1) {
        if (lot_index >= 0 && lot_index < number_of_lots) {
            if (parking_lots[lot_index].get_size() == lot_capacity) {
                cout << "The parking lot " << lot_index << " is full" << endl;
            }
            int car_ID = waiting_queue.dequeue();
            if (car_ID == -1) {
                return;
            }
            parking_lots[lot_index].push(car_ID);
        }
        else {
            for (int i = 0; i < number_of_lots; i++) {
                if (parking_lots[i].get_size() < lot_capacity) {
                    int car_ID = waiting_queue.dequeue();
                    if (car_ID == -1) {
                        return;
                    }
                    parking_lots[i].push(car_ID);
                    return;
                }
            }
            cout << "All parking lots are full." << endl;
        }
    }

    int* find(int car_number) {
        for (int i = 0; i < number_of_lots; ++i) {
            Stack temp(lot_capacity);
            temp.copy_stack(parking_lots[i]);
            int cnt = 0;
            while (temp.get_size() > 0) {
                cnt++;
                if (temp.pop() == car_number) {
                    static int find_lot[2] = {i, cnt};
                    return find_lot;
                }
            }
        }
        cout << "Car not found in any parking lot." << endl;
        static int find_lot[2] = {-1, -1};
        return find_lot;
    }

    bool remove_car_at_top(int car_number) {
        for (int i = 0; i < number_of_lots; ++i) {
            if (parking_lots[i].get_size() > 0 && parking_lots[i].peek() == car_number) {
                parking_lots[i].pop();
                return true;
            }
        }
        if (find(car_number)[0] >= 0) {
            cout << "The car is not of the above the parking lot area, and exiting from there is not possible." << endl;
            return false;
        }
        return false;
    }

    void sorting_parking_i(int lot_index) {
        if (lot_index < 0 || lot_index >= number_of_lots) {
            cout << "Invalid parking lot index." << endl;
            return;
        }
        Stack sorted_stack = parking_lots[lot_index].merge_sort_stack(parking_lots[lot_index]);
        parking_lots[lot_index] = sorted_stack;
    }

    void relocate(int from_lot, int to_lot) {
        if (from_lot < 0 || from_lot >= number_of_lots || to_lot < 0 || to_lot >= number_of_lots) {
            cout << "Invalid parking lot index." << endl;
            return;
        }
        while (parking_lots[from_lot].get_size() > 0) {
            if (parking_lots[to_lot].get_size() >= lot_capacity) {
                to_lot = (to_lot + 1) % number_of_lots;
            }
            int car_ID = parking_lots[from_lot].pop();
            parking_lots[to_lot].push(car_ID);
        }
    }

    void print_parking() {
        for (int i = 0; i < number_of_lots; i++) {
            cout << "Parking Lot " << i << ": ";
            parking_lots[i].print_stack();
        }
    }
};


int main() {
    Stack s(5);
    s.push(4);
    s.push(1);
    s.push(2);
    s.push(3);
    s.print_stack();
    Stack temp(5);
    temp.copy_stack(s);
    temp.pop();
    temp.print_stack();
    s.print_stack();
    s = s.merge_sort_stack(s);
    s.print_stack();
    return 0;
}