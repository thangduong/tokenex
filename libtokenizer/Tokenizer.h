/*---------------------------------------------------------------------------------------------
*  Copyright (c) Microsoft Corporation. All rights reserved.
*  Licensed under the MIT License. See License.txt in the project root for license information.
*--------------------------------------------------------------------------------------------*/
#pragma once
#include <string>
#include <set>
#include <unordered_map>
#include <regex>
#include <iterator>
#include <iostream>
#include <list>
using namespace std;

class Tokenizer
{
	enum {
		REGEX_TOKEN_TYPE_START = 100
	};

	list<string> _discard_delimiters;
	list<string> _retain_delimiters;
	list<string> _exception_tokens;
	list<string> _exception_tokens_delimited_before;
	unordered_map<string, string> _translit_map;
	int _min_discard_delim_len, _max_discard_delim_len;
	int _min_retain_delim_len, _max_retain_delim_len;
	int _min_exception_token_len, _max__exception_token_len;
	int _min_translit_len, _max_translit_len;
	vector<tuple<regex, string, bool>> _exception_token_group_regex;

	inline size_t ExactStringMatch(const list<string>& candidates, const string& input_string, int start)
	{
		for (auto candidate_itr = candidates.begin();
			candidate_itr != candidates.end(); candidate_itr++) {
			string candidate = *candidate_itr;
			size_t len = candidate.length();
			if (input_string.compare(start, len, candidate) == 0) {
				return candidate_itr->length();
			}
		}
		return 0;
	}
	inline list<tuple<size_t,size_t,int>> RegexStringMatch(vector<tuple<regex,string,bool>>& candidates, const string& input_string, int start, bool test_all_regex)
	{
		int idx = 0;
		list<tuple<size_t,size_t, int>> result;
		for (auto candidate_itr = candidates.begin();
			candidate_itr != candidates.end(); candidate_itr++, idx++) {
			if (test_all_regex || (get<2>(*candidate_itr))) {
				smatch sm;
				regex_search(
						next(input_string.begin(), start), input_string.end(),
						sm, get<0>(*candidate_itr));
				if (sm.length()) {
					// return is: length of string to capture,
					// length to delimiter is required
					result.push_back(tuple<size_t,size_t,int>(sm[1].length(),sm[0].length(),idx));
				}
			}
		}		
		return result; //pair<size_t,size_t>(0,0);
	}

	bool CheckDelimiters(int matched_token_len, int check_len,
		int matched_type,
		const string& input_string,
		int& start_marker,
		int& marker,
		list<tuple<int, int, int>>& start_len_type,
		bool translit,
		list<string>* token_list);

	string Translit(const string& input_string, bool translit) {
		if (translit)
			return Translit(input_string);
		else
			return input_string;
	}

	void UpdateMinMaxLength();


	/**
	Correct indices and length in token_list to appropriate values assuming input str is UTF-8.
	*/
	void ConvertToUtf8Indices(const char* str, list<tuple<int, int, int>>* token_list);
public:
	Tokenizer();
	virtual ~Tokenizer();

	/**
	Translit unicode characters in a string.
	*/
	string Translit(const string& input_string);
	
	/**
	Tokenize a string and return extended token information

	@param[in] input_string		string to tokenize.
	@param[in] translit			whether to translit the resulting tokens or not
	@param[out] token_list		output list of tokens. set to nullptr if not needed.
	@param[in] utf8_encoding	true if the indices and lengths in the return value should be
								under the assumption that input_string is a utf-8 string.  
								Otherwise, everything would be byte based.
	@return
		a list of 3-tuple, each identifying a token in the input_string.  The tuple is interpreted as follows:
		(<start_index>, <length>, <type>)
		<start_index> is the start character of the token in input_string.
		<length> is the length of the token.
		<type> is the type of token based on regex. 
	*/
	list<tuple<int, int, int>> Tokenize(
		const string& input_string,
		bool translit = true, 
		list<string>* token_list = nullptr,
		bool utf8_encoding = true
		);
	
	/**
	Tokenize a string and create a new string where all the tokens are appended with " " in between


	@param[in] input_string					string to tokenize.
	@param[in] translit						whether to translit the resulting tokens or not
	@param[in] keep_original_in_regex		whether to keep the original string when regex matches.  e.g. <int>|10 vs just <int>.
	@param[out] token_start_len_type		output list of tokens desc (see tokenize). set to nullptr if not needed.
	@param[in] utf8_encoding				true if the indices and lengths in token_start_len_type should be
											under the assumption that input_string is a utf-8 string.
											Otherwise, everything would be byte based.
	@return
		a string consisting of tokens joined with " " in between.
	*/
	string TokenizeAndJuxtapose(
		const string& input_string, 
		bool translit = true, 
		bool keep_original_in_regex = false, 
		list<tuple<int, int, int>>* token_start_len_type = 0,
		bool utf8_encoding = true
		);
	
	/**
	Load default configuration
	*/
	void LoadDefaultConfig(int config_type = DEFAULT_CONFIG_TYPE_STANDARD);
	
	/**
	Load custom configuration from a file
	*/
	bool LoadCustomConfig(const string& filename);

	/**
	Save custom config to a file
	*/
	bool SaveConfig(const string& filename);

	/**
	Tokenizer configuration type.  Several things are configurable:
	1. whether to keep all text, including white spaces.
	2. whether to use regex when tokenize
	3. whether to use special tokens (<int>, <decimal>, etc.) when tokenize
	Multiple configurations can be ORed (|) together.
	*/
	enum DefaultConfigType {
		/**
		Use all standard default configurations: discard \r\n\s, use regex, use special tokens
		*/
		DEFAULT_CONFIG_TYPE_STANDARD = 0,
		/**
		If used, turns keep all text (\r\n\s)
		*/
		DEFUALT_CONFIG_TYPE_KEEP_ALL = 1,
		/**
		If used, disables regex
		*/
		DEFAULT_CONFIG_TYPE_NO_REGEX = 2,
		/**
		If used, disables use of special tokens.  This is ignored if regex is not used.
		*/
		DEFAULT_CONFIG_TYPE_NO_SPECIAL_TOKENS = 4,
	};
};

