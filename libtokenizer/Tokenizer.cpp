#include "Tokenizer.h"
#include <list>
#include <iostream>
using namespace std;

Tokenizer::Tokenizer()
{
}


Tokenizer::~Tokenizer()
{
}

template <class T>
void getMinMaxLenFromCollection(const T& collection, int& min_len, int& max_len) {
	if (collection.size() == 0)
		return;
	min_len = max_len = (int)(*collection.begin()).length();
	for (auto itr = collection.begin(); itr != collection.end(); itr++) {
		int len = (int)itr->length();
		if (len > max_len)
			max_len = len;
		if (len < min_len)
			min_len = len;
	}
}

void Tokenizer::UpdateMinMaxLength() {
	// compute min and max lengths
	_max_translit_len = _min_translit_len = (int)_translit_map.begin()->first.length();
	for (auto translit_itr = _translit_map.begin(); translit_itr != _translit_map.end(); translit_itr++) {
		if ((int)translit_itr->first.length() < _min_translit_len)
			_min_translit_len = (int)translit_itr->first.length();
		else if ((int)translit_itr->first.length() > _max_translit_len)
			_max_translit_len = (int)translit_itr->first.length();
	}

	getMinMaxLenFromCollection(_discard_delimiters, _min_discard_delim_len, _max_discard_delim_len);
	getMinMaxLenFromCollection(_retain_delimiters, _min_retain_delim_len, _max_retain_delim_len);
	getMinMaxLenFromCollection(_exception_tokens, _min_exception_token_len, _max__exception_token_len);
}

void Tokenizer::LoadDefaultConfig(int config_type) {
	_discard_delimiters.push_back("\xc2\xa0");
	_discard_delimiters.push_back("\x20\xa0");
	_discard_delimiters.push_back(" ");
	_discard_delimiters.push_back("\t");
	_discard_delimiters.push_back("\r");
	_discard_delimiters.push_back("\n");
//	_discard_delimiters.push_back(u8"¬");	// not sure what this is.  probably just noise!

	if (config_type & DEFUALT_CONFIG_TYPE_KEEP_ALL) {
		// make all discard delimiters retain delimiters
		_retain_delimiters.splice(_retain_delimiters.end(), _discard_delimiters);
	}

	// these are moved to regex
//	_retain_delimiters.push_back("....");
//	_retain_delimiters.push_back("...");
	_retain_delimiters.push_back("''");
	_retain_delimiters.push_back(u8"$");
	_retain_delimiters.push_back(u8"`");
	_retain_delimiters.push_back(u8":");
	_retain_delimiters.push_back(u8"!");
	_retain_delimiters.push_back(u8"%");
	_retain_delimiters.push_back(u8"^");
	_retain_delimiters.push_back(u8")");
	_retain_delimiters.push_back(u8"(");
	_retain_delimiters.push_back(u8"]");
	_retain_delimiters.push_back(u8"[");
	_retain_delimiters.push_back(u8"}");
	_retain_delimiters.push_back(u8"{");
	_retain_delimiters.push_back(u8"@");
	_retain_delimiters.push_back(u8"#");
	_retain_delimiters.push_back(u8"~");
	_retain_delimiters.push_back(u8"-");
	_retain_delimiters.push_back(u8".");
	_retain_delimiters.push_back(u8"\"");
	_retain_delimiters.push_back(u8"'");
	_retain_delimiters.push_back(u8";");
	_retain_delimiters.push_back(u8",");
	_retain_delimiters.push_back(u8"™");
	_retain_delimiters.push_back(u8"€");
	_retain_delimiters.push_back(u8"°");
	_retain_delimiters.push_back(u8"?");
	_retain_delimiters.push_back(u8"*");
	_retain_delimiters.push_back(u8"|");
	_retain_delimiters.push_back(u8"…");
	_retain_delimiters.push_back(u8"=");
	_retain_delimiters.push_back(u8"+");
	_retain_delimiters.push_back(u8"&");
	_retain_delimiters.push_back(u8"/");
	_retain_delimiters.push_back(u8"\\");
	_retain_delimiters.push_back(u8"—");
	_retain_delimiters.push_back(u8"–");
	_retain_delimiters.push_back(u8"–");
	_retain_delimiters.push_back(u8"’");
	_retain_delimiters.push_back(u8"ʼ");
	_retain_delimiters.push_back(u8"“");
	_retain_delimiters.push_back(u8"”");
	_retain_delimiters.push_back(u8"‘");
	_retain_delimiters.push_back(u8"′");
	_retain_delimiters.push_back(u8"¶");
	_retain_delimiters.push_back(u8"″");
	_retain_delimiters.push_back(u8"·");
	_retain_delimiters.push_back(u8"¢");
	_retain_delimiters.push_back(u8"⁄");
	_retain_delimiters.push_back(u8">");
	_retain_delimiters.push_back(u8"<");
	_retain_delimiters.push_back(u8"−");
	_retain_delimiters.push_back(u8"•");
	_retain_delimiters.push_back(u8"·");
	_retain_delimiters.push_back(u8"£");
	_retain_delimiters.push_back(u8"±");
	_retain_delimiters.push_back(u8"");

	_exception_tokens.push_back(u8"'s");
	_exception_tokens.push_back(u8"'S");
	_exception_tokens.push_back(u8"n't");
	_exception_tokens.push_back(u8"N't");
	_exception_tokens.push_back(u8"n'T");
	_exception_tokens.push_back(u8"N'T");
	_exception_tokens.push_back(u8"’s");
	_exception_tokens.push_back(u8"’S");
	_exception_tokens.push_back(u8"ʼs");
	_exception_tokens.push_back(u8"ʼS");
	_exception_tokens.push_back(u8"n’t");
	_exception_tokens.push_back(u8"N’t");
	_exception_tokens.push_back(u8"n’T");
	_exception_tokens.push_back(u8"N’T");
	_exception_tokens.push_back(u8"'m");
	_exception_tokens.push_back(u8"'M");
	_exception_tokens.push_back(u8"’m");
	_exception_tokens.push_back(u8"’M");
	_exception_tokens.push_back(u8"s'");
	_exception_tokens.push_back(u8"S'");
	_exception_tokens.push_back(u8"s’");
	_exception_tokens.push_back(u8"S’");
	_exception_tokens.push_back(u8"gov’t");
	_exception_tokens.push_back(u8"Gov’t");
	_exception_tokens.push_back(u8"GOV’T");
	_exception_tokens.push_back(u8"'ve");
	_exception_tokens.push_back(u8"’ve");
	_exception_tokens.push_back(u8"'Ve");
	_exception_tokens.push_back(u8"’Ve");
	_exception_tokens.push_back(u8"'vE");
	_exception_tokens.push_back(u8"’vE");
	_exception_tokens.push_back(u8"'VE");
	_exception_tokens.push_back(u8"’VE");
	_exception_tokens.push_back(u8"'re");
	_exception_tokens.push_back(u8"’re");
	_exception_tokens.push_back(u8"'Re");
	_exception_tokens.push_back(u8"’Re");
	_exception_tokens.push_back(u8"'rE");
	_exception_tokens.push_back(u8"’rE");
	_exception_tokens.push_back(u8"'RE");
	_exception_tokens.push_back(u8"’RE");
	_exception_tokens.push_back(u8"'ll");
	_exception_tokens.push_back(u8"’ll");
	_exception_tokens.push_back(u8"'Ll");
	_exception_tokens.push_back(u8"’Ll");
	_exception_tokens.push_back(u8"'lL");
	_exception_tokens.push_back(u8"’lL");
	_exception_tokens.push_back(u8"'LL");
	_exception_tokens.push_back(u8"’LL");
	_exception_tokens.push_back("(tm)");
	_exception_tokens.push_back("'t");
	_exception_tokens.push_back(u8"`t");
	_exception_tokens.push_back(">=");
	_exception_tokens.push_back("<=");

	_exception_tokens_delimited_before.push_back("dr.");
	_exception_tokens_delimited_before.push_back("Dr.");
	_exception_tokens_delimited_before.push_back("no.");
	_exception_tokens_delimited_before.push_back("No.");
	_exception_tokens_delimited_before.push_back("mr.");
	_exception_tokens_delimited_before.push_back("Mr.");
	_exception_tokens_delimited_before.push_back("Ms.");
	_exception_tokens_delimited_before.push_back("ms.");
	_exception_tokens_delimited_before.push_back("Mrs.");
	_exception_tokens_delimited_before.push_back("mrs.");
	_exception_tokens_delimited_before.push_back(u8"can't");
	_exception_tokens_delimited_before.push_back(u8"can’t");
	_exception_tokens_delimited_before.push_back(u8"Can't");
	_exception_tokens_delimited_before.push_back(u8"Can’t");
	_exception_tokens_delimited_before.push_back("jr.");
	_exception_tokens_delimited_before.push_back("Jr.");
	_exception_tokens_delimited_before.push_back("sr.");
	_exception_tokens_delimited_before.push_back("Sr.");
	_exception_tokens_delimited_before.push_back("hon.");
	_exception_tokens_delimited_before.push_back("hr.");
	_exception_tokens_delimited_before.push_back("hosp.");
	_exception_tokens_delimited_before.push_back("lt.");
	_exception_tokens_delimited_before.push_back("gen.");
	_exception_tokens_delimited_before.push_back("Gen.");
	_exception_tokens_delimited_before.push_back("e-mail");
	_exception_tokens_delimited_before.push_back("E-mail");
	_exception_tokens_delimited_before.push_back("E-Mail");
	_exception_tokens_delimited_before.push_back("Rock'n'Roll");
	_exception_tokens_delimited_before.push_back("Rock'N'Roll");
	_exception_tokens_delimited_before.push_back("rock'n'roll");
	_exception_tokens_delimited_before.push_back("rock'N'roll");


	_translit_map[u8"™"] = "(tm)";
	_translit_map[u8"“"] = "\"";
	_translit_map[u8"”"] = "\"";
	_translit_map[u8"…"] = "...";
	_translit_map[u8"–"] = "-";
	_translit_map[u8"–"] = "-";
	_translit_map[u8"—"] = "--";
	_translit_map[u8"′"] = "'";
	_translit_map[u8"`"] = "'";
	_translit_map[u8"’"] = "'";
	_translit_map[u8"‘"] = "'";
	_translit_map[u8"…"] = "...";
	_translit_map["''"] = "\"";		// this is questionable
	_translit_map["``"] = "\"";		// this is questionable
	_translit_map[u8"À"] = "A";
	_translit_map[u8"Á"] = "A";
	_translit_map[u8"Â"] = "A";
	_translit_map[u8"Ã"] = "A";
	_translit_map[u8"Ä"] = "A";
	_translit_map[u8"Å"] = "A";
	_translit_map[u8"Æ"] = "AE";
	_translit_map[u8"Ç"] = "c";

	_translit_map[u8"È"] = "E";
	_translit_map[u8"É"] = "E";
	_translit_map[u8"Ê"] = "E";
	_translit_map[u8"Ë"] = "E";

	_translit_map[u8"Ì"] = "I";
	_translit_map[u8"Í"] = "I";
	_translit_map[u8"Î"] = "I";
	_translit_map[u8"Ï"] = "I";

	_translit_map[u8"Ñ"] = "N";

	_translit_map[u8"Ò"] = "O";
	_translit_map[u8"Ó"] = "O";
	_translit_map[u8"Ô"] = "O";
	_translit_map[u8"Õ"] = "O";
	_translit_map[u8"Ö"] = "O";

	_translit_map[u8"×"] = "x";
	_translit_map[u8"Ø"] = "O";

	_translit_map[u8"Ù"] = "U";
	_translit_map[u8"Ú"] = "U";
	_translit_map[u8"Û"] = "U";
	_translit_map[u8"Ü"] = "U";

	_translit_map[u8"Ý"] = "Y";


	_translit_map[u8"à"] = "a";
	_translit_map[u8"á"] = "a";
	_translit_map[u8"â"] = "a";
	_translit_map[u8"ã"] = "a";
	_translit_map[u8"ä"] = "a";
	_translit_map[u8"å"] = "a";

	_translit_map[u8"æ"] = "ae";

	_translit_map[u8"ç"] = "c";

	_translit_map[u8"è"] = "e";
	_translit_map[u8"é"] = "e";
	_translit_map[u8"ê"] = "e";
	_translit_map[u8"ë"] = "e";
	_translit_map[u8"″"] = "\"";
	_translit_map[u8"ì"] = "i";
	_translit_map[u8"í"] = "i";
	_translit_map[u8"î"] = "i";
	_translit_map[u8"ï"] = "i";

	_translit_map[u8"ò"] = "o";
	_translit_map[u8"ó"] = "o";
	_translit_map[u8"ô"] = "o";
	_translit_map[u8"õ"] = "o";
	_translit_map[u8"ö"] = "o";

	_translit_map[u8"ù"] = "u";
	_translit_map[u8"ú"] = "u";
	_translit_map[u8"û"] = "u";
	_translit_map[u8"ü"] = "u";

	_translit_map[u8"ý"] = "y";
	_translit_map[u8"ÿ"] = "y";

	_translit_map[u8"÷"] = "/";
	_translit_map[u8"ø"] = "o";
	_translit_map[u8"ñ"] = "n";

	_translit_map[u8"Š"] = "S";
	// tuple meaning:
	//	0 = regular expression
	//	1 = string to identify token, if "", then string is actual matched string
	//	2 = true if this can act as a retain delimiter, false if not

	if (!(config_type & DEFAULT_CONFIG_TYPE_NO_REGEX)) {
		_exception_token_group_regex.push_back(tuple<regex, string, bool>(regex("^([0-9]*\\.(?:[0-9])+)(?:km|mi\\.|ml|mm|kg|g|Kg|KG)"), "<decimal>", false));
		_exception_token_group_regex.push_back(tuple<regex, string, bool>(regex("^([0-9]*)(?:km|mi\\.|ml|mm|kg|g|Kg|KG)"), "<int>", false));
		_exception_token_group_regex.push_back(tuple<regex, string, bool>(regex("^([0-9]*\\.[0-9]+)(?:[mMBbkK])"), "<decimal>", false));
		_exception_token_group_regex.push_back(tuple<regex, string, bool>(regex("^([0-9]+)(?:[mMBbkK])"), "<int>", false));
		_exception_token_group_regex.push_back(tuple<regex, string, bool>(regex("^([0-9]*\\.[0-9]+)"), "<decimal>", false));

		_exception_token_group_regex.push_back(tuple<regex, string, bool>(regex("^([12][0-9][0-9]0s)"), "<decade-year>", false));
		_exception_token_group_regex.push_back(tuple<regex, string, bool>(regex("^([0-9]0s)"), "<decade>", false));
		_exception_token_group_regex.push_back(tuple<regex, string, bool>(regex("^((\\([0-9][0-9][0-9]\\)|[0-9][0-9][0-9])[ -]*[0-9][0-9][0-9][ -]*[0-9][0-9][0-9][0-9])"), "<phone>", false));
		_exception_token_group_regex.push_back(tuple<regex, string, bool>(regex("^(([0-9][0-9][0-9]|[0-9][0-9]|[0-9])(?:,[0-9][0-9][0-9])+)"), "<large-int>", false));
		_exception_token_group_regex.push_back(tuple<regex, string, bool>(regex("^(([A-Za-z][.])+[A-Za-z]?)"), "", false));
		_exception_token_group_regex.push_back(tuple<regex, string, bool>(regex("^([=-]+)"), "", true));
		_exception_token_group_regex.push_back(tuple<regex, string, bool>(regex("^(\\.\\.+)"), "", true));
		_exception_token_group_regex.push_back(tuple<regex, string, bool>(regex("^([0-9]*[04-9]th|[0-9]*1st|[0-9]*[2]nd|[0-9]*3rd|13th|12th|11th)"), "<ordinal>", false));
//		_exception_token_group_regex.push_back(tuple<regex, string, bool>(regex("^([0-9]+k)"), "<int-k>", false));


		// these are delicate.  if a number starts with 0-3, then it must have at least 2 digits
		// if a number starts with 4-9, then it doesn't need to have at least 2 digits.  it can just be 1 digit.
		_exception_token_group_regex.push_back(tuple<regex, string, bool>(regex("^([0-3][0-9]+)"), "<int>", false));
		_exception_token_group_regex.push_back(tuple<regex, string, bool>(regex("^(0)"), "<zero>", false));
		_exception_token_group_regex.push_back(tuple<regex, string, bool>(regex("^(1)"), "<one>", false));
		_exception_token_group_regex.push_back(tuple<regex, string, bool>(regex("^(2)"), "<two>", false));
		_exception_token_group_regex.push_back(tuple<regex, string, bool>(regex("^(3)"), "<three>", false));
		_exception_token_group_regex.push_back(tuple<regex, string, bool>(regex("^([0-9]+)"), "<int>", false));

		_exception_token_group_regex.push_back(tuple<regex, string, bool>(regex("^((\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+)"), "<email>", false));
		_exception_token_group_regex.push_back(tuple<regex, string, bool>(regex("^((?:https?|ftp)://[^ ]*)"), "<url>", false));
	}

	UpdateMinMaxLength();
}

bool Tokenizer::CheckDelimiters(int matched_token_len, int check_len,
	int matched_type, 
	const string& input_string, 
	int& start_marker, 
	int& marker, 
	list<tuple<int, int, int>>& start_len_type, 
	bool translit,
	list<string>* token_list) {

	if (matched_token_len > 0) {
		int proposed_marker = marker + matched_token_len;
		if (
			   (ExactStringMatch(_discard_delimiters, input_string, marker+check_len) > 0)
			|| (ExactStringMatch(_retain_delimiters, input_string, marker+check_len) > 0)
			|| ((marker+check_len) >= (int)input_string.length())
			){
			if (start_marker < marker) {
				tuple<int, int, int> token(start_marker, marker - start_marker, 0);
				start_len_type.push_back(token);
				if (token_list)
					token_list->push_back(Translit(input_string.substr(get<0>(token),get<1>(token)),translit));
			}
			tuple<int, int, int> token(marker, matched_token_len, matched_type);
			start_len_type.push_back(token);
			if (token_list) {
				if ((matched_type > 0) && (!get<1>(_exception_token_group_regex[matched_type - REGEX_TOKEN_TYPE_START]).empty()))
					token_list->push_back(Translit(get<1>(_exception_token_group_regex[matched_type - REGEX_TOKEN_TYPE_START]),translit));
				else
					token_list->push_back(Translit(input_string.substr(get<0>(token), get<1>(token)),translit));
			}
			marker = proposed_marker;
			start_marker = marker;
			return true;
		}
	}
	return false;
}


list<tuple<int,int,int>> Tokenizer::Tokenize(const string& input_string, bool translit, list<string>* token_list) {
	int start_marker = 0;
	int marker = 0;
	list<tuple<int, int, int>> result;

	while (marker < (int)input_string.length()) {
		
		size_t matched_exception_token_len = ExactStringMatch(_exception_tokens, input_string, marker);
		if ((matched_exception_token_len>0) 
			&& CheckDelimiters((int)matched_exception_token_len, (int)matched_exception_token_len, 0, input_string, start_marker, marker, result, translit, token_list))
			continue;

		if (marker == start_marker) {
			matched_exception_token_len = ExactStringMatch(_exception_tokens_delimited_before, input_string, marker);
			if ((matched_exception_token_len > 0)
				&& CheckDelimiters((int)matched_exception_token_len, (int)matched_exception_token_len, 0, input_string, start_marker, marker, result, translit, token_list))
				continue;
		}

		int regex_pattern_matched;
		pair<size_t,size_t> matched_regex_token_len = RegexStringMatch(_exception_token_group_regex, input_string, marker, (marker == start_marker), &regex_pattern_matched);
		if ((matched_regex_token_len.first>0) && (get<2>(_exception_token_group_regex[regex_pattern_matched - REGEX_TOKEN_TYPE_START]) || (marker == start_marker))) {
			if (get<2>(_exception_token_group_regex[regex_pattern_matched - REGEX_TOKEN_TYPE_START])) {
				// can act as delimiter, no need to check that the second piece is delimiter.  just skip forward
				// treat as if delimiter
				if (start_marker < marker) {
					tuple<int, int, int> token(start_marker, marker - start_marker, 0);
					result.push_back(token);
					if (token_list)
						token_list->push_back(Translit(input_string.substr(get<0>(token), get<1>(token)), translit));
				}
				tuple<int, int, int> token(marker, (int)matched_regex_token_len.first, 0);
				result.push_back(token);
				if (token_list) {
					string tok_replacement_str = get<1>(_exception_token_group_regex[regex_pattern_matched - REGEX_TOKEN_TYPE_START]);
					if (!tok_replacement_str.empty())
						token_list->push_back(Translit(tok_replacement_str, translit));
					else
						token_list->push_back(Translit(input_string.substr(get<0>(token), get<1>(token)), translit));
				}

				marker += (int)matched_regex_token_len.first;
				start_marker = marker;
				continue;
			}
			else {
				if (CheckDelimiters((int)matched_regex_token_len.first, (int)matched_regex_token_len.second, regex_pattern_matched, input_string, start_marker, marker, result, translit, token_list))
					continue;
			}
		}

		size_t discard_token_len = ExactStringMatch(_discard_delimiters, input_string, marker);
		if (discard_token_len > 0) {
			if (start_marker < marker) {
				tuple<int, int, int> token(start_marker, marker - start_marker, 0);
				result.push_back(token);
				if (token_list)
					token_list->push_back(Translit(input_string.substr(get<0>(token), get<1>(token)),translit));
			}
			marker += discard_token_len;
			start_marker = marker;
			continue;
		}

		size_t retain_token_len = ExactStringMatch(_retain_delimiters, input_string, marker);
		if (retain_token_len > 0) {
			if (start_marker < marker) {
				tuple<int, int, int> token(start_marker, marker - start_marker, 0);
				result.push_back(token);
				if (token_list)
					token_list->push_back(Translit(input_string.substr(get<0>(token), get<1>(token)),translit));
			}
			tuple<int, int, int> token(marker, (int)retain_token_len, 0);
			result.push_back(token);
			if (token_list)
				token_list->push_back(Translit(input_string.substr(get<0>(token), get<1>(token)),translit));

			marker += (int)retain_token_len;
			start_marker = marker;
			continue;
		}
		marker += 1;
	} 
	if (start_marker < marker) {
		tuple<int, int, int> token(start_marker, marker - start_marker, 0);
		result.push_back(token);
		if (token_list)
			token_list->push_back(Translit(input_string.substr(get<0>(token), get<1>(token)),translit));
	}
	return result;
}

string Tokenizer::TokenizeAndJuxtapose(const string& input_string, bool translit, bool keep_original_in_regex, list<tuple<int, int, int>>* token_start_len_type) {
	list<string> tokens;
	list<tuple<int, int, int>> local_token_start_len_type;
	if (token_start_len_type == nullptr)
		token_start_len_type = &local_token_start_len_type;
	(*token_start_len_type) = Tokenize(input_string, translit, &tokens);
	string result;
	auto slt = token_start_len_type->begin();
	for (auto token = tokens.begin(); token != tokens.end();token++, slt++) {
		if (!result.empty())
			result += " ";
		if (
				keep_original_in_regex
				&& (get<2>(*slt)>=REGEX_TOKEN_TYPE_START)
				&& (!get<1>(_exception_token_group_regex[get<2>(*slt) - REGEX_TOKEN_TYPE_START]).empty())
			)
			result += (*token)+"|"+input_string.substr(get<0>(*slt), get<1>(*slt));
		else
			result += (*token);
	}
	return result;
}

string Tokenizer::Translit(const string& input_string) {
	int marker = 0;
	int start_marker = marker;
	string result = "";
	while (marker < (int)input_string.length()) {
		for (auto len = _min_translit_len; len <= _max_translit_len; len++) {
			string piece = input_string.substr(marker, len);
			auto match = _translit_map.find(piece);
			if (match != _translit_map.end()) {
				result += input_string.substr(start_marker, marker - start_marker) + match->second;
				marker += len - 1;
				start_marker = marker + 1;
				break;
			}
		}
		marker += 1;
	}
	if (start_marker < (int)input_string.length())
		result += input_string.substr(start_marker);
	return result;
}
