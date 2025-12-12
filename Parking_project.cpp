#include <iostream>
#include <vector>
using namespace std;



class Node {
private:
    int val;
    Node* next;

public:
    Node(int value) : next(nullptr), val(value) {} // every function O(1)

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

    void add_front(int data) {   // O(1)
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

    void remove_front() {   //O(1)
        if (head == nullptr) return;
        Node* temp = head;
        head = head->getNext();
        delete temp;
        size--;
        if (head == nullptr) {
            tail = nullptr;
        }
    }

    void add_end(int data) {   //O(1)
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

    int peek() {   // O(1)
        if (list.get_size() == 0) {
            cout << "Stack is empty" << endl;
            return -1;
        }
        return list.get_head()->getVal();
    }

    void push(int data) {   // O(1)
        if (list.get_size() >= current_size) {
            cout << "Stack Overflow" << endl;
            return;
        }
        list.add_front(data);
    }

    int pop() {   // O(1)
        if (list.get_size() == 0) {
            cout << "Stack Underflow" << endl;
            return -1;
        }
        int val = list.get_head()->getVal();
        list.remove_front();
        return val;
    }

    void copy_stack(Stack& other) {   // O(n) n is number of data in stack
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

    Stack merge_sort_stack(Stack s) {   // O(nlogn)
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

    Stack merge(Stack& left, Stack& right) {  // O(m+n) ~ O(n)
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

    void print_stack() {   // O(n^2) (copy_stack is O(n^2))
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

    int get_size() {  // O(1)
        return list.get_size();
    }

    void enqueue(int data) {   // O(1)
        list.add_end(data);
    }

    int dequeue() {   // O(1)
        if (list.get_size() == 0) {
            cout << "Queue Underflow" << endl;
            return -1;
        }
        int val = list.get_head()->getVal();
        list.remove_front();
        return val;
    }

};




class Car {
private:
    int car_number;

public:
    Car(int number) : car_number(number) {}

    int get_car_number() {return car_number;}
};



class Parking {
    vector<Stack> parking_lots;
    Queue waiting_queue;
    int number_of_lots;   //n
    int lot_capacity;   //m

public:
    Parking(int num_lots, int lot_cap) : number_of_lots(num_lots), lot_capacity(lot_cap) {   // O(n) n is number_of_lots
        for (int i = 0; i < number_of_lots; i++) {
            Stack lot(lot_capacity);
            parking_lots.push_back(lot);
        }
    }

    void car_arrival(Car c) {   // O(1)
        waiting_queue.enqueue(c.get_car_number());
    }

    bool isFull() {   // O(n)
        for (int i = 0; i < number_of_lots; ++i) {
            if (parking_lots[i].get_size() < lot_capacity) return false;
        }
        return true;
    }

    void park_car(int lot_index = -1) {   // worse case: O(n) n is number_of_lots
        if (lot_index >= 0 && lot_index < number_of_lots) {
            if (parking_lots[lot_index].get_size() == lot_capacity) {
                cout << "The parking lot " << lot_index << " is full" << endl;
                return;
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

    void park_all_car() {   //O(k*n) k->number of car in waiting_queue
        while(waiting_queue.get_size()) {
            if (!isFull()) park_car();
            else {
                cout << "All parking lots are full." << endl;
                break;
            }
        }
    }

    struct Find_Result {
        int lot;
        int level;
    };

    Find_Result find(int car_number) {   // worstcase: O(n*m^3)
        for (int i = 0; i < number_of_lots; ++i) {   //O(n) n->number_of_lots
            Stack temp(lot_capacity);
            temp.copy_stack(parking_lots[i]);   //O(m^2) m->lot_capacity
            int cnt = 0;
            while (temp.get_size() > 0) {   //O(m)
                cnt++;
                if (temp.pop() == car_number) {
                    return {i, cnt};
                }
            }
        }
        cout << "Car " << car_number << " not found in any parking lot." << endl;
        return {-1, -1};
    }

    bool remove_car_at_top(int car_number) {   //worstcase: O(n*m^3)
        for (int i = 0; i < number_of_lots; ++i) {   //O(n)
            if (parking_lots[i].get_size() > 0 && parking_lots[i].peek() == car_number) {
                parking_lots[i].pop();
                return true;
            }
        }
        if (find(car_number).lot >= 0) {   //O(n*m^3)
            cout << "The car " << car_number << " is not of the above the parking lot area, and exiting from there is not possible." << endl;
            return false;
        }
        return false;
    }

    void sorting_parking_i(int lot_index) {   //O(m*logm)
        if (lot_index < 0 || lot_index >= number_of_lots) {
            cout << "Invalid parking lot index." << endl;
            return;
        }
        Stack sorted_stack = parking_lots[lot_index].merge_sort_stack(parking_lots[lot_index]);   //O(m*logm) m->lot_capacity
        parking_lots[lot_index] = sorted_stack;
    }

    void relocate(int from_lot, int to_lot) {   //worstcase: O(m*n) 
        if (from_lot < 0 || from_lot >= number_of_lots || to_lot < 0 || to_lot >= number_of_lots) {
            cout << "Invalid parking lot index." << endl;
            return;
        }
        int flag = to_lot;
        while (parking_lots[from_lot].get_size() > 0) {
            if (parking_lots[to_lot].get_size() >= lot_capacity) {
                to_lot = (to_lot + 1) % number_of_lots;
                if (to_lot == flag) {
                    if (parking_lots[from_lot].get_size() > 0) {
                        cout << "Parking is full so the car from spot " << from_lot << " can not be moved." <<endl;
                    }
                    return;
                }
                if (to_lot == from_lot) {
                    to_lot++;
                    if (to_lot == flag) {
                        if (parking_lots[from_lot].get_size() > 0) {
                            cout << "Parking is full so the car from spot " << from_lot << " can not be moved." <<endl;
                        }
                        return;
                    }
                    continue;
                }
            }
            else {
                int car_ID = parking_lots[from_lot].pop();
                parking_lots[to_lot].push(car_ID);
            }
        }
    }

    void print_parking() {  // O(m^2 * n)
        for (int i = 0; i < number_of_lots; i++) {  // O(n)
            cout << "Parking Lot " << i << ": ";
            parking_lots[i].print_stack();  // O(m^2)
        }
    }
};


int main() {
    int n, m;
    cout << "Enter number of parking lots: ";
    cin >> n;
    cout << "Enter capacity of each lot: ";
    cin >> m;

    Parking P(n, m);

    while (true) {
        cout << "\n===== Parking System UI =====\n";
        cout << "1. Car arrival\n";
        cout << "2. Park next car\n";
        cout << "3. Park all cars\n";
        cout << "4. Remove car at top\n";
        cout << "5. Find car\n";
        cout << "6. Sort a parking lot\n";
        cout << "7. Relocate cars\n";
        cout << "8. Print parking\n";
        cout << "9. Exit\n";
        cout << "Choose: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            int car_id;
            cout << "Enter car number: ";
            cin >> car_id;
            P.car_arrival(Car(car_id));
            cout << "Car added to waiting queue.\n";
        }
        else if (choice == 2) {
            int lot;
            cout << "Enter lot index (-1 for auto): ";
            cin >> lot;
            P.park_car(lot);
        }
        else if (choice == 3) {
            P.park_all_car();
        }
        else if (choice == 4) {
            int car_id;
            cout << "Enter car number to remove: ";
            cin >> car_id;
            if (P.remove_car_at_top(car_id))
                cout << "Removed successfully.\n";
        }
        else if (choice == 5) {
            int car_id;
            cout << "Enter car number to find: ";
            cin >> car_id;
            auto result = P.find(car_id);
            if (result.lot >= 0)
                cout << "Found in lot " << result.lot << ", level " << result.level << endl;
        }
        else if (choice == 6) {
            int lot;
            cout << "Enter lot index: ";
            cin >> lot;
            P.sorting_parking_i(lot);
        }
        else if (choice == 7) {
            int fromL, toL;
            cout << "Move cars FROM lot: ";
            cin >> fromL;
            cout << "TO lot: ";
            cin >> toL;
            P.relocate(fromL, toL);
        }
        else if (choice == 8) {
            P.print_parking();
        }
        else if (choice == 9) {
            cout << "Exiting...\n";
            break;
        }
        else {
            cout << "Invalid choice!\n";
        }
    }
    return 0;
}