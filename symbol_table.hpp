#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include "output.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <map>

using identifier_t = std::string;
using offset_entry_t = int;

typedef enum scope_t { 
	SCOPE_DEFAULT,
	SCOPE_GLOBAL,
    SCOPE_FUNC, 
    SCOPE_IF, 
    SCOPE_ELSE,
    SCOPE_WHILE, 
    SCOPE_SWITCH,
} scope_t;


class Type // Also required to support function types
{
public:
	Type() = default;
	Type(const std::string& basic_type, const std::string& return_type=std::string(), const std::vector<std::string>& args_types=std::vector<std::string>(), bool is_func=false):
		_basic_type(basic_type),
		_return_type(return_type),
		_args_types(args_types),
		_is_func(is_func)
		{}
	~Type() = default;
	std::string _basic_type;  // In case of function - holds the string FUNC
	std::string _return_type;  // only initiated for functions
	std::vector<std::string> _args_types;  // only initiated for functions
	bool _is_func;
};


class TableEntry
{
public:
	TableEntry() = default;
	TableEntry(const std::string& name):
		_name(name)
		{}
	TableEntry(const std::string& name, const Type& type, offset_entry_t offset, const std::string& place = "IMP_PLACE_CTOR"):
		_name(name),
		_type(type),
		_offset(offset),
		_is_func(false),
		_place(place)
		{
			if (_type._basic_type == "FUNC") {_is_func=true;}
		}
	~TableEntry() = default;
	std::string _name;
	Type _type; 
	offset_entry_t _offset; 
	bool _is_func;
	// check this
	std::string _place;
	
};


class SymbolTable
{
public:
	SymbolTable() :
		_scope_type(SCOPE_DEFAULT)
	{}
	~SymbolTable() = default;
	// void print();
	void insert(const std::string& name, const Type& type, offset_entry_t offset, const std::string& place = "IMP_PLACE");
	void insert(const std::vector<TableEntry>& args);
	bool contains_name(const std::string& name);
	TableEntry get_table_entry(const std::string& name); 
	std::string get_curr_scope_ret_type();


public:
	// std::map<identifier_t, TableEntry> _symbol_entries;  // maps between identifiers and their corresponding entries
	std::vector<TableEntry> _symbol_entries;
	scope_t _scope_type;
	std::string _scope_return_type;
};

#endif
