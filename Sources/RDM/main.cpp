
// 2023.12.23���� ���ǻ����Դϴ�. �ݵ�� �о��ּ���.
// 1. �� ������ filesystem���̺귯���� ������� C++17 �̻��� ���ǿ��� ����
// �����մϴ�.
// 2. ���� ������ ��ηδ� �����̿��� ������ �� ���� ��ΰ� ��������ϴ�.
//    ����� ���� ���� �� ���� �ÿ��� ���� ���� ���̸�,
//    �ǻ�� �ÿ��� ��� ����� ��ġ �������� game���� ���ΰ� �Ǿ�� �մϴ�.
//    ���� �ǻ��ÿ��� �ݵ�� game���� ���ο��� �����ؾ߸� �մϴ�.
// 3, �� ������ main.cpp, resource_manager.cpp, header.cpp 3���� ���Ϸ� �̷����
// ������
//    �� cpp���ϰ� �Բ� game���� �ȿ� script.rpy������ �����ؾ� ����� ������
//    �����մϴ�.
// 4. ��ü ������ ������ ���� �������� ������ ���� ���ҽ� ���� �۾��� ��������
// �ʽ��ϴ�.
//    �ݵ�� ������ ������ ���� ���� 4���� rpyȮ���� ������ �����ϴ� ���¿���
//    ������ �ּ���.

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
  cout << "������ ���� ���ҽ� ���� ����Դϴ�." << endl;
  cout << "�ؾ� �� �۾��� ��ȣ�� �Է��� �ּ���." << endl;
  cout << "���ǻ��� : ���ҽ� ���ǰ� �Ǿ� ���� ������ ��� ���ҽ� ������ "
          "�Ұ����մϴ�."
       << endl;
  cout
      << "�ݵ�� ���ҽ� ���� �۾��� ��ģ �ڿ� ��� ���ҽ� ������ ������ �ּ���."
      << endl;

  while (true) {
    cout << "1. ��ü ������" << endl;
    cout << "2. �κ� ������" << endl;
    cout << "3. ���� ���ҽ� ����" << endl;
    cin >> choice;

    if (choice == 1) {
      cout << "��ü ������ �۾��� �����մϴ�." << endl;
      DefineAll();
      break;
    } else if (choice == 2) {
      cout << "�κ� ������ �۾��� �����մϴ�." << endl;
      cout << "���ϴ� �۾��� ��ȣ�� �Է��� �ּ���." << endl;
      while (true) {
        bool subchoice_wrong_input = false;

        cout << "1. BGM ������" << endl;
        cout << "2. SE ������" << endl;
        cout << "3. SCG ������" << endl;
        cout << "4. BG ������" << endl;
        cin >> subchoice;
        subchoice_wrong_input = SubChoice(subchoice);
        if (subchoice_wrong_input == true) {
          continue;
        }
        break;
      }
      break;
    } else if (choice == 3) {
      cout << "���� ���ҽ� ���� �۾��� �����մϴ�." << endl;
      ScriptChecker();
      break;
    } else {
      cout << "�߸��� �Է��Դϴ�. �ٽ� �Է��� �ּ���." << endl;
      continue;
    }
  }
  return 0;
}

bool SubChoice(int subchoice) {
  if (subchoice == 1) {
    cout << "BGM �����Ǹ� �����մϴ�." << endl;
    BGMDefine();
    return false;
  } else if (subchoice == 2) {
    cout << "SE �����Ǹ� �����մϴ�." << endl;
    SEDefine();
    return false;
  } else if (subchoice == 3) {
    cout << "SCG �����Ǹ� �����մϴ�." << endl;
    SCGDefine();
    return false;
  } else if (subchoice == 4) {
    cout << "BG �����Ǹ� �����մϴ�." << endl;
    BGDefine();
    return false;
  } else {
    cout << "�߸��� �Է��Դϴ�." << endl;
    return true;
  }
}
