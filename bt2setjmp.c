#include <stdio.h>
#include <setjmp.h>
#include <string.h>

// Định nghĩa các mã lỗi
enum ErrorCodes { NO_ERROR, FILE_ERROR, NETWORK_ERROR, CALCULATION_ERROR };

// Biến toàn cục để lưu mã lỗi và thông điệp lỗi
jmp_buf buf;
int exception_code;
char exception_message[256];  // Biến lưu thông điệp lỗi

// Định nghĩa các macro TRY, CATCH, và THROW
#define TRY if ((exception_code = setjmp(buf)) == 0)
#define CATCH(x) else if (exception_code == (x)) 
#define THROW(x, msg) do { \
    strncpy(exception_message, msg, sizeof(exception_message) - 1); \
    exception_message[sizeof(exception_message) - 1] = '\0'; /* Đảm bảo chuỗi kết thúc đúng */ \
    longjmp(buf, (x)); \
} while (0)

// Hàm mô phỏng đọc file
void readFile() {
    printf("Doc file...\n");
    THROW(FILE_ERROR, "Loi doc file: File khong ton tai.");
}

// Hàm mô phỏng hoạt động mạng
void networkOperation() {
    printf("Xu ly mang...\n");
    THROW(NETWORK_ERROR, "Loi xu ly mang: Khong the ket noi den may chu.");
}

// Hàm mô phỏng tính toán dữ liệu
void calculateData() {
    printf("Tinh toan du lieu...\n");
    THROW(CALCULATION_ERROR, "Loi tinh toan: Du lieu khong hop le.");
}

int main() {
    // Khối TRY đầu tiên cho đọc file
    TRY {
        readFile();         // Giả lập lỗi đọc file
    } 
    CATCH(FILE_ERROR) {
        printf("Error: %s\n", exception_message);
    }

    // Khối TRY thứ hai cho xử lý mạng
    TRY {
        networkOperation(); // Giả lập lỗi mạng
    } 
    CATCH(NETWORK_ERROR) {
        printf("Error: %s\n", exception_message);
    }

    // Khối TRY thứ ba cho tính toán dữ liệu
    TRY {
        calculateData();    // Giả lập lỗi tính toán
    } 
    CATCH(CALCULATION_ERROR) {
        printf("Error: %s\n", exception_message);
    }

    printf("Ket thuc chuong trinh.\n");

    return 0;
}
