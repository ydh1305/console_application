# Commit Convention

[Conventional Commits 1.0.0](https://www.conventionalcommits.org/en/v1.0.0/) 표준을 따른다.

## 형식

```
<type>(<scope>): <subject>

[body]

[footer]
```

- **type**: 필수
- **scope**: 선택 — 변경 범위를 괄호 안에 명시 (예: `repo`, `service`, `ui`)
- **subject**: 필수 — 50자 이내, 명령형 현재형, 마침표 없음
- **body**: 선택 — 변경 이유 및 이전 동작과의 차이 설명, 한 줄 72자 이내
- **footer**: 선택 — Breaking Change 또는 이슈 참조

---

## Type 목록

| Type | 설명 |
|---|---|
| `feat` | 새로운 기능 추가 |
| `fix` | 버그 수정 |
| `refactor` | 기능 변경 없는 코드 구조 개선 |
| `style` | 포맷, 세미콜론 등 코드 의미에 영향 없는 변경 |
| `docs` | 문서만 변경 |
| `test` | 테스트 추가 또는 수정 |
| `chore` | 빌드 설정, 패키지 관리 등 기타 변경 |
| `perf` | 성능 개선 |
| `ci` | CI/CD 설정 변경 |

---

## 규칙

1. subject는 소문자로 시작하고 마침표로 끝내지 않는다.
2. subject는 명령형으로 작성한다. (`add`, `fix`, `remove` — `added`, `fixed` 사용 금지)
3. 한국어 subject도 허용하며 동사형으로 끝낸다. (예: `고객 목록 조회 기능 추가`)
4. body와 subject 사이에 반드시 빈 줄을 넣는다.
5. Breaking Change는 footer에 `BREAKING CHANGE:` 접두사로 명시한다.

---

## 예시

### 기능 추가
```
[feat](service): add customer search by name
```

### 버그 수정 (body 포함)
```
[fix](repo): prevent crash when customers.json is missing

파일이 없을 때 ofstream이 열리지 않는 경우를 처리하지 않아
첫 실행 시 예외가 발생하는 문제를 수정한다.
```

### 리팩토링
```
[refactor](repo): extract file path constant to header
```

### 문서 변경
```
[docs]: add commit convention guide
```

### Breaking Change
```
[feat](customer): change id field type from int to string

BREAKING CHANGE: customers.json의 id 필드 타입이 변경되어
기존 데이터 파일과 호환되지 않는다.
```

### 한국어 subject
```
[feat](ui): 고객 삭제 확인 프롬프트 추가
```
