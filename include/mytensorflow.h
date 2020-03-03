#ifndef MYTENSORFLOW_H
#define MYTENSORFLOW_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cassert>

using namespace std;

class mytensorflow
{
    friend class tf_parser;
    public:
        mytensorflow();
        virtual ~mytensorflow();
        void add_register(std::string a);
        void mul_register(std::string a);
        void min_register(std::string a);
        void div_register(std::string a);
        void variable(std::string a);
        void tensor(std::string a, std::string b);
        void constant(string a, std::string b);

    protected:
        vector<std::string> add_symbol;
        vector<std::string> mul_symbol;
        vector<std::string> min_symbol;
        vector<std::string> div_symbol;
        vector<std::string> var_list;
        vector<pair<string, string>> tensor_list;
        vector<pair<string, string>> constant_list;

    private:
};

#endif // MYTENSORFLOW_H
