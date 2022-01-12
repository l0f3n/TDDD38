#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <cassert>

using namespace std;

class Printable
{
public:
    virtual ~Printable() = default;
    virtual void print(ostream &os) const = 0;
};

class Serializable
{
public:
    virtual ~Serializable() = default;
    virtual string serialize() const = 0;
    virtual bool deserialize(string) = 0;
};

class Message : public Printable
{
public:
    Message(string msg) : msg{msg} {};
    void print(ostream &os) const override
    {
        os << msg << endl;
    };

private:
    string msg;
};

class Integer : public Printable, public Serializable
{
public:
    Integer(int data) : data{data} {};

    void print(ostream &os) const override
    {
        os << data << endl;
    }

    string serialize() const override
    {
        return to_string(data);
    }

    bool deserialize(string s) override
    {
        try
        {
            data = stoi(s);
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

private:
    int data;
};

vector<string> serialize(vector<Printable *> const &v)
{
    vector<string> result{};
    for (Printable *obj : v)
    {
        if (dynamic_cast<Serializable *>(obj) != nullptr)
        {
            result.push_back(dynamic_cast<Serializable *>(obj)->serialize());
        }
    }
    return result;
}

void print(ostream &os, vector<Printable *> const &v)
{
    for (Printable *obj : v)
    {
        obj->print(os);
    }
}

int main()
{
    vector<Printable *> v = {
        new Message{"Hello there"},
        new Integer{0},
        new Message{"This is a message"},
        new Integer{100053},
        new Integer{-5}};

    {
        vector<string> result{serialize(v)};
        assert((result == vector<string>{"0", "100053", "-5"}));
    }

    {
        ostringstream oss{};
        print(oss, v);
        assert(oss.str() == "Hello there\n0\nThis is a message\n100053\n-5\n");
    }

    {
        Integer i{0};
        assert(i.deserialize("15"));
        assert(i.serialize() == "15");
    }
}
