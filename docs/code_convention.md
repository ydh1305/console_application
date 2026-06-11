# Code Convention

C++17 기준, Visual Studio 2022 환경에서 적용한다.

---

## 네이밍

| 대상 | 규칙 | 예시 |
|---|---|---|
| 클래스 / 구조체 | PascalCase | `CustomerService`, `Customer` |
| 함수 / 메서드 | camelCase | `readAll()`, `from_json()` |
| 변수 (지역 / 매개변수) | camelCase | `newCustomer`, `fieldName` |
| 멤버 변수 | camelCase + 후위 `_` | `repo_`, `filePath_` |
| 상수 / `constexpr` | UPPER_SNAKE_CASE | `FILE_PATH`, `MAX_RETRY` |
| 파일명 | PascalCase | `CustomerRepository.cpp` |

---

## 파일 구성

- 헤더(`.h`)에는 선언만, 구현(`.cpp`)에는 정의만 작성한다.
- 헤더 가드는 `#pragma once`를 사용한다.
- `#include` 순서: 대응 헤더 → 프로젝트 헤더 → 표준 라이브러리 → 서드파티

```cpp
// CustomerService.cpp 예시
#include "CustomerService.h"   // 1. 대응 헤더
#include "Customer.h"          // 2. 프로젝트 헤더
#include <vector>              // 3. 표준 라이브러리
#include <nlohmann/json.hpp>   // 4. 서드파티
```

---

## 서식

- 들여쓰기: **스페이스 4칸** (탭 금지)
- 중괄호: **Allman 스타일** (여는 중괄호를 다음 줄에)

```cpp
void CustomerService::create(const Customer& c)
{
    json root = repo_.load();
    // ...
}
```

- 한 줄 최대 길이: **120자**
- 포인터 / 참조 기호는 타입에 붙인다: `std::string& value`, `json* ptr`

---

## 클래스

- 접근 지정자 순서: `public` → `protected` → `private`
- 생성자 초기화는 멤버 초기화 리스트를 사용한다.

```cpp
CustomerService::CustomerService(CustomerRepository& repo)
    : repo_(repo)
{}
```

- 복사/이동이 불필요한 클래스는 명시적으로 삭제한다.

```cpp
CustomerService(const CustomerService&)            = delete;
CustomerService& operator=(const CustomerService&) = delete;
```

---

## 함수

- 함수 하나는 한 가지 역할만 수행한다.
- 매개변수가 3개를 초과하면 구조체로 묶는 것을 검토한다.
- 출력 전용 매개변수는 포인터, 입출력은 참조, 읽기 전용은 `const` 참조를 사용한다.

---

## 오류 처리

- 복구 불가능한 오류는 `std::runtime_error`를 throw한다.
- `main` 또는 UI 핸들러에서 `catch (const std::exception& e)`로 처리한다.
- 반환값으로 오류를 표현하지 않는다 (매직 넘버 `-1`, `nullptr` 반환 금지).

---

## JSON 처리 (PoC 패턴 준수)

- `using json = nlohmann::json;` 은 헤더 파일에 한 번만 선언한다.
- 값 읽기는 `.at("key").get<T>()`를 사용한다 (`operator[]` 읽기 금지 — 키 없을 때 기본값 삽입 방지).
- 파일 쓰기는 항상 `dump(4)` (들여쓰기 4칸)로 가독성을 유지한다.

```cpp
// Good
std::string name = j.at("name").get<std::string>();

// Bad
std::string name = j["name"];
```

---

## 주석

- 주석은 **WHY**를 설명할 때만 작성한다 (WHAT은 코드로 표현).
- 한 줄 주석은 `//` 뒤에 스페이스 한 칸을 둔다.
- 멀티라인 주석 블록(`/* */`)은 사용하지 않는다.

```cpp
// PoC 폴백 패턴: 파일 없으면 빈 구조로 초기화
return { {"customers", json::array()}, {"next_id", 1} };
```

---

## 기타

- `auto`는 타입이 문맥상 명확한 경우에만 사용한다.
- 범위 기반 `for`를 우선 사용하고, 인덱스가 필요한 경우에만 일반 `for`를 사용한다.
- `std::endl` 대신 `"\n"`을 사용한다 (불필요한 flush 방지).
