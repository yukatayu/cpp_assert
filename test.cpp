#include <iostream>
#include <iomanip>

#include "assert/array.hpp"

using namespace assert;

void success(){
    std::cout << "\t-> \033[92mSuccess!\033[0m" << std::endl;
}
void line(){
    std::cout << "\n ----------\n" << std::endl;
}

//[Usage]

void test(float a[][4][3], float b[][4][3]){

    std::cerr << "testing a = b ( from test() )" << std::endl;

    // 型情報から要素数を完全には推定できない場合
    if(assertNear(2, a, b))
        success();
}

void test2(float x[], float y[]){

    std::cerr << "testing (x = y) or (x = z) ( from test2() )" << std::endl;

    // プリミティブ型のポインタでも正常に動作する
    if(assertNear(3, x, y))
        success();
}

int main(){

    float a[2][4][3] = {
        1, 2, 3, 4, 5, 6, 7, 8,
        1, 2, 3, 4, 5, 6, 7, 8,
        1, 2, 3, 4, 5, 6, 7, 8,
    };
    float b[2][4][3] = {
        1, 2, 3, 4, 5, 6,   7, 8,
        1, 2, 3, 4, 5, 6.2, 7, 8,
        1, 2, 3, 4, 5, 6,   7, 8,
    };

    float c[2][4][3] = {
        1, 2, 3, 4, 5, 6, 7, 8,
        1, 2, 3, 4, 5, 6, 7, 8,
        1, 2, 3, 4, 5, 6, 7, 8,
    };

    //表示精度の指定
    std::cerr << std::fixed << std::setprecision(5) << std::flush;

    //これらのテストは落ちる

    std::cerr << "testing a = b" << std::endl;

    //型情報から要素数を完全に推定できる場合
    //変数のみを渡せばいい。
    if(assertNear(a, b))
        success();

line();

    //配列の長さが一部分からない場合
    test(a, b);

line();

    //成功するテスト
    std::cerr << "testing a = c" << std::endl;
    if(assertNear(a, c))
        success();

line();

    float x[3] = {1, 2,   3};
    float y[3] = {1, 1.9, 3};
    float z[3] = {1, 2,   3};
    test2(x, y);

line();

    test2(x, z);

}
