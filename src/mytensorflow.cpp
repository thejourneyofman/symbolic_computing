#include "mytensorflow.h"

/// Constructor
mytensorflow::mytensorflow()
{
    //ctor
}

/// Destructor
mytensorflow::~mytensorflow()
{
    //dtor
}

/// Register a new "+" operation to the computing graph
/// :param #1 : operation name
void mytensorflow::add_register(string a)
{
    auto it = find(add_symbol.begin(), add_symbol.end(), a);
    assert(it == add_symbol.end());
    add_symbol.push_back(a);
}

/// Register a new "*" operation to the computing graph
/// :param #1 : operation name
void mytensorflow::mul_register(string a)
{
    auto it = find(mul_symbol.begin(), mul_symbol.end(), a);
    assert(it == mul_symbol.end());
    mul_symbol.push_back(a);
}

/// Register a new "-" operation to the computing graph
/// :param #1 : operation name
void mytensorflow::min_register(string a)
{
    auto it = find(min_symbol.begin(), min_symbol.end(), a);
    assert(it == min_symbol.end());
    min_symbol.push_back(a);
}

/// Register a new "/" operation to the computing graph
/// :param #1 : operation name
void mytensorflow::div_register(string a)
{
    auto it = find(div_symbol.begin(), div_symbol.end(), a);
    assert(it == div_symbol.end());
    div_symbol.push_back(a);
}

void mytensorflow::variable(string a)
{
    auto it = find(var_list.begin(), var_list.end(), a);
    assert(it == var_list.end());
    var_list.push_back(a);
}

/// Register a new tensor which is a pair of nodes to the computing graph
/// :param #1 : node1 name
/// :param #2 : node2 name
void mytensorflow::tensor(string a, string b)
{
    auto it = find(tensor_list.begin(), tensor_list.end(), pair<string, string>(a,b));
    assert(it == tensor_list.end());
    tensor_list.push_back(pair<string, string>(a,b));
}

/// Register a new input value to the computing graph
/// :param #1 : input value in string
/// :param #2 : input name
void mytensorflow::constant(string a, string b)
{
    auto it = find(constant_list.begin(), constant_list.end(), pair<string, string>(a,b));
    assert(it == constant_list.end());
    constant_list.push_back(pair<string, string>(a,b));
}


