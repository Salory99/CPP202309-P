
// 2023.11.25���� ���ǻ����Դϴ�. �ݵ�� �о��ּ���.
// 1. �� ������ filesystem���̺귯���� ������� C++17 �̻��� ���ǿ��� ���� �����մϴ�.
// 2. ���� ������ ��ηδ� �����̿��� ������ �� ���� ��ΰ� ��������ϴ�.
//    ����� ���� ���� �� ���� �ÿ��� ���� ���� ���̸�,
//    �ǻ�� �ÿ��� ��� ����� ��ġ �������� game���� ���ΰ� �Ǿ�� �մϴ�.
//    ���� �ǻ��ÿ��� �ݵ�� game���� ���ο��� �����ؾ߸� �մϴ�.
// 3. SCG�κп��� �߰��� ����ٰ� ���� ������ ������ ������ ����ϴ�.
//    �̴� �ʿ信 ���� �ǵ��� �����̸�, ���Ŀ� ����ٰ� ���ٸ� ������ ���� �ʰų�,
//    ����ٰ� ���� ������ �����ϴ� ������� ������ �����Դϴ�.


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
	cout << "������ ���� ���ҽ� ���� ����Դϴ�." << endl;
	cout << "�ؾ� �� �۾��� ��ȣ�� �Է��� �ּ���." << endl;

	while (true)
	{
		cout << "1. ��ü ������" << endl;
		cout << "2. �κ� ������" << endl;
		cout << "3. ���� ���ҽ� ����" << endl;
		cin >> choice;

		if (choice == 1)
		{
			cout << "��ü ������ �۾��� �����մϴ�." << endl;
			DefineAll();
			break;
		}
		else if (choice == 2)
		{
			cout << "�κ� ������ �۾��� �����մϴ�." << endl;
			cout << "���ϴ� �۾��� ��ȣ�� �Է��� �ּ���." << endl;
			while (true)
			{
				bool subchoice_wrong_input = false;

				cout << "1. BGM ������" << endl;
				cout << "2. SE ������" << endl;
				cout << "3. SCG ������" << endl;
				cout << "4. BG ������" << endl;
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
			cout << "���� �������� �ʴ� ����Դϴ�." << endl;
			continue;
		}
		else
		{
			cout << "�߸��� �Է��Դϴ�. �ٽ� �Է��� �ּ���." << endl;
			continue;
		}
	}
	return 0;
}


bool SubChoice(int subchoice)
{
	if (subchoice == 1)
	{
		cout << "BGM �����Ǹ� �����մϴ�." << endl;
		BGMDefine();
		return false;
	}
	else if (subchoice == 2)
	{
		cout << "SE �����Ǹ� �����մϴ�." << endl;
		SEDefine();
		return false;
	}
	else if (subchoice == 3)
	{
		cout << "SCG �����Ǹ� �����մϴ�." << endl;
		SCGDefine();
		return false;
	}
	else if (subchoice == 4)
	{
		cout << "BG �����Ǹ� �����մϴ�." << endl;
		BGDefine();
		return false;
	}
	else
	{
		cout << "�߸��� �Է��Դϴ�." << endl;
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

	fs::path bgm_dir = "./renpy_example/game/audio/BGM/"; // ���� ��� ����
	if (fs::exists(bgm_dir)&& fs::is_directory(bgm_dir)) // �ش� ���丮 ���� ���� Ȯ��
	{
		try {
			// ���丮 ���� ��� ���ϰ� ���� ���丮�� ����� ��ȸ
			cout << "���� ��� ã����..." << endl;
			for (const auto& entry : fs::recursive_directory_iterator(bgm_dir)) {
				if (fs::is_regular_file(entry)) {
					// ���� ��ο� ������ ���ڿ��� ��ȯ�Ͽ� ���Ϳ� �߰�.
					// filename()���� ���ϸ� ����, stem()���� Ȯ���� ����.
					original_bgm_file_paths.push_back(entry.path().string());
					original_bgm_file_names.push_back(entry.path().filename().stem().string());
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
			for (const auto& str : modified_bgm_file_names)
				cout << str << endl;

			cout << "���� ������..." << endl;
			if (out_file.is_open()) {
				out_file << "init:" << endl;
				// ���� �迭�� ������ ���� �����ϱ�
				for (size_t i = 0; i < modified_bgm_file_names.size(); ++i) {
					out_file << "    define audio." << modified_bgm_file_names[i] << " = ";
					out_file << "\"" << original_bgm_file_paths[i] << "\"" << endl;
				}
				out_file.close(); // ���� ��Ʈ�� �ݱ�
				cout << "���� ���� �Ϸ�: " << bgm_output_filename << endl;
			}
			else {
				cerr << "������ �� �� �����ϴ�: " << bgm_output_filename << endl;
			}			
		}
		catch (const fs::filesystem_error& e) {
			cerr << e.what() << endl;
		}
	}
	else
	{
		cout << "���丮�� �������� �ʽ��ϴ�." << endl;
		cout << "�������� ���ư��ϴ�." << endl;
	}
}


void SEDefine()
{
	vector<string> original_se_file_paths;
	vector<string> original_se_file_names;
	vector<string> modified_se_file_names;
	string se_output_filename = "se.rpy";
	ofstream out_file(se_output_filename);

	fs::path se_dir = "./renpy_example/game/audio/SE/"; // ���� ��� ����
	if (fs::exists(se_dir) && fs::is_directory(se_dir)) // �ش� ���丮 ���� ���� Ȯ��
	{
		try {
			// ���丮 ���� ��� ���ϰ� ���� ���丮�� ����� ��ȸ
			cout << "���� ��� ã����..." << endl;
			for (const auto& entry : fs::recursive_directory_iterator(se_dir)) {
				if (fs::is_regular_file(entry)) {
					// ���� ��ο� ������ ���ڿ��� ��ȯ�Ͽ� ���Ϳ� �߰�.
					// filename()���� ���ϸ� ����, stem()���� Ȯ���� ����.
					original_se_file_paths.push_back(entry.path().string());
					original_se_file_names.push_back(entry.path().filename().stem().string());
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
			for (const auto& str : modified_se_file_names)
				cout << str << endl;

			cout << "���� ������..." << endl;
			if (out_file.is_open()) {
				out_file << "init:" << endl;
				// ���� �迭�� ������ ���� �����ϱ�
				for (size_t i = 0; i < modified_se_file_names.size(); ++i) {
					out_file << "    define audio." << modified_se_file_names[i] << " = ";
					out_file << "\"" << original_se_file_paths[i] << "\"" << endl;
				}
				out_file.close(); // ���� ��Ʈ�� �ݱ�
				cout << "���� ���� �Ϸ�: " << se_output_filename << endl;
			}
			else {
				cerr << "������ �� �� �����ϴ�: " << se_output_filename << endl;
			}
		}
		catch (const fs::filesystem_error& e) {
			cerr << e.what() << endl;
		}
	}
	else
	{
		cout << "���丮�� �������� �ʽ��ϴ�." << endl;
		cout << "�������� ���ư��ϴ�." << endl;
	}
}

// SCG�� ���ҽ��� ������ �� �ݵ�� ���ϸ� ����ٰ� �ѹ��� ���߸� �Ѵ�.
// �̴� ������ ����� ��Ȱ�� ������ ���� ��¿ �� ����.
// ����� ����ٰ� ������ ������ ����.
// �ϼ� �� ���� ����ٰ� ������ �۵����� �ʵ��� ��ġ�� �� �����̴�.
void SCGDefine()
{
	vector<string> original_scg_file_paths;
	vector<string> original_scg_file_names;
	vector<string> modified_scg_file_names;
	vector<string> modified_first_file_names;
	vector<string> modified_second_file_names;
	string scg_output_filename = "scg.rpy";
	ofstream out_file(scg_output_filename);

	fs::path scg_dir = "./renpy_example/game/images/SCG/"; // ���� ��� ����
	if (fs::exists(scg_dir) && fs::is_directory(scg_dir)) // �ش� ���丮 ���� ���� Ȯ��
	{
		try {
			// ���丮 ���� ��� ���ϰ� ���� ���丮�� ����� ��ȸ
			cout << "���� ��� ã����..." << endl;
			for (const auto& entry : fs::recursive_directory_iterator(scg_dir)) {
				if (fs::is_regular_file(entry)) {
					// ���� ��ο� ������ ���ڿ��� ��ȯ�Ͽ� ���Ϳ� �߰�.
					// filename()���� ���ϸ� ����, stem()���� Ȯ���� ����.
					original_scg_file_paths.push_back(entry.path().string());
					original_scg_file_names.push_back(entry.path().filename().stem().string());
				}
				// ���� ��� ���
				cout << entry.path() << endl;
			}
			cout << "���ϸ��� ������ �ν� ���� �������� ��ȯ��..." << endl;
			for (const auto& str : original_scg_file_names) {
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
				size_t underbar_cut = str.find("_"); // ù ��° ������� ��ġ�� ã��
				if (underbar_cut != std::string::npos) {
					modified_first_file_names.push_back(str.substr(0, underbar_cut)); // ù ��° �κ�
					modified_second_file_names.push_back(str.substr(underbar_cut + 1)); // �� ��° �κ�
				}
			}

			// ������ ���ϸ� ���
			for (const auto& str : modified_scg_file_names)
				cout << str << endl;

			cout << "���� ������..." << endl;
			if (out_file.is_open()) {
				out_file << "init:" << endl;
				// ���� �迭�� ������ ���� �����ϱ�
				for (size_t i = 0; i < modified_scg_file_names.size(); ++i) {
					out_file << "    image " << modified_first_file_names[i] << " " << modified_second_file_names[i] << ":" << endl;
					out_file << "        \"" << original_scg_file_paths[i] << "\"" << endl;
					out_file << "        yalign 0.0" << endl;
				}
				out_file.close(); // ���� ��Ʈ�� �ݱ�
				cout << "���� ���� �Ϸ�: " << scg_output_filename << endl;
			}
			else {
				cerr << "������ �� �� �����ϴ�: " << scg_output_filename << endl;
			}
		}
		catch (const fs::filesystem_error& e) {
			cerr << e.what() << endl;
		}
	}
	else
	{
		cout << "���丮�� �������� �ʽ��ϴ�." << endl;
		cout << "�������� ���ư��ϴ�." << endl;
	}
}

void BGDefine()
{
	vector<string> original_bg_file_paths;
	vector<string> original_bg_file_names;
	vector<string> modified_bg_file_names;
	string bg_output_filename = "bg.rpy";
	ofstream out_file(bg_output_filename);

	fs::path bg_dir = "./renpy_example/game/images/BG/"; // ���� ��� ����
	if (fs::exists(bg_dir) && fs::is_directory(bg_dir)) // �ش� ���丮 ���� ���� Ȯ��
	{
		try {
			// ���丮 ���� ��� ���ϰ� ���� ���丮�� ����� ��ȸ
			cout << "���� ��� ã����..." << endl;
			for (const auto& entry : fs::recursive_directory_iterator(bg_dir)) {
				if (fs::is_regular_file(entry)) {
					// ���� ��ο� ������ ���ڿ��� ��ȯ�Ͽ� ���Ϳ� �߰�.
					// filename()���� ���ϸ� ����, stem()���� Ȯ���� ����.
					original_bg_file_paths.push_back(entry.path().string());
					original_bg_file_names.push_back(entry.path().filename().stem().string());
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
			for (const auto& str : modified_bg_file_names)
				cout << str << endl;

			cout << "���� ������..." << endl;
			if (out_file.is_open()) {
				out_file << "init:" << endl;
				// ���� �迭�� ������ ���� �����ϱ�
				for (size_t i = 0; i < modified_bg_file_names.size(); ++i) {
					out_file << "    image " << modified_bg_file_names[i] << ":" << endl;
					out_file << "        \"" << original_bg_file_paths[i] << "\"" << endl;
					out_file << "        yalign 0.0" << endl;
				}
				out_file.close(); // ���� ��Ʈ�� �ݱ�
				cout << "���� ���� �Ϸ�: " << bg_output_filename << endl;
			}
			else {
				cerr << "������ �� �� �����ϴ�: " << bg_output_filename << endl;
			}
		}
		catch (const fs::filesystem_error& e) {
			cerr << e.what() << endl;
		}
	}
	else
	{
		cout << "���丮�� �������� �ʽ��ϴ�." << endl;
		cout << "�������� ���ư��ϴ�." << endl;
	}
}






