// btcscript - Bitcoin script disassembler
//
// Description:
// Takes a file with Bitcoin Script bytecode as hex and prints the disassembly
// of that file.
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

#include <prevector.h>
#include <script/script.h>
using namespace std;

void PrintUsage() {
  std::cout << "USAGE: btcscript HEXFILE" << std::endl;
  std::cout << "Takes a file with hex string of Bitcoin Script bytecode and prints the" << std::endl;
  std::cout << "opcodes composing the script." << std::endl;
}

std::vector<unsigned char> HexStringToBytes(const std::string& hex) {
  std::vector<unsigned char> result;
  unsigned char byte;
  for (size_t i = 0; i < hex.length(); i += 2) {
    sscanf(hex.c_str() + i, "%2hhx", &byte);
    result.push_back(byte);
  }
  return result;
}

std::string ReadWholeFile(char* filePath) {
  std::ifstream f(filePath);

  if (!f.is_open()) {
    return "";
  }

  std::string result;

  f.seekg(0, std::ios::end);
  result.reserve(f.tellg());
  f.seekg(0, std::ios::beg);

  result.assign((std::istream_iterator<char>(f)),
                std::istream_iterator<char>());

  return result;
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    PrintUsage();
    return EXIT_FAILURE;
  }

  std::string scriptFileData = ReadWholeFile(argv[1]);
  if (scriptFileData.empty()) {
    std::cerr << "error: unable to read file '" << argv[1] << "'." << std::endl;
    return EXIT_FAILURE;
  }

  std::vector<unsigned char> scriptBytes = HexStringToBytes(scriptFileData);
  CScript script = CScript(scriptBytes.begin(), scriptBytes.end());
  if (!script.HasValidOps()) {
    std::cerr << "error: script contains invalid opcodes" << std::endl;
    return EXIT_FAILURE;
  }

  prevector<28, unsigned char>::const_iterator programCounter = script.begin();
  opcodetype nextOpcode;
  std::vector<unsigned char> returnData;

  while (programCounter != script.end()) {
    // Handle implicit OP_PUSHBYTES_NN opcodes.
    //
    // Any opcode in range [0x01, 0x4b] is interpreted as an OP_PUSHBYTES with
    // the number of bytes matching the opcode value. For example, 0x0A is an
    // OP_PUSHBYTES_10.
    if (*programCounter >= 0x01 && *programCounter <= 0x4b) {
      size_t numBytes = (size_t)*programCounter;
      std::cout << "OP_PUSHBYTES_" << std::dec << numBytes << " ";
      programCounter++;

      for (size_t i = 0; i < numBytes && programCounter != script.end(); i++) {
        std::cout << std::setfill('0') << std::setw(2) << std::hex << (int)*programCounter;
        programCounter++;
      }

      if (programCounter != script.end()) {
        std::cout << " ";
      }
    } else {
      script.GetOp(programCounter, nextOpcode, returnData);
      std::cout << GetOpName(nextOpcode);
      if (programCounter != script.end()) {
        std::cout << " ";
      }

      if (!returnData.empty()) {
        for (auto it = returnData.begin(); it != returnData.end(); it++) {
          std::cout << std::setfill('0') << std::setw(2) << std::hex << (int)*it;
        }

        if (programCounter != script.end()) {
          std::cout << " ";
        }
      }
    }
  }

  return EXIT_SUCCESS;
}
