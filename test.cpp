#include "assert/array.hpp"

//[Usage]

void test(float a[][4], float b[][4]){
    // 型情報から要素数を完全には推定できない場合
    // テンプレートの指定が必要
    assertNear<float[4]>(2, a, b);
}

int main(){
    float a[2][4] = { 1, 2, 3, 4, 5,   6, 7, 8 };
    float b[2][4] = { 1, 2, 3, 4, 5.2, 6, 7, 8 };
    //型情報から要素数を完全に推定できる場合
    //変数のみを渡せばいい。

    //これらのテストは落ちる
    assertNear(a, b);
    test(a, b);
}
