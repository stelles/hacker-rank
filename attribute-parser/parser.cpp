#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <map>
#include <regex>
#include <functional> 


using namespace std;

bool closing_tag(string s) {
    bool closing = s[1] == '/';

    return closing;
}

string tagname(const string s) {
    int start = closing_tag(s) ? 2 : 1;  // If closing tag, we want substring of 2
    char end_char = closing_tag(s) ? '>' : ' '; // set end char as well
    int end = s.find_first_of(end_char);
    end = end - start;
    // end = closing_tag(s) ? end : end - 1;
    // end = end - 1;
    string tempname = s.substr(start, end);
    return tempname;
}

map<string,string> tagattr(string s) {
    map<string, string> attrs;
    regex attr_regex("([A-z0-9\-]+) \= \"([A-z0-9\-]+)\"");
    smatch matches;
    if (regex_search(s, matches, attr_regex)) {
        int size = matches.size();
        for (size_t i = 0; i < matches.size(); i++) {
            string key = matches.str(1);
            string val = matches.str(2);
            attrs[key] = val;
        }
    }
    return attrs;
}


struct tag {
    string name;
    tag * parent;
    map<string, string> attributes;
    map<string, tag*> subtags;
};

tag parse(const string &in){
    // declare our root and set the current to root
    tag root;
    root.name = "root";
    // root.parent = &root;
    // tag *current = &root;

    vector<tag*> tagstack = { &root };

    // Use regex to extract brackets
    regex words_regex("\<.+?\>");
    auto words_begin = sregex_iterator(in.begin(), in.end(), words_regex);
    auto words_end = sregex_iterator();

    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        smatch match = *i;                                                 
        string match_str = match.str();
        
        
        if (!closing_tag(match_str)) {
            tag * new_tag = new tag();
            tag * parent = tagstack.back();

            const string name = tagname(match_str);
            const map<string,string> attributes = tagattr(match_str);
            
            new_tag->name = name;
            new_tag->attributes = attributes;
            // string print = std;
            new_tag->parent = parent;
            parent->subtags[name] = new_tag;
            tagstack.push_back(new_tag);

        } else {
            tag * finished = tagstack.back();
            tagstack.pop_back();
            tag * p = tagstack.back();
        }

    }
    return root;
}

string print_attribute(const string attr, const tag root) {
    const string not_found = "Not Found!";
    stringstream segmentstream(attr);
    string tagname = "";
    string attribute_name = "";

    bool in_attr = false;

    vector<string> taglist;

    tag * rootp = new tag(root);

    for (int i = 0; i < attr.size(); i++) {
        char c = attr[i];
        if (c == '.' || (!in_attr && i == attr.size()-1)) {
            taglist.push_back(tagname);
            tagname = "";
        } else if (c == '~') {
            taglist.push_back(tagname);
            in_attr = true;
        } else {
            if (!in_attr) { 
                tagname += c;
            } else {
                attribute_name += c;
            }
        }
    }

    for (auto &tagname : taglist) {
        try {
            tag * new_root = rootp->subtags.at(tagname);
            rootp = new_root;
        } catch (out_of_range) {
            return not_found;
        }
    }
    
    if (attribute_name != "") { 
        try {
            string val = rootp->attributes.at(attribute_name);
            return val;
        } catch (out_of_range) {
            return not_found;
        }
    }
    return rootp->name;
}

int main() {

    // Loading file ends here
    string line;
    getline(cin, line);

    vector<int> inputs;
    istringstream in(line);
    copy( istream_iterator<int>( in ), istream_iterator<int>(), back_inserter( inputs ) );

    int incout = inputs[0];
    int attrCount = inputs[1];

    string instring;
    for (int i = 0; i < incout; i++) {
        string buff;
        getline(cin, buff);
        instring.append(buff);
    }

    tag root = parse(instring);

    string attrsInfo;
    string result;
    for (int i = 0; i < attrCount; i++){
        getline(cin, attrsInfo);
        result = print_attribute(attrsInfo, root);
        cout << result << endl;
    }

    return 0;
}
