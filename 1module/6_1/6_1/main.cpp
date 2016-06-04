//
//
//6_1. Высокая пирамида.
//Каждый вышележащий слой пирамиды должен быть не больше нижележащего.
//N ≤  200 .
//
//  Created by Дмитрий  Загребаев on 24.03.16.
//  Copyright © 2016 Дмитрий  Загребаев. All rights reserved.
//

#include <iostream>

inline int readNumber() {int num = 0; std::cin >> num; return num;}
int calc(int N);

int main(int argc, const char * argv[]) {
    // insert code here...
    
    fflush(stdin);
    fflush(stdout);
    
    int N = 0;
    
    N = readNumber();
    
    std:: cout << N;
    
    return 0;
}

int calc(int N) {
    
    int answer = 0;
    
    return answer;
}