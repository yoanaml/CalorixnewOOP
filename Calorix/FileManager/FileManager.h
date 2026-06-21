#pragma once
#include <string>

class Calorix;

class FileManager
{
public:
    static void save(const Calorix& system, const std::string& filename);
    static void load(Calorix& system, const std::string& filename);
};

