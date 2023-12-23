
// 2023.12.23기준 주의사항입니다. 반드시 읽어주세요.
// 1. 본 파일은 filesystem라이브러리의 사용으로 C++17 이상의 조건에서 구동
// 가능합니다.
// 2. 현재 파일의 경로로는 렌파이에서 구동할 수 없는 경로가 만들어집니다.
//    현재는 단지 제출 및 구동 시연을 위한 것일 뿐이며,
//    실사용 시에는 상대 경로의 위치 기준점이 game폴더 내부가 되어야 합니다.
//    따라서 실사용시에는 반드시 game폴더 내부에서 구동해야만 합니다.
// 3, 이 파일은 main.cpp, resource_manager.cpp, header.cpp 3개의 파일로 이루어져
// 있으며
//    세 cpp파일과 함께 game폴더 안에 script.rpy파일이 존재해야 제대로 구동이
//    가능합니다.
// 4. 전체 재정의 과정을 먼저 진행하지 않으면 사용된 리소스 검출 작업은 구동되지
// 않습니다.
//    반드시 재정의 과정을 통해 나온 4개의 rpy확장자 파일이 존재하는 상태에서
//    구동해 주세요.

#include <filesystem>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "header.h"

using namespace std;
namespace fs = std::filesystem;

int main() {
  int choice = 0;
  int subchoice = 0;
  cout << endl;
  cout << "렌파이 전용 리소스 관리 모듈입니다." << endl;
  cout << "해야 할 작업의 번호를 입력해 주세요." << endl;
  cout << "주의사항 : 리소스 정의가 되어 있지 않으면 사용 리소스 검출이 "
          "불가능합니다."
       << endl;
  cout
      << "반드시 리소스 정의 작업을 거친 뒤에 사용 리소스 검출을 진행해 주세요."
      << endl;

  while (true) {
    cout << "1. 전체 재정의" << endl;
    cout << "2. 부분 재정의" << endl;
    cout << "3. 사용된 리소스 검출" << endl;
    cin >> choice;

    if (choice == 1) {
      cout << "전체 재정의 작업을 수행합니다." << endl;
      DefineAll();
      break;
    } else if (choice == 2) {
      cout << "부분 재정의 작업을 수행합니다." << endl;
      cout << "원하는 작업의 번호를 입력해 주세요." << endl;
      while (true) {
        bool subchoice_wrong_input = false;

        cout << "1. BGM 재정의" << endl;
        cout << "2. SE 재정의" << endl;
        cout << "3. SCG 재정의" << endl;
        cout << "4. BG 재정의" << endl;
        cin >> subchoice;
        subchoice_wrong_input = SubChoice(subchoice);
        if (subchoice_wrong_input == true) {
          continue;
        }
        break;
      }
      break;
    } else if (choice == 3) {
      cout << "사용된 리소스 검출 작업을 시작합니다." << endl;
      ScriptChecker();
      break;
    } else {
      cout << "잘못된 입력입니다. 다시 입력해 주세요." << endl;
      continue;
    }
  }
  return 0;
}

bool SubChoice(int subchoice) {
  if (subchoice == 1) {
    cout << "BGM 재정의를 시작합니다." << endl;
    BGMDefine();
    return false;
  } else if (subchoice == 2) {
    cout << "SE 재정의를 시작합니다." << endl;
    SEDefine();
    return false;
  } else if (subchoice == 3) {
    cout << "SCG 재정의를 시작합니다." << endl;
    SCGDefine();
    return false;
  } else if (subchoice == 4) {
    cout << "BG 재정의를 시작합니다." << endl;
    BGDefine();
    return false;
  } else {
    cout << "잘못된 입력입니다." << endl;
    return true;
  }
}
