#include "CustomerRepository.h"
#include <fstream>
#include <iostream>

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
    std::ofstream ofs(FILE_PATH);
    ofs << root.dump(4);
}
