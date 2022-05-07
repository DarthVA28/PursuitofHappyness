#pragma once

class Task {
public: 
    string taskDesc;
    bool taskDone;

    Task(string s) {
        taskDesc = s;
        taskDone = false;
    }
};