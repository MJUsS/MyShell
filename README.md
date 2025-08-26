# MFC TextControl 좌표 변경 예제 (순수 C언어)

이 프로젝트는 **순수 C언어**와 MFC를 사용하여 파일에서 좌표를 읽어와서 텍스트 컨트롤의 위치를 동적으로 변경하는 방법을 보여주는 예제입니다.

## 파일 구성

### MFC 통합 버전
- `coordinates.txt`: 좌표 데이터가 저장된 텍스트 파일
- `TextControlDlg.h`: MFC 다이얼로그 헤더 파일 (C언어 스타일로 수정됨)
- `TextControlDlg.cpp`: C++ 스타일의 원본 구현 파일
- `TextControlDlg_C_Style.cpp`: **순수 C언어 스타일**로 작성된 MFC 구현 파일
- `resource.h`: 리소스 ID 정의
- `TextControlApp.rc`: MFC 리소스 파일

### 순수 C언어 독립 버전
- `pure_c_example.c`: MFC 없이 **순수 C언어만**으로 작성된 파일 읽기 예제

## 주요 기능

1. **파일에서 좌표 읽기**: `coordinates.txt` 파일에서 x, y, width, height 값을 읽어옵니다.
2. **동적 위치 변경**: 읽어온 좌표를 사용하여 TextControl의 위치와 크기를 실시간으로 변경합니다.
3. **사용자 인터페이스**: 파일 선택 다이얼로그를 통해 좌표 파일을 선택할 수 있습니다.

## 좌표 파일 형식

```
# 좌표 파일 형식: x y width height
# TextControl의 위치와 크기 정보
100 50 200 25
150 100 180 30
200 150 160 20
```

- 각 줄은 하나의 TextControl에 대한 좌표를 나타냅니다.
- 순서대로 x좌표, y좌표, 너비, 높이를 의미합니다.
- `#`으로 시작하는 줄은 주석으로 처리됩니다.

## 핵심 함수

### C언어 스타일 MFC 버전

#### `LoadCoordinatesFromFile_CStyle()`
```c
BOOL LoadCoordinatesFromFile_CStyle(const CString& filename)
```
- **순수 C언어 스타일**로 작성된 파일 읽기 함수
- `fopen_s()`, `fgets()`, `sscanf_s()` 사용
- `strtok_s()`를 이용한 대안적 파싱 방법 제공

#### `UpdateTextControlPosition_CStyle()`
```c
void UpdateTextControlPosition_CStyle(int controlIndex, const TextControlCoords* coords)
```
- C언어 스타일 포인터 사용
- 구조체 포인터를 통한 데이터 접근
- SetWindowPos()를 사용하여 컨트롤 위치 변경

### 순수 C언어 독립 버전

#### `load_coordinates_from_file()`
```c
int load_coordinates_from_file(const char* filename, Coordinates coords[], int max_count)
```
- MFC 없이 순수 C언어로만 작성
- `fopen()`, `fgets()`, `sscanf()` 사용
- 파싱 실패 시 `strtok_r()` 대안 제공

#### `parse_coordinate_line_manual()`
```c
int parse_coordinate_line_manual(const char* line, Coordinates* coord)
```
- 라이브러리 함수 없이 수동 파싱
- 문자열 포인터 직접 조작
- 완전히 독립적인 C언어 구현

## 컴파일 및 실행

1. Visual Studio에서 MFC 프로젝트를 생성합니다.
2. 제공된 파일들을 프로젝트에 추가합니다.
3. 프로젝트를 빌드하고 실행합니다.
4. "좌표 파일 로드" 버튼을 클릭하여 coordinates.txt 파일을 선택합니다.
5. 텍스트 컨트롤들의 위치가 파일에 정의된 좌표로 변경되는 것을 확인합니다.

## 기술적 특징

### MFC 버전
- **MFC 다이얼로그 기반**: Windows MFC 프레임워크 사용
- **순수 C언어 파일 I/O**: `fopen_s()`, `fgets()`, `sscanf_s()` 사용
- **C언어 스타일 문자열 처리**: `strtok_s()`, 포인터 직접 조작
- **동적 UI 변경**: 런타임에 컨트롤 위치 변경
- **구조체 포인터**: C언어 스타일 데이터 구조 사용

### 순수 C언어 버전
- **완전한 C언어**: MFC나 C++ 기능 없이 순수 C언어만 사용
- **표준 C 라이브러리**: `stdio.h`, `stdlib.h`, `string.h`만 사용
- **수동 메모리 관리**: `malloc()`, `free()` 사용
- **다양한 파싱 방법**: `sscanf()`, `strtok_r()`, 수동 파싱 제공
- **크로스 플랫폼**: Unix/Linux에서도 컴파일 가능

## C언어 파일 I/O 특징

### 사용된 C언어 함수들
```c
FILE* fopen_s(&file, filename, "r");  // 안전한 파일 열기
fgets(line, sizeof(line), file);      // 한 줄씩 읽기
sscanf_s(line, "%d %d %d %d", ...);   // 안전한 문자열 파싱
strtok_s(line, " \t", &context);      // 안전한 토큰 분리
fclose(file);                         // 파일 닫기
```

### 메모리 안전성
- **버퍼 오버플로우 방지**: `fgets()`, `sscanf_s()` 사용
- **안전한 문자열 함수**: `strtok_s()` 사용
- **NULL 포인터 검사**: 모든 포인터 사용 전 검증