#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <string>
#include "output.hpp"
#include "bp.hpp"

class Node
{
public:
	Node() = default;
	Node(const std::string& type, const std::string& place = ""):
		_type(type),
		_place(place),
		_is_zero_ext(false),
		_while_global(0),
		_statement_contains_break(false)
		{}
public:
	int _lineNo;
	std::string _type;
	// check changes
	std::string _place;
	vector <pair<int, BranchLabelIndex>> true_list;
    vector <pair<int, BranchLabelIndex>> false_list;
	vector <pair<int, BranchLabelIndex>> break_list;
    vector <pair<int, BranchLabelIndex>> continue_list;
	vector <pair<int, BranchLabelIndex>> next_list;
	bool _is_zero_ext;
	int _while_global;
	bool _statement_contains_break;
};


#define YYSTYPE Node*


class Num : public Node
{
public:
	Num(int n):
		Node("NUM"),
		_value(n)
		{}
public:
	int _value;
};


class String : public Node
{
public:
	String(const std::string& str):
		Node("STRING"),
		_value(str)
		{}
public:
	std::string _value;
};


class Func : public Node
{
public:
	Func(const std::string& value, const std::string& ret_type):
		Node(ret_type),
		_value(value),
		_ret_type(ret_type),
		_contains_bool_arg(false)
		{}
public:
	std::string _value;
	std::string _ret_type;
	std::vector<std::string> _args_types;
	std::vector<std::string> _args_places;
	bool _contains_bool_arg;
};


class Case : public Node
{
public:
	Case(const std::string& quad, int numeric_val, bool contains_break = false, bool is_default = false):
		Node(std::string("CASE")),
		_quad(quad),
		_numeric_val(numeric_val),
		_contains_break(contains_break),
		_is_default(is_default)
		{}
	std::string _quad;
	int _numeric_val;
	bool _contains_break;
	bool _is_default;
};


class Caselist : public Node
{
public:
	Caselist() :
		Node("CASELIST"),
		_quad_list(std::vector<std::string>()),
		_numeric_val_list(std::vector<int>()),
		_contains_break_list(std::vector<bool>()),
		_conds_next_lists(std::vector<std::vector<std::pair<int, BranchLabelIndex>>>())
		{}
	Caselist(const std::vector<std::string>& quad_list, const std::vector<int>& numeric_val_list, bool contains_default=false):
		Node("CASELIST"),
		_quad_list(quad_list),
		_numeric_val_list(numeric_val_list),
		_contains_default(contains_default)
		{}
	std::vector<std::string> _quad_list;
	std::vector<int> _numeric_val_list;
	std::vector<bool> _contains_break_list;
	std::vector<std::vector<std::pair<int, BranchLabelIndex>>> _conds_next_lists;
	bool _contains_default;
	
};


#endif 