#include <filesystem>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "header.h"

using namespace std;
namespace fs = std::filesystem;

void DefineAll() {
  BGMDefine();
  SEDefine();
  SCGDefine();
  BGDefine();
}

void BGMDefine() {
  vector<string> original_bgm_file_paths;
  vector<string> original_bgm_file_names;
  vector<string> modified_bgm_file_names;
  string bgm_output_filename = "bgm.rpy";
  ofstream out_file(bgm_output_filename);

  fs::path bgm_dir = "./renpy_example/game/audio/BGM/";  // ���� ��� ����
  if (fs::exists(bgm_dir) &&
      fs::is_directory(bgm_dir))  // �ش� ���丮 ���� ���� Ȯ��
  {
    try {
      // ���丮 ���� ��� ���ϰ� ���� ���丮�� ����� ��ȸ
      cout << "���� ��� ã����..." << endl;
      for (const auto& entry : fs::recursive_directory_iterator(bgm_dir)) {
        if (fs::is_regular_file(entry)) {
          // ���� ��ο� ������ ���ڿ��� ��ȯ�Ͽ� ���Ϳ� �߰�.
          // filename()���� ���ϸ� ����, stem()���� Ȯ���� ����.
          original_bgm_file_paths.push_back(entry.path().string());
          original_bgm_file_names.push_back(
              entry.path().filename().stem().string());
        }
        // ���� ��� ���
        cout << entry.path() << endl;
      }
      cout << "���ϸ��� ������ �ν� ���� �������� ��ȯ��..." << endl;
      for (const auto& str : original_bgm_file_names) {
        string modified = str;

        // ���� ���񿡼� �����̰� �ν� �Ұ����� ����� �������� ����ٷ� ����
        for (char& c : modified) {
          if (c == ' ')
            c = '_';
          else if (c == '-')
            c = '_';
        }
        // ����� ���ڿ��� �� ���Ϳ� �߰�
        modified_bgm_file_names.push_back(modified);
      }
      // ������ ���ϸ� ���
      for (const auto& str : modified_bgm_file_names) cout << str << endl;

      cout << "���� ������..." << endl;
      if (out_file.is_open()) {
        out_file << "init:" << endl;
        // ���� �迭�� ������ ���� �����ϱ�
        for (size_t i = 0; i < modified_bgm_file_names.size(); ++i) {
          out_file << "    define audio." << modified_bgm_file_names[i]
                   << " = ";
          out_file << "\"" << original_bgm_file_paths[i] << "\"" << endl;
        }
        out_file.close();  // ���� ��Ʈ�� �ݱ�
        cout << "���� ���� �Ϸ�: " << bgm_output_filename << endl;
      } else {
        cerr << "������ �� �� �����ϴ�: " << bgm_output_filename << endl;
      }
    } catch (const fs::filesystem_error& e) {
      cerr << e.what() << endl;
    }
  } else {
    cout << "���丮�� �������� �ʽ��ϴ�." << endl;
    cout << "�������� ���ư��ϴ�." << endl;
  }
}

void SEDefine() {
  vector<string> original_se_file_paths;
  vector<string> original_se_file_names;
  vector<string> modified_se_file_names;
  string se_output_filename = "se.rpy";
  ofstream out_file(se_output_filename);

  fs::path se_dir = "./renpy_example/game/audio/SE/";  // ���� ��� ����
  if (fs::exists(se_dir) &&
      fs::is_directory(se_dir))  // �ش� ���丮 ���� ���� Ȯ��
  {
    try {
      // ���丮 ���� ��� ���ϰ� ���� ���丮�� ����� ��ȸ
      cout << "���� ��� ã����..." << endl;
      for (const auto& entry : fs::recursive_directory_iterator(se_dir)) {
        if (fs::is_regular_file(entry)) {
          // ���� ��ο� ������ ���ڿ��� ��ȯ�Ͽ� ���Ϳ� �߰�.
          // filename()���� ���ϸ� ����, stem()���� Ȯ���� ����.
          original_se_file_paths.push_back(entry.path().string());
          original_se_file_names.push_back(
              entry.path().filename().stem().string());
        }
        // ���� ��� ���
        cout << entry.path() << endl;
      }
      cout << "���ϸ��� ������ �ν� ���� �������� ��ȯ��..." << endl;
      for (const auto& str : original_se_file_names) {
        string modified = str;

        // ���� ���񿡼� �����̰� �ν� �Ұ����� ����� �������� ����ٷ� ����
        for (char& c : modified) {
          if (c == ' ')
            c = '_';
          else if (c == '-')
            c = '_';
        }
        // ����� ���ڿ��� �� ���Ϳ� �߰�
        modified_se_file_names.push_back(modified);
      }
      // ������ ���ϸ� ���
      for (const auto& str : modified_se_file_names) cout << str << endl;

      cout << "���� ������..." << endl;
      if (out_file.is_open()) {
        out_file << "init:" << endl;
        // ���� �迭�� ������ ���� �����ϱ�
        for (size_t i = 0; i < modified_se_file_names.size(); ++i) {
          out_file << "    define audio." << modified_se_file_names[i] << " = ";
          out_file << "\"" << original_se_file_paths[i] << "\"" << endl;
        }
        out_file.close();  // ���� ��Ʈ�� �ݱ�
        cout << "���� ���� �Ϸ�: " << se_output_filename << endl;
      } else {
        cerr << "������ �� �� �����ϴ�: " << se_output_filename << endl;
      }
    } catch (const fs::filesystem_error& e) {
      cerr << e.what() << endl;
    }
  } else {
    cout << "���丮�� �������� �ʽ��ϴ�." << endl;
    cout << "�������� ���ư��ϴ�." << endl;
  }
}

// SCG�� ���ҽ��� ������ �� �ݵ�� ���ϸ� ����ٰ� �ѹ��� ���߸� �Ѵ�.
// �̴� ������ ����� ��Ȱ�� ������ ���� ��¿ �� ����.
// ����ٰ� ���� ������ �迭 ���Կ� ���ܵǵ��� ó���Ǿ���.
void SCGDefine() {
  vector<string> original_scg_file_paths;
  vector<string> original_scg_file_names;
  vector<string> modified_scg_file_names;
  vector<string> modified_first_file_names;
  vector<string> modified_second_file_names;
  string scg_output_filename = "scg.rpy";
  ofstream out_file(scg_output_filename);

  fs::path scg_dir = "./renpy_example/game/images/SCG/";  // ���� ��� ����
  if (fs::exists(scg_dir) &&
      fs::is_directory(scg_dir))  // �ش� ���丮 ���� ���� Ȯ��
  {
    try {
      // ���丮 ���� ��� ���ϰ� ���� ���丮�� ����� ��ȸ
      cout << "���� ��� ã����..." << endl;
      for (const auto& entry : fs::recursive_directory_iterator(scg_dir)) {
        if (fs::is_regular_file(entry)) {
          // ���� ��ο� ������ ���ڿ��� ��ȯ�Ͽ� ���Ϳ� �߰�.
          // filename()���� ���ϸ� ����, stem()���� Ȯ���� ����.
          original_scg_file_paths.push_back(entry.path().string());
          original_scg_file_names.push_back(
              entry.path().filename().stem().string());
        }
        // ���� ��� ���
        cout << entry.path() << endl;
      }
      cout << "���ϸ��� ������ �ν� ���� �������� ��ȯ��..." << endl;
      for (const auto& str : original_scg_file_names) {
        // ����ٰ� ���� ������ �ǳʶ�
        if (str.find('_') == std::string::npos) {
          cout << str << " - ����ٰ� ���� ó������ �ʴ� �����Դϴ�." << endl;
          continue;
        }
        string modified = str;

        // ���� ���񿡼� �����̰� �ν� �Ұ����� ����� �������� ����ٷ� ����
        for (char& c : modified) {
          if (c == ' ')
            c = '_';
          else if (c == '-')
            c = '_';
        }
        // ����� ���ڿ��� �� ���Ϳ� �߰�
        modified_scg_file_names.push_back(modified);
      }

      // ����� ���� ���� ���ڿ��� ù ��° ����ٸ� �������� ����
      for (const auto& str : modified_scg_file_names) {
        size_t underbar_cut = str.find("_");  // ù ��° ������� ��ġ�� ã��
        if (underbar_cut != std::string::npos) {
          modified_first_file_names.push_back(
              str.substr(0, underbar_cut));  // ù ��° �κ�
          modified_second_file_names.push_back(
              str.substr(underbar_cut + 1));  // �� ��° �κ�
        }
      }

      // ������ ���ϸ� ���
      for (const auto& str : modified_scg_file_names) cout << str << endl;

      cout << "���� ������..." << endl;
      if (out_file.is_open()) {
        out_file << "init:" << endl;
        // ���� �迭�� ������ ���� �����ϱ�
        for (size_t i = 0; i < modified_scg_file_names.size(); ++i) {
          out_file << "    image " << modified_first_file_names[i] << " "
                   << modified_second_file_names[i] << ":" << endl;
          out_file << "        \"" << original_scg_file_paths[i] << "\""
                   << endl;
          out_file << "        yalign 0.0" << endl;
        }
        out_file.close();  // ���� ��Ʈ�� �ݱ�
        cout << "���� ���� �Ϸ�: " << scg_output_filename << endl;
      } else {
        cerr << "������ �� �� �����ϴ�: " << scg_output_filename << endl;
      }
    } catch (const fs::filesystem_error& e) {
      cerr << e.what() << endl;
    }
  } else {
    cout << "���丮�� �������� �ʽ��ϴ�." << endl;
    cout << "�������� ���ư��ϴ�." << endl;
  }
}

void BGDefine() {
  vector<string> original_bg_file_paths;
  vector<string> original_bg_file_names;
  vector<string> modified_bg_file_names;
  string bg_output_filename = "bg.rpy";
  ofstream out_file(bg_output_filename);

  fs::path bg_dir = "./renpy_example/game/images/BG/";  // ���� ��� ����
  if (fs::exists(bg_dir) &&
      fs::is_directory(bg_dir))  // �ش� ���丮 ���� ���� Ȯ��
  {
    try {
      // ���丮 ���� ��� ���ϰ� ���� ���丮�� ����� ��ȸ
      cout << "���� ��� ã����..." << endl;
      for (const auto& entry : fs::recursive_directory_iterator(bg_dir)) {
        if (fs::is_regular_file(entry)) {
          // ���� ��ο� ������ ���ڿ��� ��ȯ�Ͽ� ���Ϳ� �߰�.
          // filename()���� ���ϸ� ����, stem()���� Ȯ���� ����.
          original_bg_file_paths.push_back(entry.path().string());
          original_bg_file_names.push_back(
              entry.path().filename().stem().string());
        }
        // ���� ��� ���
        cout << entry.path() << endl;
      }
      cout << "���ϸ��� ������ �ν� ���� �������� ��ȯ��..." << endl;
      for (const auto& str : original_bg_file_names) {
        string modified = str;

        // ���� ���񿡼� �����̰� �ν� �Ұ����� ����� �������� ����ٷ� ����
        for (char& c : modified) {
          if (c == ' ')
            c = '_';
          else if (c == '-')
            c = '_';
        }
        // ����� ���ڿ��� �� ���Ϳ� �߰�
        modified_bg_file_names.push_back(modified);
      }
      // ������ ���ϸ� ���
      for (const auto& str : modified_bg_file_names) cout << str << endl;

      cout << "���� ������..." << endl;
      if (out_file.is_open()) {
        out_file << "init:" << endl;
        // ���� �迭�� ������ ���� �����ϱ�
        for (size_t i = 0; i < modified_bg_file_names.size(); ++i) {
          out_file << "    image " << modified_bg_file_names[i] << ":" << endl;
          out_file << "        \"" << original_bg_file_paths[i] << "\"" << endl;
          out_file << "        yalign 0.0" << endl;
        }
        out_file.close();  // ���� ��Ʈ�� �ݱ�
        cout << "���� ���� �Ϸ�: " << bg_output_filename << endl;
      } else {
        cerr << "������ �� �� �����ϴ�: " << bg_output_filename << endl;
      }
    } catch (const fs::filesystem_error& e) {
      cerr << e.what() << endl;
    }
  } else {
    cout << "���丮�� �������� �ʽ��ϴ�." << endl;
    cout << "�������� ���ư��ϴ�." << endl;
  }
}

// ����� ���ҽ��� �����ϴ� �κ��Դϴ�.
// � ���ҽ��� ��ũ��Ʈ���� ����ϴ�����, script.rpy������ ������ �� ��
// �ֽ��ϴ�.
void ScriptChecker() {
  string script_path = "./renpy_example/game/script.rpy";  // ���� ������ ���
  string bgm_string = "play music ";  // ã���� �ϴ� ���ڿ� ��ġ
  string sound_string = "play sound ";
  string bg_string = "scene ";
  string scg_string = "show ";
  set<string> used_bgm_string;  // �ߺ��� �����ϴ� set ���̺귯�� ���
  set<string> used_sound_string;
  set<string> used_bg_string;
  set<string> used_scg_string;

  ifstream file(script_path);

  if (!file.is_open()) {
    cerr << "������ �� �� �����ϴ�: " << script_path << endl;
    return;
  }

  // �� ���ҽ� ������ ó���� �ܺ� �Լ��� ó��
  string line;
  while (getline(file, line)) {
    ProcessLine(line, bgm_string, used_bgm_string);
    ProcessLine(line, sound_string, used_sound_string);
    ProcessLine(line, bg_string, used_bg_string);
    ProcessLineForSCG(line, scg_string, used_scg_string);
  }

  file.close();

  // ��� txt�� ��������
  PrintSet("BGM", used_bgm_string);
  PrintSet("SE", used_sound_string);
  PrintSet("BG", used_bg_string);
  PrintSet("SCG", used_scg_string);
  cout << "��� ���ҽ� �ĺ� �� txt Ȯ���ڷ� �������� �۾��� �Ϸ�Ǿ����ϴ�."
       << endl;

  // ���ҽ� �� �۾� ����
  cout << "���ǵ� ���ҽ��� ���� ���ҽ� �� �۾��� �����մϴ�." << endl;
  FindUnusedResources("BGM");
  FindUnusedResources("SE");
  FindUnusedResources("SCG");
  FindUnusedResources("BG");
  cout << "�� �۾��� �Ϸ�Ǿ����ϴ�. ������ ���� ���ҽ����� txtȮ���ڷ� "
          "��ϵǾ����ϴ�."
       << endl;
}

// �ܺ� �Լ� ó����. ù ��° ���� �������� �������� �߶�� ����.
void ProcessLine(const string& line, const string& search_string,
                 set<string>& result_set) {
  size_t pos = line.find(search_string);
  if (pos != string::npos) {
    string next_string = line.substr(pos + search_string.length());
    stringstream ss(next_string);
    string first_word;
    ss >> first_word;
    if (!first_word.empty()) {
      result_set.insert(first_word);
    }
  }
}

// SCG ���� ó���Լ�
void ProcessLineForSCG(const string& line, const string& search_string,
                       set<string>& result_set) {
  size_t pos = line.find(search_string);
  if (pos != string::npos) {
    string rest_of_line = line.substr(pos + search_string.length());
    size_t space_pos = rest_of_line.find(' ');
    if (space_pos != string::npos) {
      rest_of_line[space_pos] =
          '_';  // ù ��° ������ ����ٷ� �ٲ۴�(�ʼ�������)
      stringstream ss(rest_of_line);
      string modified_first_word;
      ss >> modified_first_word;
      if (!modified_first_word.empty()) {
        result_set.insert(modified_first_word);  // �迭�� �����Ѵ�
      }
    }
  }
}

// ��¿�
void PrintSet(const string& set_type, const set<string>& result_set) {
  ofstream out_file(set_type + "_used_resources.txt");  // ���� ����
  if (!out_file.is_open()) {
    cerr << "������ �� �� �����ϴ�: " << set_type + "_used_resources.txt"
         << endl;
    return;
  }

  // out_file << set_type << ":" << endl;
  for (const auto& value : result_set) {
    out_file << value << endl;
  }
  out_file.close();  // ���� ����

  cout << set_type << " ���ҽ� ����� ���Ϸ� ����Ǿ����ϴ�: "
       << set_type + "_used_resources.txt" << endl;
}

// �� �Լ��� ������ ������ ���� ���ҽ��� ã�� ���̴�.
// �ռ� txt�� ��µ� ���� ���ҽ� ������, ���ҽ� ���ǰ� ��� rpy������
// �����Ѵ�.
void FindUnusedResources(const string& resource_type) {
  set<string> defined_resources;  // �ߺ� ����!
  set<string> used_resources;
  string line;
  string string_finder;

  // ���� ������ ��� define audio���� ����ϱ⿡ ��Ʈ�����δ��� �̷��� �����.
  if (resource_type == "BGM" || resource_type == "SE") {
    string_finder = "    define audio.";
  }
  // �̹��� ������ ��� image���� ����ϱ⿡ ��Ʈ�����δ��� �̷��� �����.
  else if (resource_type == "SCG" || resource_type == "BG") {
    string_finder = "    image ";
  }

  // ���ǵ� rpy���� Ȯ��
  ifstream defined_file(resource_type + ".rpy");
  if (defined_file.is_open()) {
    while (getline(defined_file, line)) {
      size_t pos = line.find(string_finder);
      if (pos != string::npos) {
        size_t start = pos + string_finder.length();
        size_t end = line.find(" ", start);
        string resource_name =
            line.substr(start, end - start);  // �κ� ���ڿ� ����
        defined_resources.insert(resource_name);
      }
    }
    defined_file.close();
  }

  // ����� ���ҽ� ��� txt������ Ȯ��
  ifstream used_file(resource_type + "_used_resources.txt");
  if (used_file.is_open()) {
    while (getline(used_file, line)) {
      used_resources.insert(line);
    }
    used_file.close();
  }

  // ������ ���� ���ҽ� ����� ����
  ofstream out_file(resource_type + "_unused_resources.txt");
  if (out_file.is_open()) {
    for (const auto& resource : defined_resources) {
      if (used_resources.find(resource) == used_resources.end()) {
        out_file << resource << endl;
      }
    }
    out_file.close();
  }
}