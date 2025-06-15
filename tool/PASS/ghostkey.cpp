#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <openssl/sha.h>
#include <ostream>
#include <sstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>

#include "../../core/menu.hpp"
#include "../../core/visual/banner.hpp"

void delete_line(int target_line_num) {
  const std::string folder = "data";
  const std::string filename = folder + "/zxc_P.txt";

  if (!std::filesystem::exists(folder)) {
    if (!std::filesystem::create_directory(folder)) {
      std::cerr << "ERROR: Cannot create directory: " << folder << std::endl;
      return;
    }
  }

  std::ifstream file(filename);

  if (!file) {
    std::cerr << std::endl;
    std::cerr << "ERROR: FILE IS NOT OPEN" << std::endl;
    return;
  }

  std::vector<std::string> lines;
  std::string line;
  int current_line = 1;

  while (std::getline(file, line)) {
    if (current_line != target_line_num) {
      lines.push_back(line);
    }
    current_line++;
  }

  file.close();

  std::ofstream out(filename, std::ios::trunc);
  for (const auto &l : lines) {
    out << l << '\n';
  }
  out.close();

  chmod("data", S_IRWXU);
  chmod("data/zxc_P.txt", S_IRUSR | S_IWUSR);

  std::cout << "  PASS [" << target_line_num << "] DELETE" << std::endl;
}

void out_P() {
  const std::string folder = "data";
  const std::string filename = folder + "/zxc_P.txt";

  if (!std::filesystem::exists(folder)) {
    if (!std::filesystem::create_directory(folder)) {
      std::cerr << "ERROR: Cannot create directory: " << folder << std::endl;
      return;
    }
  }

  std::ifstream file(filename);

  if (!file) {
    std::cerr << std::endl;
    std::cerr << "ERROR: FILE IS NOT OPEN" << std::endl;
    return;
  }

  std::string line;
  int num = 0;

  std::cout << std::endl;
  std::cout << "  --- HASH PASS ---" << std::endl;

  while (std::getline(file, line)) {
    num++;
    std::cout << "  [ " << num << " ] ";
    std::cout << line << std::endl;
  }
  chmod("data", S_IRWXU);
  chmod("data/zxc_P.txt", S_IRUSR | S_IWUSR);
}

void data(std::string in_service, std::string pass, std::string in_pass) {
  const std::string folder = "data";
  const std::string filename = folder + "/zxc_P.txt";

  if (!std::filesystem::exists(folder)) {
    if (!std::filesystem::create_directory(folder)) {
      std::cerr << "ERROR: Cannot create directory: " << folder << std::endl;
      return;
    }
  }

  std::ofstream file(filename, std::ofstream::app);
  if (!file.is_open()) {
    std::cerr << std::endl;
    std::cerr << "ERROR: FILE IS NOT OPEN" << std::endl;
    return;
  }

  file << in_service << ": ";
  file << in_pass << " > ";
  file << pass << std::endl;

  file.close();
  chmod("data", S_IRWXU);
  chmod("data/zxc_P.txt", S_IRUSR | S_IWUSR);
}

std::string sha256(const std::string str) {
  unsigned char hash[SHA256_DIGEST_LENGTH];

  SHA256_CTX sha256;
  SHA256_Init(&sha256);
  SHA256_Update(&sha256, str.c_str(), str.size());
  SHA256_Final(hash, &sha256);

  std::stringstream ss;

  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
    ss << std::hex << std::setw(2) << std::setfill('0')
       << static_cast<int>(hash[i]);
  }
  return ss.str();
}

void ghostkey() {
  clear_console();
  main_banner();
  char d_a = 'a';
  std::string in_service = "";
  int in_len_pass = 1;
  std::string in_pass = "";

  std::cout << std::endl;
  std::cout << "  [ 1 ] DEL OR ADD? ( D/A ): ";
  std::cin >> d_a;

  if (d_a == 'A') {
    std::cout << "  [ 1 ] IN SERVICE: ";
    std::cin >> in_service;

    std::cout << "  [ 1 ] IN LEN PASS: ";
    std::cin >> in_len_pass;

    if (std::cin.fail()) {
      std::cin.clear();
      std::cout << std::endl;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "  ERROR: IN LEN PASS" << std::endl;
      wait_and_return_to_menu();
      return;
    }

    std::cout << "  [ 1 ] IN PASS: ";
    std::cin >> in_pass;

    std::string pass = sha256(in_pass).substr(0, in_len_pass);

    std::cout << std::endl;
    std::cout << "  [ " << in_pass << " > " << pass << " ]" << std::endl;

    data(in_service, pass, in_pass);
  } else if (d_a == 'D') {
    out_P();
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "  IN NUM DEL: ";
    int num;
    std::cin >> num;

    if (std::cin.fail()) {
      std::cin.clear();
      std::cout << std::endl;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "  ERROR: IN LEN DEL" << std::endl;
      wait_and_return_to_menu();
      return;
    }

    delete_line(num);
  } else {
    ghostkey();
  }
}
