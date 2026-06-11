#include "CustomerRepository.h"
#include <fstream>
#include <filesystem>

json CustomerRepository::load()
{
    std::ifstream ifs(FILE_PATH);
    if (!ifs.is_open())
    {
        // PoC 폴백 패턴: 파일 없으면 빈 구조로 초기화
        return { {"customers", json::array()}, {"next_id", 1} };
    }

    json root;
    ifs >> root;
    return root;
}

void CustomerRepository::save(const json& root)
{
    std::filesystem::create_directories("data");
    std::ofstream ofs(FILE_PATH);
    if (!ofs.is_open())
        throw std::runtime_error("customers.json 파일을 저장할 수 없습니다.");
    ofs << root.dump(4);
}
