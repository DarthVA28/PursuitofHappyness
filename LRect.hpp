#pragma once

class LRect {
public: 
    int x1, x2;
    int y1, y2;

    LRect(int x_1,int y_1,int x_2,int y_2) {
        x1 = x_1;
        x2 = x_2;
        y1 = y_1;
        y2 = y_2;
    }

    bool inside(int x,int y) {
        if (x>=x1 && x<=x2 && y1<=y && y2>=y) {
            return true;
        } else {
            return false;
        }
    } 
};