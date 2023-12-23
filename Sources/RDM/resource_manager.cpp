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

  fs::path bgm_dir = "./renpy_example/game/audio/BGM/";  // 문서 경로 지정
  if (fs::exists(bgm_dir) &&
      fs::is_directory(bgm_dir))  // 해당 디렉토리 존재 여부 확인
  {
    try {
      // 디렉토리 내의 모든 파일과 하위 디렉토리를 재귀적 순회
      cout << "원본 경로 찾는중..." << endl;
      for (const auto& entry : fs::recursive_directory_iterator(bgm_dir)) {
        if (fs::is_regular_file(entry)) {
          // 파일 경로와 제목을 문자열로 변환하여 벡터에 추가.
          // filename()으로 파일명 추출, stem()으로 확장자 제거.
          original_bgm_file_paths.push_back(entry.path().string());
          original_bgm_file_names.push_back(
              entry.path().filename().stem().string());
        }
        // 파일 경로 출력
        cout << entry.path() << endl;
      }
      cout << "파일명을 렌파이 인식 가능 버전으로 전환중..." << endl;
      for (const auto& str : original_bgm_file_names) {
        string modified = str;

        // 파일 제목에서 렌파이가 인식 불가능한 공백과 하이픈을 언더바로 변경
        for (char& c : modified) {
          if (c == ' ')
            c = '_';
          else if (c == '-')
            c = '_';
        }
        // 변경된 문자열을 새 벡터에 추가
        modified_bgm_file_names.push_back(modified);
      }
      // 수정된 파일명 출력
      for (const auto& str : modified_bgm_file_names) cout << str << endl;

      cout << "파일 저장중..." << endl;
      if (out_file.is_open()) {
        out_file << "init:" << endl;
        // 벡터 배열의 내용을 토대로 정의하기
        for (size_t i = 0; i < modified_bgm_file_names.size(); ++i) {
          out_file << "    define audio." << modified_bgm_file_names[i]
                   << " = ";
          out_file << "\"" << original_bgm_file_paths[i] << "\"" << endl;
        }
        out_file.close();  // 파일 스트림 닫기
        cout << "파일 저장 완료: " << bgm_output_filename << endl;
      } else {
        cerr << "파일을 열 수 없습니다: " << bgm_output_filename << endl;
      }
    } catch (const fs::filesystem_error& e) {
      cerr << e.what() << endl;
    }
  } else {
    cout << "디렉토리가 존재하지 않습니다." << endl;
    cout << "메인으로 돌아갑니다." << endl;
  }
}

void SEDefine() {
  vector<string> original_se_file_paths;
  vector<string> original_se_file_names;
  vector<string> modified_se_file_names;
  string se_output_filename = "se.rpy";
  ofstream out_file(se_output_filename);

  fs::path se_dir = "./renpy_example/game/audio/SE/";  // 문서 경로 지정
  if (fs::exists(se_dir) &&
      fs::is_directory(se_dir))  // 해당 디렉토리 존재 여부 확인
  {
    try {
      // 디렉토리 내의 모든 파일과 하위 디렉토리를 재귀적 순회
      cout << "원본 경로 찾는중..." << endl;
      for (const auto& entry : fs::recursive_directory_iterator(se_dir)) {
        if (fs::is_regular_file(entry)) {
          // 파일 경로와 제목을 문자열로 변환하여 벡터에 추가.
          // filename()으로 파일명 추출, stem()으로 확장자 제거.
          original_se_file_paths.push_back(entry.path().string());
          original_se_file_names.push_back(
              entry.path().filename().stem().string());
        }
        // 파일 경로 출력
        cout << entry.path() << endl;
      }
      cout << "파일명을 렌파이 인식 가능 버전으로 전환중..." << endl;
      for (const auto& str : original_se_file_names) {
        string modified = str;

        // 파일 제목에서 렌파이가 인식 불가능한 공백과 하이픈을 언더바로 변경
        for (char& c : modified) {
          if (c == ' ')
            c = '_';
          else if (c == '-')
            c = '_';
        }
        // 변경된 문자열을 새 벡터에 추가
        modified_se_file_names.push_back(modified);
      }
      // 수정된 파일명 출력
      for (const auto& str : modified_se_file_names) cout << str << endl;

      cout << "파일 저장중..." << endl;
      if (out_file.is_open()) {
        out_file << "init:" << endl;
        // 벡터 배열의 내용을 토대로 정의하기
        for (size_t i = 0; i < modified_se_file_names.size(); ++i) {
          out_file << "    define audio." << modified_se_file_names[i] << " = ";
          out_file << "\"" << original_se_file_paths[i] << "\"" << endl;
        }
        out_file.close();  // 파일 스트림 닫기
        cout << "파일 저장 완료: " << se_output_filename << endl;
      } else {
        cerr << "파일을 열 수 없습니다: " << se_output_filename << endl;
      }
    } catch (const fs::filesystem_error& e) {
      cerr << e.what() << endl;
    }
  } else {
    cout << "디렉토리가 존재하지 않습니다." << endl;
    cout << "메인으로 돌아갑니다." << endl;
  }
}

// SCG는 리소스를 저장할 때 반드시 파일명에 언더바가 한번씩 들어가야만 한다.
// 이는 렌파이 기능의 원활한 수행을 위해 어쩔 수 없다.
// 언더바가 없는 파일은 배열 포함에 제외되도록 처리되었다.
void SCGDefine() {
  vector<string> original_scg_file_paths;
  vector<string> original_scg_file_names;
  vector<string> modified_scg_file_names;
  vector<string> modified_first_file_names;
  vector<string> modified_second_file_names;
  string scg_output_filename = "scg.rpy";
  ofstream out_file(scg_output_filename);

  fs::path scg_dir = "./renpy_example/game/images/SCG/";  // 문서 경로 지정
  if (fs::exists(scg_dir) &&
      fs::is_directory(scg_dir))  // 해당 디렉토리 존재 여부 확인
  {
    try {
      // 디렉토리 내의 모든 파일과 하위 디렉토리를 재귀적 순회
      cout << "원본 경로 찾는중..." << endl;
      for (const auto& entry : fs::recursive_directory_iterator(scg_dir)) {
        if (fs::is_regular_file(entry)) {
          // 파일 경로와 제목을 문자열로 변환하여 벡터에 추가.
          // filename()으로 파일명 추출, stem()으로 확장자 제거.
          original_scg_file_paths.push_back(entry.path().string());
          original_scg_file_names.push_back(
              entry.path().filename().stem().string());
        }
        // 파일 경로 출력
        cout << entry.path() << endl;
      }
      cout << "파일명을 렌파이 인식 가능 버전으로 전환중..." << endl;
      for (const auto& str : original_scg_file_names) {
        // 언더바가 없는 파일은 건너뜀
        if (str.find('_') == std::string::npos) {
          cout << str << " - 언더바가 없어 처리되지 않는 파일입니다." << endl;
          continue;
        }
        string modified = str;

        // 파일 제목에서 렌파이가 인식 불가능한 공백과 하이픈을 언더바로 변경
        for (char& c : modified) {
          if (c == ' ')
            c = '_';
          else if (c == '-')
            c = '_';
        }
        // 변경된 문자열을 새 벡터에 추가
        modified_scg_file_names.push_back(modified);
      }

      // 변경된 파일 제목 문자열을 첫 번째 언더바를 기준으로 절단
      for (const auto& str : modified_scg_file_names) {
        size_t underbar_cut = str.find("_");  // 첫 번째 언더바의 위치를 찾음
        if (underbar_cut != std::string::npos) {
          modified_first_file_names.push_back(
              str.substr(0, underbar_cut));  // 첫 번째 부분
          modified_second_file_names.push_back(
              str.substr(underbar_cut + 1));  // 두 번째 부분
        }
      }

      // 수정된 파일명 출력
      for (const auto& str : modified_scg_file_names) cout << str << endl;

      cout << "파일 저장중..." << endl;
      if (out_file.is_open()) {
        out_file << "init:" << endl;
        // 벡터 배열의 내용을 토대로 정의하기
        for (size_t i = 0; i < modified_scg_file_names.size(); ++i) {
          out_file << "    image " << modified_first_file_names[i] << " "
                   << modified_second_file_names[i] << ":" << endl;
          out_file << "        \"" << original_scg_file_paths[i] << "\""
                   << endl;
          out_file << "        yalign 0.0" << endl;
        }
        out_file.close();  // 파일 스트림 닫기
        cout << "파일 저장 완료: " << scg_output_filename << endl;
      } else {
        cerr << "파일을 열 수 없습니다: " << scg_output_filename << endl;
      }
    } catch (const fs::filesystem_error& e) {
      cerr << e.what() << endl;
    }
  } else {
    cout << "디렉토리가 존재하지 않습니다." << endl;
    cout << "메인으로 돌아갑니다." << endl;
  }
}

void BGDefine() {
  vector<string> original_bg_file_paths;
  vector<string> original_bg_file_names;
  vector<string> modified_bg_file_names;
  string bg_output_filename = "bg.rpy";
  ofstream out_file(bg_output_filename);

  fs::path bg_dir = "./renpy_example/game/images/BG/";  // 문서 경로 지정
  if (fs::exists(bg_dir) &&
      fs::is_directory(bg_dir))  // 해당 디렉토리 존재 여부 확인
  {
    try {
      // 디렉토리 내의 모든 파일과 하위 디렉토리를 재귀적 순회
      cout << "원본 경로 찾는중..." << endl;
      for (const auto& entry : fs::recursive_directory_iterator(bg_dir)) {
        if (fs::is_regular_file(entry)) {
          // 파일 경로와 제목을 문자열로 변환하여 벡터에 추가.
          // filename()으로 파일명 추출, stem()으로 확장자 제거.
          original_bg_file_paths.push_back(entry.path().string());
          original_bg_file_names.push_back(
              entry.path().filename().stem().string());
        }
        // 파일 경로 출력
        cout << entry.path() << endl;
      }
      cout << "파일명을 렌파이 인식 가능 버전으로 전환중..." << endl;
      for (const auto& str : original_bg_file_names) {
        string modified = str;

        // 파일 제목에서 렌파이가 인식 불가능한 공백과 하이픈을 언더바로 변경
        for (char& c : modified) {
          if (c == ' ')
            c = '_';
          else if (c == '-')
            c = '_';
        }
        // 변경된 문자열을 새 벡터에 추가
        modified_bg_file_names.push_back(modified);
      }
      // 수정된 파일명 출력
      for (const auto& str : modified_bg_file_names) cout << str << endl;

      cout << "파일 저장중..." << endl;
      if (out_file.is_open()) {
        out_file << "init:" << endl;
        // 벡터 배열의 내용을 토대로 정의하기
        for (size_t i = 0; i < modified_bg_file_names.size(); ++i) {
          out_file << "    image " << modified_bg_file_names[i] << ":" << endl;
          out_file << "        \"" << original_bg_file_paths[i] << "\"" << endl;
          out_file << "        yalign 0.0" << endl;
        }
        out_file.close();  // 파일 스트림 닫기
        cout << "파일 저장 완료: " << bg_output_filename << endl;
      } else {
        cerr << "파일을 열 수 없습니다: " << bg_output_filename << endl;
      }
    } catch (const fs::filesystem_error& e) {
      cerr << e.what() << endl;
    }
  } else {
    cout << "디렉토리가 존재하지 않습니다." << endl;
    cout << "메인으로 돌아갑니다." << endl;
  }
}

// 사용한 리소스를 검출하는 부분입니다.
// 어떤 리소스를 스크립트에서 사용하는지는, script.rpy파일을 읽으면 알 수
// 있습니다.
void ScriptChecker() {
  string script_path = "./renpy_example/game/script.rpy";  // 읽을 파일의 경로
  string bgm_string = "play music ";  // 찾고자 하는 문자열 위치
  string sound_string = "play sound ";
  string bg_string = "scene ";
  string scg_string = "show ";
  set<string> used_bgm_string;  // 중복을 방지하는 set 라이브러리 사용
  set<string> used_sound_string;
  set<string> used_bg_string;
  set<string> used_scg_string;

  ifstream file(script_path);

  if (!file.is_open()) {
    cerr << "파일을 열 수 없습니다: " << script_path << endl;
    return;
  }

  // 각 리소스 종류별 처리는 외부 함수로 처리
  string line;
  while (getline(file, line)) {
    ProcessLine(line, bgm_string, used_bgm_string);
    ProcessLine(line, sound_string, used_sound_string);
    ProcessLine(line, bg_string, used_bg_string);
    ProcessLineForSCG(line, scg_string, used_scg_string);
  }

  file.close();

  // 결과 txt로 내보내기
  PrintSet("BGM", used_bgm_string);
  PrintSet("SE", used_sound_string);
  PrintSet("BG", used_bg_string);
  PrintSet("SCG", used_scg_string);
  cout << "사용 리소스 식별 및 txt 확장자로 내보내기 작업이 완료되었습니다."
       << endl;

  // 리소스 비교 작업 수행
  cout << "정의된 리소스와 사용된 리소스 비교 작업을 시작합니다." << endl;
  FindUnusedResources("BGM");
  FindUnusedResources("SE");
  FindUnusedResources("SCG");
  FindUnusedResources("BG");
  cout << "비교 작업이 완료되었습니다. 사용되지 않은 리소스들이 txt확장자로 "
          "기록되었습니다."
       << endl;
}

// 외부 함수 처리용. 첫 번째 공백 기준으로 오른쪽은 잘라다 버림.
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

// SCG 전용 처리함수
void ProcessLineForSCG(const string& line, const string& search_string,
                       set<string>& result_set) {
  size_t pos = line.find(search_string);
  if (pos != string::npos) {
    string rest_of_line = line.substr(pos + search_string.length());
    size_t space_pos = rest_of_line.find(' ');
    if (space_pos != string::npos) {
      rest_of_line[space_pos] =
          '_';  // 첫 번째 공백을 언더바로 바꾼다(필수과정임)
      stringstream ss(rest_of_line);
      string modified_first_word;
      ss >> modified_first_word;
      if (!modified_first_word.empty()) {
        result_set.insert(modified_first_word);  // 배열에 삽입한다
      }
    }
  }
}

// 출력용
void PrintSet(const string& set_type, const set<string>& result_set) {
  ofstream out_file(set_type + "_used_resources.txt");  // 파일 생성
  if (!out_file.is_open()) {
    cerr << "파일을 열 수 없습니다: " << set_type + "_used_resources.txt"
         << endl;
    return;
  }

  // out_file << set_type << ":" << endl;
  for (const auto& value : result_set) {
    out_file << value << endl;
  }
  out_file.close();  // 파일 닫음

  cout << set_type << " 리소스 목록이 파일로 저장되었습니다: "
       << set_type + "_used_resources.txt" << endl;
}

// 이 함수의 역할은 사용되지 않은 리소스를 찾는 것이다.
// 앞서 txt로 출력된 사용된 리소스 내역과, 리소스 정의가 담긴 rpy파일을
// 대조한다.
void FindUnusedResources(const string& resource_type) {
  set<string> defined_resources;  // 중복 방지!
  set<string> used_resources;
  string line;
  string string_finder;

  // 음원 파일의 경우 define audio문을 사용하기에 스트링파인더를 이렇게 맞춘다.
  if (resource_type == "BGM" || resource_type == "SE") {
    string_finder = "    define audio.";
  }
  // 이미지 파일의 경우 image문을 사용하기에 스트링파인더를 이렇게 맞춘다.
  else if (resource_type == "SCG" || resource_type == "BG") {
    string_finder = "    image ";
  }

  // 정의된 rpy파일 확인
  ifstream defined_file(resource_type + ".rpy");
  if (defined_file.is_open()) {
    while (getline(defined_file, line)) {
      size_t pos = line.find(string_finder);
      if (pos != string::npos) {
        size_t start = pos + string_finder.length();
        size_t end = line.find(" ", start);
        string resource_name =
            line.substr(start, end - start);  // 부분 문자열 추출
        defined_resources.insert(resource_name);
      }
    }
    defined_file.close();
  }

  // 사용한 리소스 명단 txt파일을 확인
  ifstream used_file(resource_type + "_used_resources.txt");
  if (used_file.is_open()) {
    while (getline(used_file, line)) {
      used_resources.insert(line);
    }
    used_file.close();
  }

  // 사용되지 않은 리소스 목록을 저장
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