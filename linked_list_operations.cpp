#include <iostream>
#include <string>
using namespace std;
struct TaskNode {
    int taskID;
    string description;
    int priority;
    TaskNode* next;
};
class TaskManager {
private:
    TaskNode* head;  // Pointer to the first node
public:
    TaskManager() {
        head = nullptr;  // Initialize the head as null
    }
    TaskNode* createTask(int id, string desc, int priority) {
        TaskNode* newTask = new TaskNode;
        newTask->taskID = id;
        newTask->description = desc;
        newTask->priority = priority;
        newTask->next = nullptr;
        return newTask;
    }
    void addTask(int id, string desc, int priority) {
        TaskNode* newTask = createTask(id, desc, priority);
        if (!head || head->priority < priority) { // Insert at head if higher priority
            newTask->next = head;
            head = newTask;
        } else {
            TaskNode* temp = head;
            while (temp->next && temp->next->priority >= priority) {
                temp = temp->next;
            }
            newTask->next = temp->next;
            temp->next = newTask;
        }
        cout << "Task added successfully.\n";
    }
    void removeHighestPriorityTask() {
        if (!head) {
            cout << "No tasks to remove.\n";
            return;
        }
        TaskNode* temp = head;
        head = head->next;
        cout << "Removed task with ID: " << temp->taskID << " (Highest priority).\n";
        delete temp;
    }
    void removeTaskByID(int id) {
        if (!head) {
            cout << "No tasks to remove.\n";
            return;
        }
        if (head->taskID == id) {  // If head is the task to be removed
            TaskNode* temp = head;
            head = head->next;
            delete temp;
            cout << "Task with ID " << id << " removed.\n";
            return;
        }
        TaskNode* temp = head;
        while (temp->next && temp->next->taskID != id) {
            temp = temp->next;
        }
        if (temp->next) {
            TaskNode* toDelete = temp->next;
            temp->next = toDelete->next;
            delete toDelete;
            cout << "Task with ID " << id << " removed.\n";
        } else {
            cout << "Task with ID " << id << " not found.\n";
        }
 }
    void displayTasks() {
        if (!head) {
            cout << "No tasks to display.\n";
            return;
        }
        TaskNode* temp = head;
        while (temp) {
            cout << "Task ID: " << temp->taskID << ", Description: " << temp->description
                 << ", Priority: " << temp->priority << "\n";
            temp = temp->next;
        }
    }
    ~TaskManager() {
        while (head) {
            TaskNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
};
int main() {
    TaskManager manager;
    int choice, id, priority;
    string description;
    do {
        cout << "\nTask Manager Menu:\n";
        cout << "1. Add a new task\n";
        cout << "2. View all tasks\n";
        cout << "3. Remove the highest priority task\n";
        cout << "4. Remove a task by ID\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter task ID: ";
                cin >> id;
                cout << "Enter task description: ";
                cin.ignore();  // To ignore the newline character left by previous input
                getline(cin, description);
                cout << "Enter task priority: ";
                cin >> priority;
                manager.addTask(id, description, priority);
                break;
            case 2:
                cout << "All Tasks:\n";
                manager.displayTasks();
                break;
            case 3:
                manager.removeHighestPriorityTask();
                break;
            case 4:
                cout << "Enter task ID to remove: ";
                cin >> id;
                manager.removeTaskByID(id);
                break;
            case 5:
                cout << "Exiting Task Manager.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);
    return 0;
}
