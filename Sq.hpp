#pragma once

class Sq {
public: 
    int xc;
    int yc;

    Rect(int x, int y) {
        xc = x;
        yc = y;
    }

    bool inside(int x,int y) {
        if (x<xc+64 && x>xc-64 && y<yc+64 && y>yc-64) {
            return true;
        } else {
            return false;
        }
    }
};