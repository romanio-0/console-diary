#include "sup.h"

#include <iostream>
#include <fstream>
#include <list>

#define EVENT_FILE -2
#define BIRTHDAY_FILE -3

using namespace std;

bool writeFileData(list<Event> const &listEvent, list<Birthday> const &listBirthday) {
    ofstream file("data.bin", ios::binary | ios::out);
    if (!file.is_open()) {
        return false;
    }

    char tmp;

    for (Event it: listEvent) {
        tmp = EVENT_FILE;
        file.write(&tmp, 1);

        file.write((char *) (&it.created), sizeof(it.created));
        file.write((char *) (&it.expires), sizeof(it.expires));
        file.write(it.description.c_str(), it.description.size() + 1);
    }


    for (Birthday it: listBirthday) {
        tmp = BIRTHDAY_FILE;
        file.write(&tmp, 1);

        file.write((char *) (&it.date), sizeof(it.date));
        file.write(it.full_name.surname.c_str(), it.full_name.surname.size() + 1);
        file.write(it.full_name.name.c_str(), it.full_name.name.size() + 1);
        file.write(it.full_name.patronymic.c_str(), it.full_name.patronymic.size() + 1);
    }

    /*tmp = EOF;
    file.write(&tmp, 1);*/

    file.close();
    return true;
}

void readFileData(list<Event> &listEvent, list<Birthday> &listBirthday) {
    ifstream file("data.bin", ios::binary | ios::in);
    if (!file.is_open()) {
        return;
    }

    Event tmpEvent;
    Birthday tmpBirthday;
    char tmp;

    while (true) {
        file.get(tmp);

        if (tmp == EOF) {
            break;

        } else if (tmp == EVENT_FILE) {
            file.read((char *) (&tmpEvent.created), sizeof(tmpEvent.created));
            file.read((char *) (&tmpEvent.expires), sizeof(tmpEvent.expires));
            do {
                file.get(tmp);
                tmpEvent.description.push_back(tmp);
            } while (tmp != '\0');

            listEvent.push_back(tmpEvent);
        } else if (tmp == BIRTHDAY_FILE) {
            file.read((char *) (&tmpBirthday.date), sizeof(tmpBirthday.date));
            do {
                file.get(tmp);
                tmpBirthday.full_name.surname.push_back(tmp);
            } while (tmp != '\0');
            do {
                file.get(tmp);
                tmpBirthday.full_name.name.push_back(tmp);
            } while (tmp != '\0');
            do {
                file.get(tmp);
                tmpBirthday.full_name.patronymic.push_back(tmp);
            } while (tmp != '\0');

            listBirthday.push_back(tmpBirthday);
        }
    }

    file.close();
}

int main() {
    list<Event> listEvent;
    list<Birthday> listBirthday;

    readFileData(listEvent, listBirthday);

    bool status = true;
    string consRead;
    Birthday tmpCheck;


    // работает пока пользователь не введете "0"
    while (status) {
        cout << "Commands:\n[1] - Add | [2] - Request | [0] - Exit and Save" << endl;
        consRead.clear();
        getline(cin, consRead);

        switch (consRead[0]) {
            case '0':
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
                        break;
                    case '2':
                        while (true) {
                            tmpCheck = addBirthday();
                            if (!checkRepeatBirthday(listBirthday, tmpCheck)) {
                                break;
                            }
                            cout << "This person is already on the list" << endl;
                        }
                        listBirthday.push_back(tmpCheck);
                        break;
                    default:
                        cout << "Enter valid value" << endl;
                }
                break;
            case '2':
                cout << "How to sort the data?\n[1] - date of occurrence | [2] - Name | [3] - date create" << endl;
                consRead.clear();
                getline(cin, consRead);

                switch (consRead[0]) {
                    case '1':
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
                    case '2':
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
                    case '3':
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
                break;
            default:
                cout << "Enter valid value" << endl;
        }
    }


    return 0;
}
