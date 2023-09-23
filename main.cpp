#include "sup.h"
#include "fileSave.h"

#include <iostream>
#include <list>

using namespace std;

#define SORT_DATA_OCCURRENCE '1'
#define SORT_NAME '2'
#define SORT_DATA_CREATE '3'

void sortAndPrint(list<Event> listEvent, list<Birthday> listBirthday, char mode){
    switch (mode) {
        case SORT_DATA_OCCURRENCE:
            listBirthday.sort([](Birthday const &a, Birthday const &b) {
                if (a.date.year < b.date.year)
                    return true;
                else if (a.date.year > b.date.year)
                    return false;
                else if (a.date.month < b.date.month)
                    return true;
                else if (a.date.month > b.date.month)
                    return false;
                else
                    return a.date.day < b.date.day;
            });
            listEvent.sort([](Event const &a, Event const &b) {
                if (a.expires.year < b.expires.year)
                    return true;
                else if (a.expires.year > b.expires.year)
                    return false;
                else if (a.expires.month < b.expires.month)
                    return true;
                else if (a.expires.month > b.expires.month)
                    return false;
                else
                    return a.expires.day < b.expires.day;
            });

            outBirthday(listBirthday);
            outEvent(listEvent);
            break;
        case SORT_NAME:
            listBirthday.sort([](Birthday const &a, Birthday const &b) {
                if (a.full_name.surname < b.full_name.surname)
                    return true;
                else if (a.full_name.surname > b.full_name.surname)
                    return false;
                else if (a.full_name.name < b.full_name.name)
                    return true;
                else if (a.full_name.name > b.full_name.name)
                    return false;
                else
                    return a.full_name.patronymic < b.full_name.patronymic;
            });

            outBirthday(listBirthday);
            break;
        case SORT_DATA_CREATE:
            listEvent.sort([](Event const &a, Event const &b) {
                if (a.created.year < b.created.year)
                    return true;
                else if (a.created.year > b.created.year)
                    return false;
                else if (a.created.month < b.created.month)
                    return true;
                else if (a.created.month > b.created.month)
                    return false;
                else if (a.created.day < b.created.day)
                    return true;
                else if (a.created.day > b.created.day)
                    return false;
                else if (a.created.hour < b.created.hour)
                    return true;
                else
                    return a.created.minutes < b.created.minutes;
            });

            outEvent(listEvent);
            break;
        default:
            cout << "Enter valid value" << endl;
    }
}

int main() {
    list<Event> listEvent;
    list<Birthday> listBirthday;

    readFileData(listEvent, listBirthday);

    bool status = true;
    string consRead;
    Birthday tmpCheckBirthday;


    // работает пока пользователь не введете "0"
    while (status) {
        cout << "Commands:\n[1] - Add | [2] - Request | [0] - Exit" << endl;
        consRead.clear();
        getline(cin, consRead);

        switch (consRead[0]) {
            case '0':
                // пересохроняет все данные на случай ошибки или удаления данных
                while (true) {
                    if (!writeFileData(listEvent, listBirthday)) {
                        cout << "Error save data in file\n[1] - Exit | [2] - Repeat" << endl;
                        consRead.clear();
                        getline(cin, consRead);

                        if (consRead[0] == '1')
                            break;
                        else
                            continue;
                    }
                    cout << "Save!" << endl;
                    break;
                }

                status = false;
                break;
            case '1':
                cout << "Add:\n[1] - Event | [2] - Birthday" << endl;
                consRead.clear();
                getline(cin, consRead);

                switch (consRead[0]) {
                    case '1':
                        listEvent.push_back(addEvent());

                        // save
                        writeEvent(listEvent.back());
                        break;
                    case '2':
                        while (true) {
                            tmpCheckBirthday = addBirthday();
                            if (!checkRepeatBirthday(listBirthday, tmpCheckBirthday)) {
                                break;
                            }
                            cout << "This person is already on the list" << endl;
                        }
                        listBirthday.push_back(tmpCheckBirthday);

                        //save
                        writeBirthday(tmpCheckBirthday);
                        break;
                    default:
                        cout << "Enter valid value" << endl;
                }
                break;
            case '2':
                cout << "How to sort the data?\n[1] - date of occurrence | [2] - Name | [3] - date create" << endl;
                consRead.clear();
                getline(cin, consRead);

                // сортирует списки и выводит нужные данные
                sortAndPrint(listEvent, listBirthday, consRead[0]);

                break;
            default:
                cout << "Enter valid value" << endl;
        }
    }


    return 0;
}
