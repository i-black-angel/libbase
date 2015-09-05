#include "utils.h"

void base::split(const string &content, const string &delim, vector<string> *retarr) {
	if (NULL == retarr) return;
	string split_content = content;
	string::size_type key_point = string::npos;
	while ((key_point = split_content.find_first_of(delim)) != string::npos) {
		if (key_point > 0) {
			retarr->push_back(split_content.substr(0, key_point));
		} else {
			retarr->push_back("");
		}
		split_content = split_content.substr(key_point + 1);
	}
	if (split_content.size() > 0) {
		retarr->push_back(split_content);
	} else {
		retarr->push_back("");
	}
}
