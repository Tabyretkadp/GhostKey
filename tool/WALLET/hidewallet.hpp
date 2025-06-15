#pragma once

#include <string>
#include <vector>

void delete_wallet_section(const std::string& target_wallet);
void out_W();
void data(std::string in_service, int in_num_words,
          std::vector<std::string> pass, std::string wallet_pass, std::string wallet_pass_hash);
void hidewallet();