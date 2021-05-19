#pragma once

using namespace std;

class CDatabaseInitException : public runtime_error
{
public:
    explicit CDatabaseInitException(const string &message) : runtime_error(message) {}
};

class CInputParameterException : public runtime_error
{
public:
    explicit CInputParameterException(const string &message) : runtime_error(message) {}
};