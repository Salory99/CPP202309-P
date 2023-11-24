
// 2023.11.25기준 주의사항입니다. 반드시 읽어주세요.
// 1. 본 파일은 filesystem라이브러리의 사용으로 C++17 이상의 조건에서 구동 가능합니다.
// 2. 현재 파일의 경로로는 렌파이에서 구동할 수 없는 경로가 만들어집니다.
//    현재는 단지 제출 및 구동 시연을 위한 것일 뿐이며,
//    실사용 시에는 상대 경로의 위치 기준점이 game폴더 내부가 되어야 합니다.
//    따라서 실사용시에는 반드시 game폴더 내부에서 구동해야만 합니다.
// 3. SCG부분에서 중간에 언더바가 없는 파일이 있으면 에러를 뱉습니다.
//    이는 필요에 따라 의도된 사항이며, 이후에 언더바가 없다면 구동이 되지 않거나,
//    언더바가 없는 파일은 무시하는 방식으로 개선할 예정입니다.


#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <fstream>

using namespace std;
namespace fs = std::filesystem;

bool SubChoice(int subchoice);
void DefineAll();
void BGMDefine();
void SEDefine();
void SCGDefine();
void BGDefine();

int main()
{
	int choice = 0;
	int subchoice = 0;
	cout << "렌파이 전용 리소스 관리 모듈입니다." << endl;
	cout << "해야 할 작업의 번호를 입력해 주세요." << endl;

	while (true)
	{
		cout << "1. 전체 재정의" << endl;
		cout << "2. 부분 재정의" << endl;
		cout << "3. 사용된 리소스 검출" << endl;
		cin >> choice;

		if (choice == 1)
		{
			cout << "전체 재정의 작업을 수행합니다." << endl;
			DefineAll();
			break;
		}
		else if (choice == 2)
		{
			cout << "부분 재정의 작업을 수행합니다." << endl;
			cout << "원하는 작업의 번호를 입력해 주세요." << endl;
			while (true)
			{
				bool subchoice_wrong_input = false;

				cout << "1. BGM 재정의" << endl;
				cout << "2. SE 재정의" << endl;
				cout << "3. SCG 재정의" << endl;
				cout << "4. BG 재정의" << endl;
				cin >> subchoice;
				subchoice_wrong_input = SubChoice(subchoice);
				if (subchoice_wrong_input == true)
				{
					continue;
				}
				break;
			}
			break;
		}
		else if (choice == 3)
		{
			cout << "현재 지원하지 않는 기능입니다." << endl;
			continue;
		}
		else
		{
			cout << "잘못된 입력입니다. 다시 입력해 주세요." << endl;
			continue;
		}
	}
	return 0;
}


bool SubChoice(int subchoice)
{
	if (subchoice == 1)
	{
		cout << "BGM 재정의를 시작합니다." << endl;
		BGMDefine();
		return false;
	}
	else if (subchoice == 2)
	{
		cout << "SE 재정의를 시작합니다." << endl;
		SEDefine();
		return false;
	}
	else if (subchoice == 3)
	{
		cout << "SCG 재정의를 시작합니다." << endl;
		SCGDefine();
		return false;
	}
	else if (subchoice == 4)
	{
		cout << "BG 재정의를 시작합니다." << endl;
		BGDefine();
		return false;
	}
	else
	{
		cout << "잘못된 입력입니다." << endl;
		return true;
	}
}

void DefineAll()
{
	BGMDefine();
	SEDefine();
	SCGDefine();
	BGDefine();
}

void BGMDefine()
{
	vector<string> original_bgm_file_paths;
	vector<string> original_bgm_file_names;
	vector<string> modified_bgm_file_names;
	string bgm_output_filename = "bgm.rpy";
	ofstream out_file(bgm_output_filename);

	fs::path bgm_dir = "./renpy_example/game/audio/BGM/"; // 문서 경로 지정
	if (fs::exists(bgm_dir)&& fs::is_directory(bgm_dir)) // 해당 디렉토리 존재 여부 확인
	{
		try {
			// 디렉토리 내의 모든 파일과 하위 디렉토리를 재귀적 순회
			cout << "원본 경로 찾는중..." << endl;
			for (const auto& entry : fs::recursive_directory_iterator(bgm_dir)) {
				if (fs::is_regular_file(entry)) {
					// 파일 경로와 제목을 문자열로 변환하여 벡터에 추가.
					// filename()으로 파일명 추출, stem()으로 확장자 제거.
					original_bgm_file_paths.push_back(entry.path().string());
					original_bgm_file_names.push_back(entry.path().filename().stem().string());
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
			for (const auto& str : modified_bgm_file_names)
				cout << str << endl;

			cout << "파일 저장중..." << endl;
			if (out_file.is_open()) {
				out_file << "init:" << endl;
				// 벡터 배열의 내용을 토대로 정의하기
				for (size_t i = 0; i < modified_bgm_file_names.size(); ++i) {
					out_file << "    define audio." << modified_bgm_file_names[i] << " = ";
					out_file << "\"" << original_bgm_file_paths[i] << "\"" << endl;
				}
				out_file.close(); // 파일 스트림 닫기
				cout << "파일 저장 완료: " << bgm_output_filename << endl;
			}
			else {
				cerr << "파일을 열 수 없습니다: " << bgm_output_filename << endl;
			}			
		}
		catch (const fs::filesystem_error& e) {
			cerr << e.what() << endl;
		}
	}
	else
	{
		cout << "디렉토리가 존재하지 않습니다." << endl;
		cout << "메인으로 돌아갑니다." << endl;
	}
}


void SEDefine()
{
	vector<string> original_se_file_paths;
	vector<string> original_se_file_names;
	vector<string> modified_se_file_names;
	string se_output_filename = "se.rpy";
	ofstream out_file(se_output_filename);

	fs::path se_dir = "./renpy_example/game/audio/SE/"; // 문서 경로 지정
	if (fs::exists(se_dir) && fs::is_directory(se_dir)) // 해당 디렉토리 존재 여부 확인
	{
		try {
			// 디렉토리 내의 모든 파일과 하위 디렉토리를 재귀적 순회
			cout << "원본 경로 찾는중..." << endl;
			for (const auto& entry : fs::recursive_directory_iterator(se_dir)) {
				if (fs::is_regular_file(entry)) {
					// 파일 경로와 제목을 문자열로 변환하여 벡터에 추가.
					// filename()으로 파일명 추출, stem()으로 확장자 제거.
					original_se_file_paths.push_back(entry.path().string());
					original_se_file_names.push_back(entry.path().filename().stem().string());
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
			for (const auto& str : modified_se_file_names)
				cout << str << endl;

			cout << "파일 저장중..." << endl;
			if (out_file.is_open()) {
				out_file << "init:" << endl;
				// 벡터 배열의 내용을 토대로 정의하기
				for (size_t i = 0; i < modified_se_file_names.size(); ++i) {
					out_file << "    define audio." << modified_se_file_names[i] << " = ";
					out_file << "\"" << original_se_file_paths[i] << "\"" << endl;
				}
				out_file.close(); // 파일 스트림 닫기
				cout << "파일 저장 완료: " << se_output_filename << endl;
			}
			else {
				cerr << "파일을 열 수 없습니다: " << se_output_filename << endl;
			}
		}
		catch (const fs::filesystem_error& e) {
			cerr << e.what() << endl;
		}
	}
	else
	{
		cout << "디렉토리가 존재하지 않습니다." << endl;
		cout << "메인으로 돌아갑니다." << endl;
	}
}

// SCG는 리소스를 저장할 때 반드시 파일명에 언더바가 한번씩 들어가야만 한다.
// 이는 렌파이 기능의 원활한 수행을 위해 어쩔 수 없다.
// 현재는 언더바가 없으면 에러를 뱉어낸다.
// 완성 때 만일 언더바가 없으면 작동되지 않도록 조치도 할 예정이다.
void SCGDefine()
{
	vector<string> original_scg_file_paths;
	vector<string> original_scg_file_names;
	vector<string> modified_scg_file_names;
	vector<string> modified_first_file_names;
	vector<string> modified_second_file_names;
	string scg_output_filename = "scg.rpy";
	ofstream out_file(scg_output_filename);

	fs::path scg_dir = "./renpy_example/game/images/SCG/"; // 문서 경로 지정
	if (fs::exists(scg_dir) && fs::is_directory(scg_dir)) // 해당 디렉토리 존재 여부 확인
	{
		try {
			// 디렉토리 내의 모든 파일과 하위 디렉토리를 재귀적 순회
			cout << "원본 경로 찾는중..." << endl;
			for (const auto& entry : fs::recursive_directory_iterator(scg_dir)) {
				if (fs::is_regular_file(entry)) {
					// 파일 경로와 제목을 문자열로 변환하여 벡터에 추가.
					// filename()으로 파일명 추출, stem()으로 확장자 제거.
					original_scg_file_paths.push_back(entry.path().string());
					original_scg_file_names.push_back(entry.path().filename().stem().string());
				}
				// 파일 경로 출력
				cout << entry.path() << endl;
			}
			cout << "파일명을 렌파이 인식 가능 버전으로 전환중..." << endl;
			for (const auto& str : original_scg_file_names) {
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
				size_t underbar_cut = str.find("_"); // 첫 번째 언더바의 위치를 찾음
				if (underbar_cut != std::string::npos) {
					modified_first_file_names.push_back(str.substr(0, underbar_cut)); // 첫 번째 부분
					modified_second_file_names.push_back(str.substr(underbar_cut + 1)); // 두 번째 부분
				}
			}

			// 수정된 파일명 출력
			for (const auto& str : modified_scg_file_names)
				cout << str << endl;

			cout << "파일 저장중..." << endl;
			if (out_file.is_open()) {
				out_file << "init:" << endl;
				// 벡터 배열의 내용을 토대로 정의하기
				for (size_t i = 0; i < modified_scg_file_names.size(); ++i) {
					out_file << "    image " << modified_first_file_names[i] << " " << modified_second_file_names[i] << ":" << endl;
					out_file << "        \"" << original_scg_file_paths[i] << "\"" << endl;
					out_file << "        yalign 0.0" << endl;
				}
				out_file.close(); // 파일 스트림 닫기
				cout << "파일 저장 완료: " << scg_output_filename << endl;
			}
			else {
				cerr << "파일을 열 수 없습니다: " << scg_output_filename << endl;
			}
		}
		catch (const fs::filesystem_error& e) {
			cerr << e.what() << endl;
		}
	}
	else
	{
		cout << "디렉토리가 존재하지 않습니다." << endl;
		cout << "메인으로 돌아갑니다." << endl;
	}
}

void BGDefine()
{
	vector<string> original_bg_file_paths;
	vector<string> original_bg_file_names;
	vector<string> modified_bg_file_names;
	string bg_output_filename = "bg.rpy";
	ofstream out_file(bg_output_filename);

	fs::path bg_dir = "./renpy_example/game/images/BG/"; // 문서 경로 지정
	if (fs::exists(bg_dir) && fs::is_directory(bg_dir)) // 해당 디렉토리 존재 여부 확인
	{
		try {
			// 디렉토리 내의 모든 파일과 하위 디렉토리를 재귀적 순회
			cout << "원본 경로 찾는중..." << endl;
			for (const auto& entry : fs::recursive_directory_iterator(bg_dir)) {
				if (fs::is_regular_file(entry)) {
					// 파일 경로와 제목을 문자열로 변환하여 벡터에 추가.
					// filename()으로 파일명 추출, stem()으로 확장자 제거.
					original_bg_file_paths.push_back(entry.path().string());
					original_bg_file_names.push_back(entry.path().filename().stem().string());
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
			for (const auto& str : modified_bg_file_names)
				cout << str << endl;

			cout << "파일 저장중..." << endl;
			if (out_file.is_open()) {
				out_file << "init:" << endl;
				// 벡터 배열의 내용을 토대로 정의하기
				for (size_t i = 0; i < modified_bg_file_names.size(); ++i) {
					out_file << "    image " << modified_bg_file_names[i] << ":" << endl;
					out_file << "        \"" << original_bg_file_paths[i] << "\"" << endl;
					out_file << "        yalign 0.0" << endl;
				}
				out_file.close(); // 파일 스트림 닫기
				cout << "파일 저장 완료: " << bg_output_filename << endl;
			}
			else {
				cerr << "파일을 열 수 없습니다: " << bg_output_filename << endl;
			}
		}
		catch (const fs::filesystem_error& e) {
			cerr << e.what() << endl;
		}
	}
	else
	{
		cout << "디렉토리가 존재하지 않습니다." << endl;
		cout << "메인으로 돌아갑니다." << endl;
	}
}






