#include "banner.hpp"

#include <iostream>
#include <string>

void print_colored(const std::string &text, const std::string &color_code) {
  std::cout << "\033[" << color_code << "m" << text << "\033[0m";
}

void menu_banner() {
  print_colored(R"( 
  [ 1 ] > HASH PASS      ! KEEP
  [ 2 ] > HIDE WALLETS   ! PASS/HASH
  [ 0 ] > ALL OUT PASS   ! ON                                  v1.0
  [ 9 ] > ALL OUT WALLET ! PAPER                           EXIT: ^C
        
  )",
                "38;5;255");
}

void main_banner() {
  print_colored(R"(
    ▄████  ██░ ██  ▒█████    ██████ ▄▄▄█████▓ ██ ▄█▀▓█████▓██   ██▓
   ██▒ ▀█▒▓██░ ██▒▒██▒  ██▒▒██    ▒ ▓  ██▒ ▓▒ ██▄█▒ ▓█   ▀ ▒██  ██▒
  ▒██░▄▄▄░▒██▀▀██░▒██░  ██▒░ ▓██▄   ▒ ▓██░ ▒░▓███▄░ ▒███    ▒██ ██░
  ░▓█  ██▓░▓█ ░██ ▒██   ██░  ▒   ██▒░ ▓██▓ ░ ▓██ █▄ ▒▓█  ▄  ░ ▐██▓░
  ░▒▓███▀▒░▓█▒░██▓░ ████▓▒░▒██████▒▒  ▒██▒ ░ ▒██▒ █▄░▒████▒ ░ ██▒▓░
   ░▒   ▒  ▒ ░░▒░▒░ ▒░▒░▒░ ▒ ▒▓▒ ▒ ░  ▒ ░░   ▒ ▒▒ ▓▒░░ ▒░ ░  ██▒▒▒ 
    ░   ░  ▒ ░▒░ ░  ░ ▒ ▒░ ░ ░▒  ░ ░    ░    ░ ░▒ ▒░ ░ ░  ░▓██ ░▒░ 
  ░ ░   ░  ░  ░░ ░░ ░ ░ ▒  ░  ░  ░    ░      ░ ░░ ░    ░   ▒ ▒ ░░  
        ░  ░  ░  ░    ░ ░        ░           ░  ░      ░  ░░ ░     
                                                           ░ ░      )",
                "38;5;255");
  print_colored(
      R"(

 --------------------------------------------------------------------
    )",
      "38;5;196");
}
