#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>

#include "../../core/menu.hpp"
#include "../../core/visual/banner.hpp"
#include "../PASS/ghostkey.hpp"

void delete_wallet_section(const std::string &target_wallet) {
  const std::string folder = "data";
  const std::string filename = folder + "/zxc_W.txt";

  if (!std::filesystem::exists(folder)) {
    if (!std::filesystem::create_directory(folder)) {
      std::cerr << "ERROR: Cannot create directory: " << folder << std::endl;
      return;
    }
  }

  std::ifstream file(filename);

  if (!file) {
    std::cerr << "ERROR: FILE IS NOT OPEN" << std::endl;
    return;
  }

  std::vector<std::string> lines;
  std::string line;
  bool in_target_section = false;

  std::string target_header = target_wallet + ": ";

  while (std::getline(file, line)) {
    line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());

    if (line.find(':') != std::string::npos &&
        line.find('>') == std::string::npos) {
      if (line == target_header) {
        in_target_section = true;
        continue;
      } else {
        in_target_section = false;
      }
    }

    if (!in_target_section) {
      lines.push_back(line);
    }
  }

  file.close();

  std::ofstream out(filename, std::ios::trunc);
  if (!out) {
    std::cerr << "ERROR: CANNOT WRITE FILE" << std::endl;
    return;
  }

  for (const auto &l : lines) {
    out << l << '\n';
  }

  out.close();
  chmod("data", S_IRWXU);
  chmod("data/zxc_W.txt", S_IRUSR | S_IWUSR);

  std::cout << "  WALLET \"" << target_wallet << "\" DELETE" << std::endl;
}

void out_W() {
  const std::string folder = "data";
  const std::string filename = folder + "/zxc_W.txt";

  if (!std::filesystem::exists(folder)) {
    if (!std::filesystem::create_directory(folder)) {
      std::cerr << "ERROR: Cannot create directory: " << folder << std::endl;
      return;
    }
  }

  std::ifstream file(filename);

  if (!file) {
    std::cerr << std::endl;
    std::cerr << "  ERROR: FILE IS NOT OPEN" << std::endl;
    return;
  }

  std::string line;
  int num = 0;

  std::cout << std::endl;
  std::cout << "  --- HIDE WALLET ---" << std::endl;

  while (std::getline(file, line)) {
    std::cout << "  ";
    std::cout << line << std::endl;
    ++num;
  }

  file.close();
  chmod("data", S_IRWXU);
  chmod("data/zxc_W.txt", S_IRUSR | S_IWUSR);

  std::cout << std::endl;
}

void data(std::string in_service, int in_num_words,
          std::vector<std::string> pass, std::string wallet_pass,
          std::string wallet_pass_hash) {
  const std::string folder = "data";
  const std::string filename = folder + "/zxc_W.txt";

  if (!std::filesystem::exists(folder)) {
    if (!std::filesystem::create_directory(folder)) {
      std::cerr << "ERROR: Cannot create directory: " << folder << std::endl;
      return;
    }
  }

  std::ofstream file(filename, std::ofstream::app);
  int num = 1;

  if (!file.is_open()) {
    std::cerr << std::endl;
    std::cerr << "  ERROR: FILE IS NOT OPEN" << std::endl;
    return;
  }

  file << in_service << ": " << std::endl;
  file << "[ PASS ] ";
  file << wallet_pass << " > ";
  file << wallet_pass_hash << std::endl;

  for (std::string p : pass) {
    file << "[ " << num << " ] " << p << std::endl;
    num++;
  }
  file << std::endl;

  file.close();
  chmod("data", S_IRWXU);
  chmod("data/zxc_W.txt", S_IRUSR | S_IWUSR);
}

void hidewallet() {
  clear_console();
  main_banner();
  char d_a = 'a';
  std::string in_service = "";
  int in_num_words = 1;
  std::string in_pass = "";
  std::vector<std::string> pass;

  std::cout << std::endl;
  std::cout << "  [ 2 ] DELL OR ADD? ( D/A ): ";
  std::cin >> d_a;

  if (d_a == 'A') {
    std::cout << "  [ 2 ] IN SERVICE: ";
    std::cin >> in_service;

    std::cout << "  [ 2 ] IN NUM WORD: ";
    std::cin >> in_num_words;

    if (std::cin.fail()) {
      std::cin.clear();
      std::cout << std::endl;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "  ERROR: IN NUM WORD" << std::endl;
      wait_and_return_to_menu();
      return;
    }

    std::cout << std::endl;
    int num = 1;

    for (int i = 0; i < in_num_words; ++i) {
      std::cout << "  [ " << i << " ] " << "IN PASS: ";
      std::cin >> in_pass;
      pass.push_back(in_pass);
    }

    std::cout << std::endl;

    std::string wallet_pass = "";
    int in_len_pass = 1;

    std::cout << "  [ 2 ] IN LEN PASS: ";
    std::cin >> in_len_pass;

    if (std::cin.fail()) {
      std::cin.clear();
      std::cout << std::endl;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "  ERROR: IN LEN PASS" << std::endl;
      wait_and_return_to_menu();
      return;
    }

    std::cout << "  [ 2 ] IN PASS WALLET: ";
    std::cin >> wallet_pass;

    std::string wallet_pass_hash = sha256(wallet_pass).substr(0, in_len_pass);

    std::cout << std::endl;

    std::cout << "  " << in_service << ": " << std::endl;
    std::cout << "  " << wallet_pass_hash << std::endl;

    for (std::string p : pass) {
      std::cout << "   " << num << "> " << p << std::endl;
      num++;
    }

    data(in_service, in_num_words, pass, wallet_pass, wallet_pass_hash);

  } else if (d_a == 'D') {
    out_W();
    std::string name;
    std::cout << "  IN NAME DEL: ";
    std::cin >> name;
    delete_wallet_section(name);

  } else {
    hidewallet();
  }
}
