# 고객 정보 CRUD 콘솔 애플리케이션

## 프로젝트 개요

JSON 파일을 영구 저장소로 사용하는 C++ 고객 정보 관리 콘솔 애플리케이션.
Create / Read / Update / Delete 기능을 제공하며 데이터는 로컬 JSON 파일에 유지된다.

## 기술 스택

- **언어**: C++ (C++17 이상)
- **IDE / 빌드**: Visual Studio 2022, MSBuild (`.sln` / `.vcxproj`)
- **JSON 라이브러리**: [nlohmann/json](https://github.com/nlohmann/json) — 단일 헤더(`include/nlohmann/json.hpp`)로 포함
- **플랫폼**: Windows 11

## JSON 처리 방식 (POC 참고)

> 참조: https://github.com/ydh1305/json_library_poc

POC의 패턴을 그대로 적용한다.

### 핵심 패턴

```cpp
#include <nlohmann/json.hpp>
using json = nlohmann::json;
```

| 용도 | POC 패턴 |
|---|---|
| 파일 읽기 | `std::ifstream ifs("customers.json"); ifs >> root;` |
| 파일 쓰기 | `std::ofstream ofs("customers.json"); ofs << root.dump(4);` |
| 값 추출 | `root.at("name").get<std::string>()` |
| 값 수정 | `root["field"] = new_value;` |
| 배열 순회 | `for (const auto& item : root)` |
| 1단계 평탄화 | `json_to_flat_map(j)` → `unordered_map<string,string>` |
| 중첩 평탄화 | `flatten_recursive(j, "", out)` → dot-notation 키 |

### JSON 파일 구조 (예정)

```json
{
    "customers": [
        {
            "id": 1,
            "name": "홍길동",
            "email": "hong@example.com",
            "phone": "010-1234-5678",
            "address": "서울시 강남구",
            "created_at": "2026-06-11"
        }
    ],
    "next_id": 2
}
```

## 고객 데이터 필드

| 필드 | 타입 | 설명 |
|---|---|---|
| `id` | int | 자동 증가 고유 식별자 |
| `name` | string | 고객 이름 |
| `email` | string | 이메일 주소 |
| `phone` | string | 전화번호 |
| `address` | string | 주소 |
| `created_at` | string | 등록일 (YYYY-MM-DD) |

## 예정 프로젝트 구조

```
console_application/
├── console_application.sln
├── include/
│   └── nlohmann/
│       └── json.hpp          # POC와 동일한 위치
└── console_application/
    ├── console_application.vcxproj
    ├── main.cpp
    ├── Customer.h
    ├── Customer.cpp
    ├── CustomerRepository.h  # JSON 파일 I/O 담당
    ├── CustomerRepository.cpp
    ├── CustomerService.h     # CRUD 비즈니스 로직
    ├── CustomerService.cpp
    └── data/
        └── customers.json    # 실행 시 자동 생성
```

## CRUD 기능 명세

- **Create** : 새 고객 추가, `next_id` 자동 증가
- **Read** : 전체 목록 조회 / ID로 단건 조회
- **Update** : ID로 고객 검색 후 필드 수정
- **Delete** : ID로 고객 삭제

## 빌드 및 실행

```
# Visual Studio에서 솔루션 열기
console_application.sln

# 또는 MSBuild CLI
msbuild console_application.sln /p:Configuration=Release
```

실행 파일과 같은 디렉토리에 `data/customers.json`이 없으면 자동 생성된다.

## 관련 문서

- [커밋 컨벤션](docs/commit_convention.md) — Conventional Commits 기반 커밋 메시지 규칙

## 개발 시 주의사항

- nlohmann/json 헤더는 POC와 동일하게 `include/nlohmann/json.hpp` 경로 사용
- JSON 파일 읽기 실패 시 빈 customers 배열로 초기화 (POC의 inline_json 폴백 패턴 참고)
- 파일 쓰기는 항상 `dump(4)` (들여쓰기 4칸)로 가독성 유지
- `root.at()` 사용 시 키 부재 예외(`json::out_of_range`)를 적절히 처리
