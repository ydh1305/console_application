#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "Customer.h"
#include "CustomerRepository.h"
#include "CustomerService.h"

static void printDivider()
{
    std::cout << "-----------------------------\n";
}

static void printMenu()
{
    std::cout << "\n=============================\n";
    std::cout << "  고객 정보 관리 시스템\n";
    std::cout << "=============================\n";
    std::cout << " 1. 고객 추가       (Create)\n";
    std::cout << " 2. 전체 목록 조회  (Read All)\n";
    std::cout << " 3. ID로 검색       (Read by ID)\n";
    std::cout << " 4. 키/값으로 검색  (Read by Key)\n";
    std::cout << " 5. 고객 정보 수정  (Update)\n";
    std::cout << " 6. 고객 삭제       (Delete)\n";
    std::cout << " 0. 종료\n";
    std::cout << "=============================\n";
    std::cout << "선택: ";
}

static void printCustomer(const Customer& c)
{
    printDivider();
    std::cout << "ID       : " << c.id         << "\n";
    std::cout << "이름     : " << c.name        << "\n";
    std::cout << "이메일   : " << c.email       << "\n";
    std::cout << "전화번호 : " << c.phone       << "\n";
    std::cout << "주소     : " << c.address     << "\n";
    std::cout << "등록일   : " << c.created_at  << "\n";
}

static std::string promptLine(const std::string& label)
{
    std::string value;
    while (true)
    {
        std::cout << label;
        std::getline(std::cin, value);
        if (!value.empty()) return value;
        std::cout << "  입력값이 비어 있습니다. 다시 입력해 주세요.\n";
    }
}

static void handleCreate(CustomerService& svc)
{
    std::cout << "\n[ 고객 추가 ]\n";
    Customer c;
    c.id         = 0; // service에서 자동 부여
    c.name       = promptLine("이름     : ");
    c.email      = promptLine("이메일   : ");
    c.phone      = promptLine("전화번호 : ");
    c.address    = promptLine("주소     : ");
    c.created_at = promptLine("등록일 (YYYY-MM-DD) : ");

    svc.create(c);
    std::cout << "  고객이 추가되었습니다.\n";
}

static void handleReadAll(CustomerService& svc)
{
    std::cout << "\n[ 전체 고객 목록 ]\n";
    auto list = svc.readAll();
    if (list.empty())
    {
        std::cout << "  등록된 고객이 없습니다.\n";
        return;
    }
    for (const auto& c : list)
        printCustomer(c);
    printDivider();
}

static void handleReadById(CustomerService& svc)
{
    std::cout << "\n[ ID로 고객 검색 ]\n";
    int id;
    std::cout << "검색할 ID: ";
    std::cin >> id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    Customer c = svc.readById(id);
    printCustomer(c);
    printDivider();
}

static void handleReadByKey(CustomerService& svc)
{
    std::cout << "\n[ 키/값으로 고객 검색 ]\n";
    std::cout << "검색 가능 필드: name, email, phone, address, created_at\n";
    std::string key   = promptLine("필드명 : ");
    std::string value = promptLine("검색값 : ");

    auto list = svc.readByKey(key, value);
    if (list.empty())
    {
        std::cout << "  검색 결과가 없습니다.\n";
        return;
    }
    for (const auto& c : list)
        printCustomer(c);
    printDivider();
}

static void handleUpdate(CustomerService& svc)
{
    std::cout << "\n[ 고객 정보 수정 ]\n";
    int id;
    std::cout << "수정할 고객 ID: ";
    std::cin >> id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "수정 가능 필드: name, email, phone, address, created_at\n";
    std::string field = promptLine("필드명 : ");
    std::string value = promptLine("새 값  : ");

    svc.update(id, field, value);
    std::cout << "  수정이 완료되었습니다.\n";
}

static void handleDelete(CustomerService& svc)
{
    std::cout << "\n[ 고객 삭제 ]\n";
    int id;
    std::cout << "삭제할 고객 ID: ";
    std::cin >> id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "정말 삭제하시겠습니까? [y/N]: ";
    std::string confirm;
    std::getline(std::cin, confirm);
    if (confirm != "y" && confirm != "Y")
    {
        std::cout << "  삭제가 취소되었습니다.\n";
        return;
    }

    svc.remove(id);
    std::cout << "  삭제가 완료되었습니다.\n";
}

int main()
{
    CustomerRepository repo;
    CustomerService    svc(repo);

    int choice = -1;
    while (true)
    {
        printMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        try
        {
            switch (choice)
            {
            case 1: handleCreate(svc);    break;
            case 2: handleReadAll(svc);   break;
            case 3: handleReadById(svc);  break;
            case 4: handleReadByKey(svc); break;
            case 5: handleUpdate(svc);    break;
            case 6: handleDelete(svc);    break;
            case 0:
                std::cout << "프로그램을 종료합니다.\n";
                return 0;
            default:
                std::cout << "  잘못된 입력입니다.\n";
                break;
            }
        }
        catch (const std::exception& e)
        {
            std::cout << "  오류: " << e.what() << "\n";
        }
    }
}
