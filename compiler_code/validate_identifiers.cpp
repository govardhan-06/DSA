#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Structure for Quadruple
struct Quad
{
    string op, arg1, arg2, result;
};

// Structure for Triple
struct Triple
{
    string op, arg1, arg2;
};

// Function to display Quadruples
void showQuad(const vector<Quad> &q)
{
    cout << "\nQuadruple Representation\n";
    cout << "Idx\tOp\tArg1\tArg2\tResult\n";
    for (int i = 0; i < q.size(); i++)
        cout << i << "\t" << q[i].op << "\t"
             << q[i].arg1 << "\t"
             << q[i].arg2 << "\t"
             << q[i].result << endl;
}

// Function to display Triples
void showTriple(const vector<Triple> &t)
{
    cout << "\nTriple Representation\n";
    cout << "Idx\tOp\tArg1\tArg2\n";
    for (int i = 0; i < t.size(); i++)
        cout << i << "\t" << t[i].op << "\t"
             << t[i].arg1 << "\t"
             << t[i].arg2 << endl;
}

// Function to display Indirect Triples
void showIndirect(const vector<int> &ind)
{
    cout << "\nIndirect Triple Representation\n";
    cout << "Pointer -> Instruction Index\n";
    for (int i = 0; i < ind.size(); i++)
        cout << i << " -> (" << ind[i] << ")\n";
}

// Simple Backpatching function
void backpatch(const vector<int> &list, int target)
{
    for (int i = 0; i < list.size(); i++)
        cout << "Instruction " << list[i]
             << " patched with target " << target << endl;
}

int main()
{
    // Predefined Three Address Code statements
    vector<Quad> quad = {
        {"*", "4", "i", "S1"},
        {"=[]", "x", "S1", "S2"},
        {"*", "4", "j", "S3"},
        {"=[]", "y", "S3", "S4"},
        {"*", "S2", "S4", "S5"},
        {"+", "result", "S5", "S6"},
        {"=", "S6", "-", "result"},
        {"+", "j", "1", "S7"},
        {"=", "S7", "-", "j"},
        {"if<=", "j", "10", "3"},
        {"+", "i", "1", "S8"},
        {"=", "S8", "-", "i"},
        {"if<=", "i", "20", "1"}};

    // Convert Quadruples to Triples
    vector<Triple> triple;
    for (int i = 0; i < quad.size(); i++)
        triple.push_back({quad[i].op, quad[i].arg1, quad[i].arg2});

    // Indirect Triple (pointer table)
    vector<int> indirect;
    for (int i = 0; i < triple.size(); i++)
        indirect.push_back(i);

    // Display all representations
    showQuad(quad);
    showTriple(triple);
    showIndirect(indirect);

    // ---------------- Backpatching Example ----------------
    cout << "\nBackpatching Example\n";

    // Example true and false lists
    vector<int> trueList = {9};   // Instruction index for true jump
    vector<int> falseList = {12}; // Instruction index for false jump

    backpatch(trueList, 3);   // Patch true condition to instruction 3
    backpatch(falseList, 13); // Patch false condition to next instruction

    return 0;
}