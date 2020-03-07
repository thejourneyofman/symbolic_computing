#ifndef TF_PARSER_H
#define TF_PARSER_H

#include <memory>
#include <cstring>
#include <sstream>
#include "mytensorflow.h"

using namespace std;

class tf_parser
{
    public:
        tf_parser(mytensorflow);
        virtual ~tf_parser();
        void add_callback(function<void(string)> cb);
        void mul_callback(function<void(string)> cb);
        void min_callback(function<void(string)> cb);
        void div_callback(function<void(string)> cb);
        void input_callback(function<void(int)> cb);
        void connection_callback(function<void(string, string, string, string)> cb);
        void value_callback(function<void(string, string, string)> cb);
        void run();

    protected:

    private:
        mytensorflow tf;
        function<void(string)> add_callback_;
        function<void(string)> mul_callback_;
        function<void(string)> min_callback_;
        function<void(string)> div_callback_;
        function<void(int n)> input_callback_;
        function<void(string, string, string, string)> connection_callback_;
        function<void(string, string, string)> value_callback_;
        void split(const string& s,vector<string>& sv,const char sep);
};

#endif // TF_PARSER_H
