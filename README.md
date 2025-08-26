# MFC TextControl 좌표 변경 예제

이 프로젝트는 C언어와 MFC를 사용하여 파일에서 좌표를 읽어와서 텍스트 컨트롤의 위치를 동적으로 변경하는 방법을 보여주는 예제입니다.

## 파일 구성

- `coordinates.txt`: 좌표 데이터가 저장된 텍스트 파일
- `TextControlDlg.h`: MFC 다이얼로그 헤더 파일
- `TextControlDlg.cpp`: 메인 구현 파일 (파일 읽기 및 컨트롤 위치 변경 로직)
- `resource.h`: 리소스 ID 정의
- `TextControlApp.rc`: MFC 리소스 파일

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

### `LoadCoordinatesFromFile()`
```cpp
BOOL LoadCoordinatesFromFile(const CString& filename)
```
- 파일에서 좌표 데이터를 읽어오는 함수
- std::ifstream을 사용한 C++ 스타일 파일 읽기
- 주석 라인과 빈 라인을 자동으로 건너뛰기

### `UpdateTextControlPosition()`
```cpp
void UpdateTextControlPosition(int controlID, const TextControlCoords& coords)
```
- 특정 컨트롤의 위치와 크기를 업데이트하는 함수
- SetWindowPos()를 사용하여 컨트롤 위치 변경
- 변경 후 화면 갱신

## 컴파일 및 실행

1. Visual Studio에서 MFC 프로젝트를 생성합니다.
2. 제공된 파일들을 프로젝트에 추가합니다.
3. 프로젝트를 빌드하고 실행합니다.
4. "좌표 파일 로드" 버튼을 클릭하여 coordinates.txt 파일을 선택합니다.
5. 텍스트 컨트롤들의 위치가 파일에 정의된 좌표로 변경되는 것을 확인합니다.

## 기술적 특징

- **MFC 다이얼로그 기반**: Windows MFC 프레임워크 사용
- **파일 I/O**: C++ 표준 라이브러리의 ifstream 사용
- **동적 UI 변경**: 런타임에 컨트롤 위치 변경
- **에러 처리**: 파일 읽기 실패 시 사용자에게 알림