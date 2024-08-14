#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std; 

struct Task {
    string title;
    string description;
};

void saveTasks(const vector<Task>& tasks) {
    ofstream file("tasks.txt");
    for (const auto& task : tasks) {
        file << task.title << endl;
        file << task.description << endl;
    }
    file.close();
}

/*function to load tasks from a file*/ 
vector<Task> loadTasks() {
    vector<Task> tasks;
    ifstream file("tasks.txt");
    string title, description;

    while (getline(file, title) && getline(file, description)) {
        tasks.push_back({title, description});
    }
    file.close();
    return tasks;
}

/* Function to add a task*/
void addTask(vector<Task>& tasks) {
    Task task;
    cout << "Enter the task title: ";
    cin.ignore(); /* To ignore leftover newline*/
    getline(cin, task.title);
    cout << "Enter the task description: ";
    getline(cin, task.description);
    tasks.push_back(task);
    saveTasks(tasks);
    cout << "Task '" << task.title << "' added.\n";
}

void removeTask(vector<Task>& tasks) {
    int taskNumber;
    cout << "Enter the task number to remove: ";
    cin >> taskNumber;
    if (taskNumber > 0 && taskNumber <= tasks.size()) {
        cout << "Are you sure you want to remove '" << tasks[taskNumber - 1].title << "'? (y/n): ";
        char confirmation;
        cin >> confirmation;
        if (confirmation == 'y' || confirmation == 'Y') {
            tasks.erase(tasks.begin() + taskNumber - 1);
            saveTasks(tasks);
            cout << "Task removed.\n";
        } else {
            cout << "Task not removed.\n";
        }
    } else {
        cout << "Invalid task number!\n";
    }
}

/* Function to view tasks*/
void viewTasks(vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "Your Todo List is empty.\n";
    } else {
        sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
            return a.title < b.title;
        });
        cout << "Your Todo List:\n";
        for (size_t i = 0; i < tasks.size(); ++i) {
            cout << i + 1 << ". " << tasks[i].title << " - " << tasks[i].description << endl;
        }
    }
}

int main() {
    vector<Task> tasks = loadTasks();
    int choice;

    do {
        cout << "\nWelcome to the Todo List Application!\n";
        cout << "1. Add Task\n2. Remove Task\n3. View Tasks\n4. Exit\n";
        cout << "Please choose an option: ";
        cin >> choice;

        if (choice == 1) {
            addTask(tasks);
        } else if (choice == 2) {
            removeTask(tasks);
        } else if (choice == 3) {
            viewTasks(tasks);
        } else if (choice == 4) {
            cout << "Exiting the application. Goodbye!\n";
        } else {
            cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 4);

    return 0;
}