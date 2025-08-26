/*
 * 순수 C 언어로 작성된 좌표 파일 읽기 예제
 * MFC와 독립적으로 사용할 수 있는 C 함수들
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// C 언어 스타일 좌표 구조체
typedef struct {
    int x;
    int y;
    int width;
    int height;
} Coordinates;

// 함수 프로토타입 선언
int load_coordinates_from_file(const char* filename, Coordinates coords[], int max_count);
int parse_coordinate_line(const char* line, Coordinates* coord);
void print_coordinates(const Coordinates coords[], int count);
int is_comment_or_empty_line(const char* line);
void trim_newline(char* line);

/*
 * 메인 함수 - 사용 예제
 */
int main()
{
    const char* filename = "coordinates.txt";
    Coordinates coords[3];  // 최대 3개의 좌표 저장
    int count;
    
    printf("=== 순수 C 언어 좌표 파일 읽기 예제 ===\n\n");
    
    // 파일에서 좌표 로드
    count = load_coordinates_from_file(filename, coords, 3);
    
    if (count > 0)
    {
        printf("성공적으로 %d개의 좌표를 읽었습니다:\n", count);
        print_coordinates(coords, count);
    }
    else
    {
        printf("좌표 파일을 읽는데 실패했습니다.\n");
        return 1;
    }
    
    return 0;
}

/*
 * 파일에서 좌표를 읽어오는 함수
 * filename: 읽을 파일명
 * coords: 좌표를 저장할 배열
 * max_count: 최대 읽을 좌표 개수
 * 반환값: 성공적으로 읽은 좌표의 개수, 실패시 -1
 */
int load_coordinates_from_file(const char* filename, Coordinates coords[], int max_count)
{
    FILE* file;
    char line[256];
    int count = 0;
    
    // 파일 열기
    file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("파일을 열 수 없습니다: %s\n", filename);
        return -1;
    }
    
    printf("파일 '%s'을(를) 읽는 중...\n", filename);
    
    // 파일에서 한 줄씩 읽기
    while (fgets(line, sizeof(line), file) != NULL && count < max_count)
    {
        // 개행 문자 제거
        trim_newline(line);
        
        // 주석이나 빈 줄 건너뛰기
        if (is_comment_or_empty_line(line))
        {
            continue;
        }
        
        // 좌표 파싱
        if (parse_coordinate_line(line, &coords[count]) == 1)
        {
            printf("라인 파싱 성공: %s\n", line);
            count++;
        }
        else
        {
            printf("라인 파싱 실패: %s\n", line);
        }
    }
    
    fclose(file);
    return count;
}

/*
 * 한 줄에서 좌표를 파싱하는 함수
 * line: 파싱할 라인
 * coord: 파싱된 좌표를 저장할 구조체 포인터
 * 반환값: 성공시 1, 실패시 0
 */
int parse_coordinate_line(const char* line, Coordinates* coord)
{
    // 방법 1: sscanf 사용
    if (sscanf(line, "%d %d %d %d", &coord->x, &coord->y, &coord->width, &coord->height) == 4)
    {
        return 1;
    }
    
    // 방법 2: 수동 파싱 (sscanf가 실패한 경우)
    char* line_copy = malloc(strlen(line) + 1);
    if (line_copy == NULL)
        return 0;
        
    strcpy(line_copy, line);
    
    char* token;
    char* saveptr;
    int values[4];
    int i = 0;
    
    token = strtok_r(line_copy, " \t", &saveptr);
    while (token != NULL && i < 4)
    {
        values[i] = atoi(token);
        i++;
        token = strtok_r(NULL, " \t", &saveptr);
    }
    
    free(line_copy);
    
    if (i == 4)
    {
        coord->x = values[0];
        coord->y = values[1];
        coord->width = values[2];
        coord->height = values[3];
        return 1;
    }
    
    return 0;
}

/*
 * 좌표 배열을 화면에 출력하는 함수
 */
void print_coordinates(const Coordinates coords[], int count)
{
    int i;
    
    printf("\n좌표 정보:\n");
    printf("Index | X   | Y   | Width | Height\n");
    printf("------|-----|-----|-------|-------\n");
    
    for (i = 0; i < count; i++)
    {
        printf("  %d   | %3d | %3d |  %3d  |  %3d\n", 
               i, coords[i].x, coords[i].y, coords[i].width, coords[i].height);
    }
    printf("\n");
}

/*
 * 주석이나 빈 줄인지 확인하는 함수
 */
int is_comment_or_empty_line(const char* line)
{
    if (line[0] == '#' || line[0] == '\0' || strlen(line) == 0)
        return 1;
        
    // 공백만 있는 줄 확인
    int i;
    for (i = 0; line[i] != '\0'; i++)
    {
        if (line[i] != ' ' && line[i] != '\t')
            return 0;
    }
    
    return 1;  // 공백만 있는 줄
}

/*
 * 문자열 끝의 개행 문자를 제거하는 함수
 */
void trim_newline(char* line)
{
    int len = strlen(line);
    
    if (len > 0 && (line[len-1] == '\n' || line[len-1] == '\r'))
    {
        line[len-1] = '\0';
        
        // Windows 스타일 개행 문자 (\r\n) 처리
        if (len > 1 && line[len-2] == '\r')
        {
            line[len-2] = '\0';
        }
    }
}

/*
 * 대안적인 더 기본적인 파싱 함수 (strtok 없이)
 */
int parse_coordinate_line_manual(const char* line, Coordinates* coord)
{
    const char* ptr = line;
    int values[4];
    int value_count = 0;
    int current_value = 0;
    int has_digit = 0;
    
    while (*ptr != '\0' && value_count < 4)
    {
        if (*ptr >= '0' && *ptr <= '9')
        {
            current_value = current_value * 10 + (*ptr - '0');
            has_digit = 1;
        }
        else if ((*ptr == ' ' || *ptr == '\t') && has_digit)
        {
            values[value_count] = current_value;
            value_count++;
            current_value = 0;
            has_digit = 0;
        }
        ptr++;
    }
    
    // 마지막 값 처리
    if (has_digit && value_count < 4)
    {
        values[value_count] = current_value;
        value_count++;
    }
    
    if (value_count == 4)
    {
        coord->x = values[0];
        coord->y = values[1];
        coord->width = values[2];
        coord->height = values[3];
        return 1;
    }
    
    return 0;
}