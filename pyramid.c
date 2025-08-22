#include <stdio.h>

int main() {
    int rows, i, j, space;
    
    printf("피라미드의 높이를 입력하세요: ");
    scanf("%d", &rows);
    
    // 피라미드 출력
    for (i = 1; i <= rows; i++) {
        // 공백 출력 (중앙 정렬을 위해)
        for (space = 1; space <= rows - i; space++) {
            printf(" ");
        }
        
        // 별(*) 출력
        for (j = 1; j <= 2 * i - 1; j++) {
            printf("*");
        }
        
        // 다음 줄로 이동
        printf("\n");
    }
    
    return 0;
}