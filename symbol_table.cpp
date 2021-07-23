#include "symbol_table.hpp"


void SymbolTable::insert(const std::string& name, const Type& type, offset_entry_t offset , const std::string& place)
{
	if (contains_name(name))
	{
		std::cout << "Error: SymbolTable::insert(): name " << name << " already exists!\n";
		return;
	}

	TableEntry t(name, type, offset, place);
	if (type._is_func) {t._is_func=true;}
	_symbol_entries.push_back(t);
}


void SymbolTable::insert(const std::vector<TableEntry>& args)
{
	for (auto &p : args)
	{
		insert(p._name, p._type, p._offset, p._place);
	}
}

/*
void SymbolTable::print()
{
	for (auto const &p : _symbol_entries)
	{
		std::cout << "Name: " << p._name << "\nType: " << p._type._basic_type << "\n";
		if (p._is_func) 
		{ 
			std::cout << "Function Type:\n" << p._type._basic_type << "\n";
			std::cout << "Function return type:\n" << p._type._return_type << "\n";
			std::cout << "Function args:\n";
			for (auto const &p : p._type._args_types)
			{
				std::cout << p << "\n";
			}
		}
	}
}
*/


bool SymbolTable::contains_name(const std::string& name)
{
	for (auto const &p : _symbol_entries)
	{
		if (p._name == name){return true;}
	}
	return false;
}


TableEntry SymbolTable::get_table_entry(const std::string& name)

{
	for (auto &p : _symbol_entries)
	{
		if (p._name == name){return p;}
	}

	std::cout << "Reached SymbolTable::get_table_entry - mistake?\n";
	exit(1337);
}

std::string SymbolTable::get_curr_scope_ret_type()
{
	std::string s("NO_FUNC");
	for (std::vector<TableEntry>::reverse_iterator it = _symbol_entries.rbegin(); it != _symbol_entries.rend(); ++it)	
	{
		if (it ->_type._basic_type == "FUNC") {return it ->_type._return_type;}
	}
	return s;
}