﻿/*---------------------------------------------------------------------------------------------
*  Copyright (c) Microsoft Corporation. All rights reserved.
*  Licensed under the MIT License. See License.txt in the project root for license information.
*--------------------------------------------------------------------------------------------*/
#include <Windows.h>
#include <stdio.h>
#include "Tokenizer.h"
#include <regex>
#include <fstream>
#include <cwchar>
#include <clocale>
using namespace std;
int main(int argc, char* argv[]) {
	Tokenizer t;
	t.LoadDefaultConfig();
	list<tuple<int, int, int>> toks = t.Tokenize(u8"™Hello this is a “test” and there’s more …", true);
	for (auto x = toks.begin(); x != toks.end(); x++) {
		cout << get<0>(*x) << " " << get<1>(*x) << " " << get<2>(*x) << endl;
	}
	cout << t.Translit(u8"™Hello this is a “test” and there’s more …") << endl;
//	string tj = t.TokenizeAndJuxtapose("1995 is from 1950s to 1980s $150, 1 man ate 50 sandwiches by himself and the effrot was 0.  thang@quantee.com email me and my homepage is http://www.quantee.com/test.asp. my number is 510-847-7898 or (510)847-7898 or (510) 847-7898");
//	string tj = t.TokenizeAndJuxtapose("The car on t.v. runs at about 500 r.p.m.");
	DWORD bef = timeGetTime();
	string tj;
	for (int i = 0; i < 1000; i++)
		tj = t.TokenizeAndJuxtapose("An-24 with a succession of upgrades culminating in the Xian MA60 (Modern Ark) series.");
	DWORD diff = timeGetTime() - bef;
	cout << tj << " " << diff << endl;
	exit(0);
	if (argc != 3) {
		cout << "Usage: " << argv[0] << " <input-file> <output-file>" << endl;
		exit(0);
	}
	ifstream ifile(argv[1]);// "O:\\1-billion-word-language-modeling-benchmark\\training-monolingual\\news.2007.en.shuffled");
	ofstream ofile(argv[2]);// "e:\\test.txt");
	string str;
	int i = 0;
	while (getline(ifile, str))
	{
		string tj = t.TokenizeAndJuxtapose(str);
		ofile << tj << endl;
		i++;
		if ((i % 10000) == 0) {
			cout << "Tokenized " << i << " records" << endl;
			ofile.flush();
		}
	}
	return 0;
}
