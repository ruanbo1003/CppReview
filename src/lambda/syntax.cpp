//
// Created by 阮波 on 2023/1/11.
//

#include <iostream>

class Game {
public:
    Game() {
        std::cout << "Game()" << std::endl;
    }
    Game(const Game& rhs) {
        std::cout << "Game(const Game&)" << std::endl;
    }
    Game& operator = (const Game& other) {
        std::cout << "Game& operator = (const Game& other)" << std::endl;
        return *this;
    }
    ~Game() {
        std::cout << "~Game()" << std::endl;
    }

public:
    int point() {
        return 10;
    }

    int const_point() const {
        return 10;
    }
};

void lambda_syntax() {
    std::cout << "no parameter and return integer" << std::endl;
    {
        auto f1 = []() -> int { return 100; };
        auto ret = f1();
        std::cout << "ret:" << ret << std::endl;  // 100
    }

    std::cout << "\nmany statements in lambda function" << std::endl;
    {
        int i1 = 10;
        auto func = []() -> int {
            std::cout << "in lambda function" << std::endl;

            // error, cannot access i1 here, i1 is out-of lambda function, and not been captured.
//            std::cout << i1 << std::endl;

            return 101;
        };
        auto ret = func();
        std::cout << "ret:" << ret << std::endl;  // 101
    }

    std::cout << "\nlambda function parameters" << std::endl;
    {
        auto func = [](int a, int b) -> int {
            std::cout << "a:" << a << ", b:" << b << std::endl;  // 1, 10
            return a + b;
        };
        int ret = func(1, 10);
        std::cout << "ret:" << ret << std::endl;  // 11
    }

    std::cout << "\ncapture variable" << std::endl;
    {
        int data = 10;
        auto func = [data](int x) -> int {
            std::cout << "data:" << data << std::endl;  // 10

            // lambda function is const by default. we cannot change the captured value.
            // data = 11;  // error: cannot assign to a variable captured by copy in a non-mutable lambda.

            return data * x;
        };
        int ret = func(2);
        std::cout << "ret:" << ret << std::endl;  // 20
    }

    std::cout << "\ncapture a class instance to see if the capture make a copy of the instance" << std::endl;
    {
        Game game;
        std::cout << "step 1: before declare the lambda function" << std::endl;

        // the captured value game, will call the copy-constructor(Game(const Game& rhs))
        // to make a copy of the captured value.
        auto func = [game](int x) -> int {
            // by default, lambda function is const, we can only call the class's const member functions.
            int game_point = game.const_point();
            std::cout << "game_point:" << game_point << std::endl;  // 10
            return game_point;
        };

        std::cout << "step 2: after declare the lambda function" << std::endl;

        int ret = func(22);
        std::cout << "ret:" << ret << std::endl;  // 10
    }

    std::cout << "\ncapture a class instance reference to see if the lambda function will make copy the of value" << std::endl;
    {
        Game game;

        // when capture reference of variable, the lambda will make a copy of the variable.
        auto func = [&game](int x) -> int {
            int game_point = game.const_point();
            std::cout << x << ", " << game_point << std::endl; // 2, 10
            return game_point;
        };
        int ret = func(2);
        std::cout << "ret:" << ret << std::endl; // 10
    }

    std::cout << "\nmutable lambda function to change the out-side variable value" << std::endl;
    {
        int data = 100;

        // when make the lambda function mutable with adding mutable keyword after the parameter.
        // we can change the value out-side of the lambda function.
        auto func = [data](int x) mutable -> int {
            std::cout << x << ", " << data << std::endl;  // 2, 100
            data = 10;
            return data;
        };

        int ret = func(2);
        std::cout << "ret:" << ret << std::endl;  // 10
    }

    std::cout << "\ndirectly call the lambda function without extra function variable" << std::endl;
    {
        int x = 10;
        int y = 2;

        // declare a lambda function and call it directly.
        [&x, &y](int a, int b) mutable -> int {
            x = x + a;
            y = y + b;
            return a + b;
        }(1, 100);

        std::cout << x << ", " << y << std::endl;  // 11, 102
    }
}


void lambda_syntax_test() {
    lambda_syntax();

}