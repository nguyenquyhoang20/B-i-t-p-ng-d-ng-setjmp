#include <stdio.h>
#include <setjmp.h>
#include <string.h>

jmp_buf buf;
int exception_code;
char exception_message[256];  // Biến lưu thông điệp lỗi

#define TRY if ((exception_code = setjmp(buf)) == 0)
#define CATCH(x) else if (exception_code == (x)) 
#define THROW(x, msg) do { \
    strncpy(exception_message, msg, sizeof(exception_message) - 1); \
    longjmp(buf, (x)); \
} while (0)


// Hàm divide với thông điệp lỗi
double divide(int a, int b) {
    if (b == 0) {
        THROW(1, "Loi: Phep chia cho 0!");  // Ném mã lỗi 1 với thông điệp tương ứng
    }
    return (double)a / b;
}

int main() {
    int a = 10;
    int b = 0;
    double result = 0.0;

    TRY {
        result = divide(a, b);  // Gây ra lỗi chia cho 0
        printf("Result: %f\n", result);
    } 
    CATCH(1) {
        printf("Error: %s\n", exception_message);  // In thông điệp lỗi
    }

    // Thêm các xử lý khác của chương trình
    return 0;
}
