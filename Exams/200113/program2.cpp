#include <vector>
#include <string>
#include <sstream>
#include <iostream>

class Option
{
public:
    Option(std::string name) : name{name} {};

    // We need virtual destructor since this has a virtual function parse()
    // that will be overloaded
    virtual ~Option() = default;

    // Delete copy constructor and assignment
    Option(Option const &) = delete;
    Option &operator=(Option const &) = delete;

    virtual bool parse(std::string const &arg) = 0;
    virtual void print(std::ostream &os) const
    {
        os << name;
    };

protected:
    std::string name;
};

class Flag : public Option
{
public:
    Flag(std::string name, bool &present) : Option{name}, present{present}
    {
        present = false;
    };

    bool parse(std::string const &arg) override
    {
        return present = arg == name;
    }

    void print(std::ostream &os) const override
    {
        os << "[";
        Option::print(os);
        os << "]";
    }

private:
    bool &present;
};

template <typename T>
class Argument : public Option
{
public:
    Argument(std::string name, T &target) : Option{name}, target{target} {};

    // When inheriting from Option we don't need to delete
    // copy constructor / assignment since we already did in Option. @Solution

    bool parse(std::string const &arg) override
    {
        std::istringstream iss{arg};
        iss >> target;
        return !iss.fail();
    }

private:
    T &target;
};

class Parser
{
public:
    ~Parser()
    {
        for (Option *option : options)
            delete option;
    }

    //Parser(Parser &) = delete; // It wont compile with this deleted for some reason
    Parser &operator=(Parser &) = delete;

    void add(Option *option)
    {
        options.push_back(option);
    };

    bool parse(std::vector<std::string> const &args);
    void print(std::ostream &os, std::string const &program) const;

private:
    std::vector<Option *> options{};
};

/* This function is an implementation for the parse function of the
   Parser class. You will have to include this implementation as a
   member function in the Parser class.

   The goal of this function is to match each option in the options
   vector with an argument from the args vector (i.e. parse the
   arguments).

   In this simplified framework the position of each argument and flag
   matters. Example:
   
   In main we create a parser that has two flags: -a, and --b-flag as
   well as two arguments: int and string. The following cases are allowed:

   ./a.out -a --b-flag 5 hello
   ./a.out -a 5 hello
   ./a.out --b-flag 5 hello
   ./a.out 5 hello

   While cases such as:

   ./a.out 5 -a hello
   ./a.out 5 hello --b-flag
   ./a.out --b-flag -a 5 hello

   are not. Meaning that the order is important, if the -a flag is
   present it must be the first argument, and if --b-flag is present
   it must come before the int argument. The int and string arguments
   must be given in order. This is because we parse each option in the
   same order as they appear in the options vector. Flags can be
   skipped but the order must still be preserved.

   The parse function already deals with this case but you have to
   complete the implementation by replacing the comments with actual
   code.
 */
bool Parser::parse(std::vector<std::string> const &args)
{
    if (args.empty())
    {
        std::cerr << "No arguments given." << std::endl;
        return false;
    }

    int i{0};
    for (Option *option : options)
    {
        if (i < args.size())
        {
            if (option->parse(args[i]))
            {
                ++i;
            }
            else if (dynamic_cast<Flag *>(option) == nullptr)
            {
                std::cerr << "Unknown argument: " << args[i] << std::endl;
                return false;
            }
        }
        else if (dynamic_cast<Flag *>(option) == nullptr)
        {
            std::cerr << "Too few arguments" << std::endl;
            return false;
        }
    }

    if (i < args.size())
    {
        std::cerr << "Too many arguments." << std::endl;
        return false;
    }

    return true;
}

/* print algorithm for Parser */
void Parser::print(std::ostream &os, std::string const &program) const
{
    os << "Usage: " << program;
    for (Option *option : options)
    {
        os << " ";
        option->print(os);
    }
    os << std::endl;
}

/*

  Example of usage:

$ ./a.out 
No arguments given.
Usage: ./a.out [-a] [--b-flag] int string

$ ./a.out -a 5
Too few arguments
Usage: ./a.out [-a] [--b-flag] int string

$ ./a.out -a hello
Unknown argument: hello
Usage: ./a.out [-a] [--b-flag] int string

$ ./a.out --b-flag -a 5 hello
Unknown argument: -a
Usage: ./a.out [-a] [--b-flag] int string

$ ./a.out -a 5 hello
a == 1
b == 0
num == 5
str == hello

$ ./a.out -a --b-flag 5 hello
a == 1
b == 1
num == 5
str == hello

 */
int main(int argc, char **argv)
{
    std::vector<std::string> args{argv + 1, argv + argc};
    Parser p{};

    bool a{};
    p.add(new Flag{"-a", a});

    bool b{};
    p.add(new Flag{"--b-flag", b});

    int num{};
    p.add(new Argument<int>{"int", num});

    std::string str{};
    p.add(new Argument<std::string>{"string", str});

    if (!p.parse(args))
    {
        p.print(std::cerr, argv[0]);
    }
    else
    {
        std::cout << "a == " << a << std::endl
                  << "b == " << b << std::endl
                  << "num == " << num << std::endl
                  << "str == " << str << std::endl;
    }
}
