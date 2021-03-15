#include <iostream>
using namespace std;
#include "LibrarySystem.h"

int main(){
    LibrarySystem LS;
    LS.addBook(1100, "On origins of universe", 2011);
    LS.addBook(120, "How to Be Sheldon", 2001);
    LS.addBook(13007, "Academic Writing With Python", 1996);
    LS.addBook(14005, "C++ and Airplanes", 2005);
    LS.addBook(1225, "War and Peace", 1867);
    LS.addBook(1405, "Deep Learning", 1990);
    LS.addBook(1225, "Intro to Photoshop", 2001);

    cout << endl;
    cout << "addBook Test1 over" << endl;
    cout << endl;

    LS.deleteBook(13007);
    LS.deleteBook(14099);
    LS.addBook(13007, "Programming with Python", 2000);

    cout << endl;
    cout << "deleteBook Test1, addBook Test2 over" << endl;
    cout << endl;

    LS.addStudent(21000000, "Pierre Bezukhov");
    LS.addStudent(21000011, "Natasha Rostova");
    LS.addStudent(210012, "Andrei Bolkonsky");
    LS.addStudent(2100002, "Nikolai Rostov");
    LS.addStudent(2100002, "Anatole Kuragin");
    LS.addStudent(215000005, "Helene Kuragin");

    LS.deleteStudent(210012);
    LS.addStudent(210012, "Mikhail Kutuzov");

    cout << endl;
    cout << "addStudent Test1, deleteStudent Test1 over" << endl;
    cout << endl;

    LS.checkoutBook(120, 21000000);
    LS.checkoutBook(1225, 21000000);
    LS.checkoutBook(1405, 21000011);
    LS.checkoutBook(13007, 21000444);

    cout << endl;
    cout << "chekoutBook Test1 over" << endl;
    cout << endl;

    LS.showStudent(21000000);
    cout << endl;
    LS.showStudent(21000011);
    cout << endl;
    LS.showStudent(2100002);

    cout << endl;
    LS.showBook(120);
    LS.showBook(130007);

    cout << endl;
    LS.showAllBooks();

    cout << endl;
    cout << "showStudent Test1, showBook Test1, showAllBooks Test1 over" << endl;
    cout << endl;

    cout << endl;
    LS.returnBook(120);
    LS.checkoutBook(120, 21000011);

    cout << endl;
    LS.showAllBooks();
    cout << endl;
    LS.deleteStudent(21000011);
    cout << endl;
    LS.deleteBook(21000011);
    cout << endl;

    LS.showAllBooks();
    cout << endl;


    return 0;
}
