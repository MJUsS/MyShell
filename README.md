# MFC 텍스트 컨트롤 위치 변경 예제

이 프로젝트는 C언어 파일 입출력을 사용하여 좌표 파일에서 좌표를 읽어와서 MFC 다이얼로그의 텍스트 컨트롤 위치를 동적으로 변경하는 예제입니다.

## 파일 구성

1. **coordinates.txt** - 텍스트 컨트롤의 좌표 데이터 파일
2. **TextControlDlg.h** - MFC 다이얼로그 헤더 파일
3. **TextControlDlg.cpp** - MFC 다이얼로그 구현 파일
4. **resource.h** - 리소스 ID 정의
5. **TextControlDlg.rc** - 리소스 스크립트 파일

## 주요 기능

### 1. 좌표 파일 형식
```
# 텍스트 컨트롤의 좌표 (x, y, width, height)
# TextControl1
100 50 200 25
# TextControl2  
150 100 250 30
# TextControl3
200 150 180 25
```

### 2. 핵심 함수들

- **LoadCoordinatesFromFile()**: C언어 스타일 파일 읽기 함수
- **MoveTextControl()**: 텍스트 컨트롤 위치 변경 함수
- **OnBnClickedLoadCoordinates()**: 좌표 파일 로드 버튼 이벤트 핸들러
- **OnBnClickedResetPositions()**: 위치 리셋 버튼 이벤트 핸들러

### 3. C언어 파일 입출력 특징

```cpp
// 순수 C 스타일 파일 읽기
FILE* file = nullptr;
errno_t err = _tfopen_s(&file, filePath, _T("r"));

char line[256];
while (fgets(line, sizeof(line), file) && coordIndex < 3)
{
    // 좌표 파싱
    int x, y, width, height;
    if (sscanf_s(line, "%d %d %d %d", &x, &y, &width, &height) == 4)
    {
        // 좌표 저장
    }
}
```

## 사용 방법

1. MFC 프로젝트에 파일들을 추가
2. 리소스 파일에서 다이얼로그와 컨트롤 ID 설정
3. coordinates.txt 파일에 원하는 좌표 입력
4. "좌표 파일 로드" 버튼으로 좌표 적용
5. "위치 리셋" 버튼으로 원래 위치 복원

## 컴파일 요구사항

- Visual Studio with MFC
- Windows SDK
- C++/CLI 또는 C++ 표준 라이브러리

## 특징

- **순수 C 스타일 파일 입출력** 사용
- **동적 컨트롤 위치 변경** 지원
- **오류 처리** 및 **사용자 피드백** 제공
- **원본 위치 복원** 기능
- **주석이 있는 좌표 파일** 지원