#include <iostream>
#include <vector>

using namespace std;

int main (void) {
    vector<int> v1;

    //* Capacity
    // Each iteration inserts i to the last position
    for (int i = 0; i < 7; ++i)
        v1.push_back(i);
    
    cout << "Size:      " << v1.size() << endl; 
    cout << "Capacity:  " << v1.capacity() << endl;
    cout << "Max Size:  " << v1.max_size() << endl;
    

    //* Iterators begin(), end()
    // Iterators are used to point at the memory addresses of STL containers.
    cout << "Vector content (begin to end): ";
    if (true == v1.empty())
        cout << "empty" << endl;
    else {
        // begin(): Returns an iterator pointing to the first element in the vector
        for (auto i = v1.begin(); i != v1.end(); ++i)
            cout << *i <<  " ";
        cout << endl;

        cout << "Vector content (end to begin): ";
        for (auto ir = v1.rbegin(); ir != v1.rend(); ++ir)
            cout << *ir << " ";
        cout << endl;
    }

    // For efficiency purposes, but the else part is just an example, Not logicly yes.
    if (v1.capacity() - v1.size() > 0)
        v1.push_back(7);
    else
        v1.resize(v1.size() * 2);

    //* Element access: front(), back(), [], at()
    cout << "\nAddress of the Vector: " << v1.data() << endl;
    cout << "First element: " << v1.front() << endl;
    cout << "Last element : " << v1.back() << endl;

    cout << "Vector: ";
    for (int i = 0; i < v1.size(); ++i)
        cout << v1[i] << " ";
    cout << endl;


    // Modifiers
    vector<int> v2;

    // Fill the vector with 10 5 times
    v2.assign(5, 10);

    v2.emplace(v2.begin(), 17);
    cout << "First element is " << v2[0] << endl;

    v2.emplace_back(12);
    cout << "Last element is " << v2[v2.size() - 1] << endl;


    // Push & Pop
    v2.pop_back();

    v2.erase(v2.begin());

    for (unsigned int i = 0; i < v2.size(); ++i)
        cout << v2[i] << endl;

    v2.clear();
    cout << "Vector size after clear : " << v2.size() << endl;
}