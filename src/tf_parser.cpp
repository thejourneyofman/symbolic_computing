#include "tf_parser.h"
#include "mytensorflow.h"

/// Constructor
/// :param mytensorflow :a mytensorflow instance.
tf_parser::tf_parser(mytensorflow mytf):tf(mytf)
{
    //ctor
}

/// Destructor
tf_parser::~tf_parser()
{
    //dtor
}

/// String split function
/// :param s : original string
/// :param sv : a vector to store the sub strings
/// :param sep : the separator char
void tf_parser::split(const string& s,vector<string>& sv,const char sep = ' ') {
    sv.clear();
    istringstream iss(s);
    string temp;

    while (getline(iss, temp, sep)) {
        sv.push_back(temp);
    }
    return;
}

/// Register a callback function for a "+" operation
/// :param #1 : operation name
void tf_parser::add_callback(function<void(string)> cb)
{
    add_callback_ = cb;
}

/// Register a callback function for a "*" operation
/// :param #1 : operation name
void tf_parser::mul_callback(function<void(string)> cb)
{
    mul_callback_ = cb;
}

/// Register a callback function for a "-" operation
/// :param #1 : operation name
void tf_parser::min_callback(function<void(string)> cb)
{
    min_callback_ = cb;
}

/// Register a callback function for a "/" operation
/// :param #1 : operation name
void tf_parser::div_callback(function<void(string)> cb)
{
    div_callback_ = cb;
}

/// Register a callback function for input variables
/// :param #1 : the counts of the input variables
void tf_parser::input_callback(function<void(int)> cb)
{
    input_callback_ = cb;
}

/// Register a callback function for each edge in the computing graph variables
/// :param #1 : the input name
/// :param #2 : the input index
/// :param #3 : the output name
/// :param #4 : the output index
void tf_parser::connection_callback(function<void(string, string, string, string)> cb)
{
    connection_callback_ = cb;
}

/// Register a callback function for each constant values for the inputs
/// :param #1 : always "input"
/// :param #2 : the input index
/// :param #3 : value in string
void tf_parser::value_callback(function<void(string, string, string)> cb)
{
    value_callback_ = cb;
}

/// Run the parsing and call all the callbacks registered.
void tf_parser::run()
{
    // handle the expected number of units
    for (size_t i = 0; i < tf.add_symbol.size(); i++)
    {
        if (add_callback_)
            add_callback_(tf.add_symbol[i]);
    }

    for (size_t i = 0; i < tf.mul_symbol.size(); i++)
    {
        if (mul_callback_)
            mul_callback_(tf.mul_symbol[i]);
    }

    for (size_t i = 0; i < tf.min_symbol.size(); i++)
    {
        if (min_callback_)
            min_callback_(tf.min_symbol[i]);
    }

    for (size_t i = 0; i < tf.div_symbol.size(); i++)
    {
        if (div_callback_)
            div_callback_(tf.div_symbol[i]);

    }

    if (input_callback_)
        input_callback_(tf.var_list.size());

    for (size_t i = 0; i < tf.tensor_list.size(); i++)
    {
        string from = tf.tensor_list[i].first;
        string to = tf.tensor_list[i].second;
        assert(from != "result");
        vector<string> from_strs;
        split(from, from_strs, '_');
        assert(from_strs.size() >= 1);
        vector<string> to_strs;
        split(to, to_strs, '_');
        assert(to_strs.size() >= 1);

        string inputName = from_strs[0];
        // the first parameter is from_strs[0]
        string inputIndex = from_strs[0] == "input" ? from_strs[1] : "";
        string outputName = to_strs[0];

        string outputIndex = "";
        if (to_strs[0] != "result")
        {
            outputIndex = to_strs[1];
        }

        if (connection_callback_)
            connection_callback_(inputName, inputIndex, outputName, outputIndex);

    }

    for (size_t i = 0; i < tf.constant_list.size(); i++)
    {
        vector<string> strs;
        split(tf.constant_list[i].second, strs, '_');
        assert(strs.size() == 2);
        if (value_callback_)
            value_callback_(strs[0], strs[1], tf.constant_list[i].first);

    }
}
