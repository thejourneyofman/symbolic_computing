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
        void add_register(string a);
        void mul_register(string a);
        void min_register(string a);
        void div_register(string a);
        void variable(string a);
        void tensor(string a, string b);
        void constant(string a, string b);

    protected:
        vector<string> add_symbol;
        vector<string> mul_symbol;
        vector<string> min_symbol;
        vector<string> div_symbol;
        vector<string> var_list;
        vector<pair<string, string>> tensor_list;
        vector<pair<string, string>> constant_list;

    private:
};

#endif // MYTENSORFLOW_H
