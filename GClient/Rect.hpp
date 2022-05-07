#pragma once

class Rect {
public: 
    int x1, x2;
    int y1, y2;
    bool horizontal;

    Rect(int x_1,int y_1,int x_2,int y_2) {
        if (y_1 == y_2) {
            horizontal = true;
            if (x_2>x_1) {
                x1 = x_1;
                x2 = x_2;
            } else {
                x1 = x_2;
                x2 = x_1;
            }
            y1 = y_1;
            y2 = y_2;
        } else {
            horizontal = false;
            if (y_2>y_1) {
                y1 = y_1;
                y2 = y_2;
            } else {
                y1 = y_2;
                y2 = y_1;
            }
            x1 = x_1;
            x2 = x_2;
        }
    }

    bool inside(int x,int y) {
        if (horizontal) {
            if (x>=x1 && x<=x2 && y1-64<=y && y1+64>=y) {
                return true;
            } else {
                return false;
            }
        } else {
            if (x1-64<=x && x<=x1+64 && y1<=y && y<=y2) {
                return true;
            } else {
                return false;
            }
        }
    }
};