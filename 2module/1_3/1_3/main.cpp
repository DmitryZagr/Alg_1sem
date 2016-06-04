//
//  main.cpp
//  1_3
//Аналогично 1.2, но ломаная должна быть замкнутая.
//Предполагается, что никакие три точки не лежат на одной прямой.
//Указание: стройте ломаную от точки, имеющей наименьшую координату x.
//Если таких точек несколько, то используйте точку с наименьшей координатой y.
//Точки на ломаной расположите в порядке убывания углов лучей от начальной точки до всех остальных точек.
//
//  Created by Дмитрий  Загребаев on 08.04.16.
//  Copyright © 2016 Дмитрий  Загребаев. All rights reserved.
//

#include <iostream>
#include <cmath>
#include "string.h"
#include <vector>

using namespace std;

struct Point {
    int X;
    int Y;
    float angle;
    Point() : X(0), Y(0) , angle(0) {}
};

typedef struct Point Point;


template <class T> void insertionSort(T *points, int32_t size);

void readStream(Point *points, int32_t sizeArr);

bool operator < (const Point& left, const Point& right) {
    return left.angle < right.angle;
}

int main(int argc, const char * argv[]) {

    int32_t sizeOfArray = 0;
    
    cin >> sizeOfArray;
    
    Point *points = nullptr;
    
    points = new Point[sizeOfArray];
    
    readStream(points, sizeOfArray);
    
    insertionSort(points, sizeOfArray);
    
    for (int32_t i = sizeOfArray - 1; i >= 0; i--) {
        std::cout << points[i].X << " " << points[i].Y << std::endl;
    }
    
    delete [] points;
    
    return 0;
}


void readStream(Point *points, int32_t sizeArr) {
    
    Point minPoint;
    int32_t minIndex = 0;
    
    for(int32_t i = 0; i < sizeArr; i++) {
        std::cin >> points[i].X;
        std::cin >> points[i].Y;
        if( i == 0) {
            minPoint = points[0];
            minIndex = 0;
        }
        
        if(minPoint.X > points[i].X) {
            minPoint.X = points[i].X;
            minPoint.Y = points[i].Y;
            minIndex   = i;
        } else if (minPoint.X == points[i].X && minPoint.Y > points[i].Y) {
            minPoint.Y = points[i].Y;
            minIndex   = i;
        }
    }
    
    int32_t xCoordVector = 0;
    int32_t yCoordVector = 0;
    float absVector = 0;
    
    for (int i = 0; i < sizeArr; i++) {
        xCoordVector = points[i].X - points[minIndex].X;
        yCoordVector = points[i].Y - points[minIndex].Y;
        absVector    = sqrt(xCoordVector * xCoordVector + yCoordVector * yCoordVector);
        if( i != minIndex)
            points[i].angle = yCoordVector / absVector;
        else
            points[i].angle = 1.1;
    }
}

template<class T> void insertionSort(T *points, int32_t size) {
    int32_t j;
    T point;
    for (int32_t i = 1; i < size; i++) {
        j = i;
        while (j > 0 && points[j] < points[j - 1]) {
            std::swap(points[j], points[j - 1]);
            j--;
        }
    }
}


