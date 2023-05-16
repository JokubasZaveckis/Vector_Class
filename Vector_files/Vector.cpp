#include "ManoVektorius.h"
#include "Header.h"


int main() {

    //Pirma dalis
    MyVector<int> myVector;
    vector<int> stdVector;

    myVector.reserve(100);
    stdVector.reserve(200);

    myVector.push_back(1);
    myVector.push_back(2);
    myVector.push_back(3);
    myVector.push_back(4);
    myVector.push_back(5);

    cout << "Mano vektorius: ";
    for (auto i : myVector)
    {
        cout << i << " ";
    }
    cout << endl;

    stdVector.push_back(1);
    stdVector.push_back(2);
    stdVector.push_back(3);
    stdVector.push_back(4);
    stdVector.push_back(5);


    cout << "Std vektorius: ";
    for (auto i : stdVector)
    {
        cout << i << " ";
    }
    cout << endl;

    cout << "MyVector dydis: " << myVector.size() << endl;
    cout << "StdVector dydis: " << stdVector.size() << endl;

    cout << "MyVector capacity: " << myVector.capacity() << endl;
    cout << "StdVector capacity: " << stdVector.capacity() << endl;

    cout << "MyVector empty: " << myVector.empty() << endl;
    cout << "StdVector empty: " << stdVector.empty() << endl;

    cout << "MyVector max size: " << myVector.max_size() << endl;
    cout << "StdVector max size: " << stdVector.max_size() << endl;

    cout << "MyVector front: " << myVector.front() << endl;
    cout << "StdVector front: " << stdVector.front() << endl;

    cout << "MyVector back: " << myVector.back() << endl;
    cout << "StdVector back: " << stdVector.back() << endl;

    cout << "MyVector at 3: " << myVector.at(3) << endl;
    cout << "StdVector at 3: " << stdVector.at(3) << endl;

    myVector.pop_back();

    cout << "Mano vektorius: ";
    for (auto i : myVector)
    {
        cout << i << " ";
    }
    cout << endl;

    stdVector.pop_back();

    cout << "Std vektorius: ";
    for (auto i : stdVector)
    {
        cout << i << " ";
    }
    cout << endl;

    myVector.shrink_to_fit();
    stdVector.shrink_to_fit();

    cout << "MyVector capacity: " << myVector.capacity() << endl;
    cout << "StdVector capacity: " << stdVector.capacity() << endl;

    myVector.clear();
    stdVector.clear();

    //Antra dalis
    cout << endl << "=======================================" << endl;

    long int size = 100000000;

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < size; i++)
    {
        myVector.push_back(i);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    cout << "Mano vektoriaus uzpildymas " << size << " elementu uztruko: " << duration << "ms" << endl;

    auto start1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < size; i++)
    {
        stdVector.push_back(i);
    }
    auto end1 = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1).count();
    cout << "Std vektoriaus uzpildymas " << size << " elementu uztruko: " << duration1 << "ms" << endl;

    myVector.clear();
    stdVector.clear();

   
    //Trecia dalis
    cout << endl << "=======================================" << endl;

    MyVector<int> manoVektorius;
    vector<int> stdVektorius;

    int dydis = 100000000;
    int mano = 0, std = 0;
    for (int i = 0; i < dydis; i++)
    {
        if (manoVektorius.capacity() == manoVektorius.size())
        {
            mano++;
        }
        manoVektorius.push_back(i);
    }

    for (int i = 0; i < dydis; i++)
    {
        if (stdVektorius.capacity() == stdVektorius.size())
        {
            std++;
        }
        stdVektorius.push_back(i);
    }

    cout << "Mano vektoriaus perskirstymai: " << mano << endl;
    cout << "Std vektoriaus perskirstymai: " << std << endl;

    myVector.clear();
    stdVector.clear();

    return 0;
}
