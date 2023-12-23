#pragma once
#include <filesystem>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;
namespace fs = std::filesystem;

bool SubChoice(int subchoice);
void DefineAll();
void BGMDefine();
void SEDefine();
void SCGDefine();
void BGDefine();
void ScriptChecker();
void ProcessLine(const string& line, const string& search_string,
                 set<string>& result_set);
void PrintSet(const string& set_type, const set<string>& result_set);
void ProcessLineForSCG(const string& line, const string& search_string,
                       set<string>& result_set);
void FindUnusedResources(const string& resource_type);