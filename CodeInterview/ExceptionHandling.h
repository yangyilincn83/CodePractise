#pragma once

#include <exception>
#include <iostream>

using namespace std;

namespace CPlusPlus
{
    class DataFormatException : public exception
    {
    public:
        DataFormatException(const char* const msg) : exception(msg)
        {
        }
    };

    class NetworkIOException : public exception
    {
    public:
        NetworkIOException(const char* const msg) : exception(msg)
        {
        }
    };

    void FunctionThrowingException(const char* type, const char* msg)
    {
        if (0 == _strcmpi(type, "DataFormat"))
        {
            throw DataFormatException(msg);
        }

        if (0 == _strcmpi(type, "NetworkIO"))
        {
            throw NetworkIOException(msg);
        }

        if (0 == _strcmpi(type, "ErrorCode"))
        {
            throw 500;
        }

        throw exception();
    }

    void ExceptionTest()
    {
        try {
            // FunctionThrowingException("DataFormat", "Data Format Error");
            // FunctionThrowingException("NetworkIO", "Network IO Error");
            // FunctionThrowingException("ErrorCode", nullptr);
            FunctionThrowingException("ErrorCode", nullptr);
        }
        catch (const DataFormatException& dfe)
        {
            // If the parameter of the catch - clause is a reference type, any changes made to it are reflected in the exception object, and can be observed by another handler if the exception is rethrown with throw.
            // If the parameter is not a reference, any changes made to it are are local and its lifetime ends when the handler exits.
            cout << dfe.what() << endl;
        }
        catch (const NetworkIOException& nioe)
        {
            cout << nioe.what() << endl;
        }
        catch (const int& errorCode)
        {
            cout << "Error code: " << errorCode << endl;
        }
        catch (...)
        {
            throw;
        }
    }

    void NoThrowNewTest()
    {
        std::cout << "Attempting to allocate 1 MB...";
        char* p = new (std::nothrow) char[1048576];
        if (p == 0)
        {
            std::cout << "Failed!\n";
        }
        else
        {
            std::cout << "Succeeded!\n";
            delete[] p;
        }

    }
}