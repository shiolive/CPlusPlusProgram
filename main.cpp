#include <Python.h>
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>


    using namespace std;

    void CallProcedure(string pName)
    {
        char *procname = new char[pName.length() + 1];
        std::strcpy(procname, pName.c_str());

        Py_Initialize();
        PyRun_SimpleString("import sys");
        PyRun_SimpleString("import os");
        PyRun_SimpleString("sys.path.append(os.getcwd())");
        PyObject* my_module = PyImport_ImportModule("python_modules.PythonCode");
        PyErr_Print();
        PyObject* my_function = PyObject_GetAttrString(my_module, procname);
        PyObject* my_result = PyObject_CallObject(my_function, NULL);
        Py_Finalize();

        delete[] procname;
    }

    int callIntFunc(string proc, string param)
    {
        char *procname = new char[proc.length() + 1];
        std::strcpy(procname, proc.c_str());

        char *paramval = new char[param.length() + 1];
        std::strcpy(paramval, param.c_str());


        PyObject *pName, *pModule, *pDict, *pFunc, *pValue = nullptr, *presult = nullptr;
        // Initialize the Python Interpreter
        Py_Initialize();
        // Build the name object
        PyRun_SimpleString("import sys");
        PyRun_SimpleString("import os");
        PyRun_SimpleString("sys.path.append(os.getcwd())");
        pName = PyUnicode_FromString((char*)"python_modules.PythonCode");
        // Load the module object
        pModule = PyImport_Import(pName);
        // pDict is a borrowed reference
        pDict = PyModule_GetDict(pModule);
        // pFunc is also a borrowed reference
        pFunc = PyDict_GetItemString(pDict, procname);
        if (PyCallable_Check(pFunc))
        {
            pValue = Py_BuildValue("(z)", paramval);
            PyErr_Print();
            presult = PyObject_CallObject(pFunc, pValue);
            PyErr_Print();
        }
        else
        {
            PyErr_Print();
        }
        //printf("Result is %d\n", _PyLong_AsInt(presult));
        Py_DECREF(pValue);
        // Clean up
        Py_DECREF(pModule);
        Py_DECREF(pName);
        // Finish the Python Interpreter
        Py_Finalize();

        // clean
        delete[] procname;
        delete[] paramval;


        return _PyLong_AsInt(presult);
    }

    int callIntFunc(string proc, int param)
    {
        char *procname = new char[proc.length() + 1];
        std::strcpy(procname, proc.c_str());

        PyObject *pName, *pModule, *pDict, *pFunc, *pValue = nullptr, *presult = nullptr;
        // Initialize the Python Interpreter
        Py_Initialize();
        // Build the name object
        PyRun_SimpleString("import sys");
        PyRun_SimpleString("import os");
        PyRun_SimpleString("sys.path.append(os.getcwd())");
        pName = PyUnicode_FromString((char*)"python_modules.PythonCode");
        // Load the module object
        pModule = PyImport_Import(pName);
        // pDict is a borrowed reference
        pDict = PyModule_GetDict(pModule);
        // pFunc is also a borrowed reference
        pFunc = PyDict_GetItemString(pDict, procname);
        if (PyCallable_Check(pFunc))
        {
            pValue = Py_BuildValue("(i)", param);
            PyErr_Print();
            presult = PyObject_CallObject(pFunc, pValue);
            PyErr_Print();
        }
        else
        {
            PyErr_Print();
        }
        //printf("Result is %d\n", _PyLong_AsInt(presult));
        Py_DECREF(pValue);
        // Clean up
        Py_DECREF(pModule);
        Py_DECREF(pName);
        // Finish the Python Interpreter
        Py_Finalize();

        // clean
        delete[] procname;

        return _PyLong_AsInt(presult);
    }

    void PrintMenu(){ //display menu output
        cout << "\nPlease enter an option:\n1: View list of all items purchased with purchase frequency\n";
        cout << "2: View purchase frequency of specific item\n";
        cout << "3: Display a histogram to view purchase frequency of each item\n";
        cout << "4: Quit\n \n";

    }
    void DisplayFrequency(){
        string userStr;
        cout << "What item would you like to check?\n";
        cin >> userStr; //get user input and use to call python function for output
        cout << "Purchase Frequency of " << userStr << ": " << callIntFunc("FindFrequency", userStr) << endl;

    }

    void Histogram(){
        ifstream inFS; //create file io stream object
        int frequency;
        string item;

        CallProcedure("FileData"); //call python function to create frequency.dat file
        inFS.open("frequency.dat"); //open newly created file

        if (!inFS.is_open()){ //error checking file open
            cout << "Could not open file frequency.dat";
        }
        else{
            while (!inFS.fail()){ //loop until end of file
            inFS >> item; //input from file into variables
            inFS >> frequency;
            cout << item << " ";
            for (int i=0; i < frequency; ++i){ //loop to output symbol for histogram
                cout << "*";
            }
            cout << endl;

            }
            inFS.close();
        }


    }

    int main()
    {
        int userInput;

        while (userInput != 4){
            PrintMenu();
            cin >> userInput;
            switch(userInput){
                case 1: //option to print all items with purchase frequency
                    CallProcedure("PrintItems");
                    break;
                case 2: //option to display frequency of specific item
                    DisplayFrequency();
                    break;
                case 3: //option to display histogram for all items
                    Histogram();
                    break;
                case 4: //exit program
                    cout << "Exiting program.";
                    break;
                default: //invalid input
                    cout << "Try another option";

            }

        }

    }