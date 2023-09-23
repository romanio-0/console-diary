#include "sup.h"
#include "fileSave.h"

#include <iostream>
#include <list>
#include <vector>

using namespace std;

#define SORT_DATA_OCCURRENCE '1'
#define SORT_NAME '2'
#define SORT_DATA_CREATE '3'

void sortAndPrint(list<Event> listEvent, list<Birthday> listBirthday, char mode) {
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
                else if (a.created.hour > b.created.hour)
                    return false;
                else
                    return a.created.minutes < b.created.minutes;
            });

            outEvent(listEvent);
            break;
        default:
            break;
    }
}

void clearData(list<Event> &listEvent, list<Birthday> &listBirthday){
    listEvent.clear();
    listBirthday.clear();

    remove(NAME_FILE_DATA);
}

void checkEvBr(list<Event> &listEvent, list<Birthday> &listBirthday) {
    time_t timeT;
    tm *pTm;
    chrono::system_clock::time_point timePoint;
    chrono::system_clock::duration durationTime;

    while (true) {
        //узнаем сколько осталось до окончания события
        timeT = chrono::system_clock::to_time_t(chrono::system_clock::now());
        pTm = localtime(&timeT);
        pTm->tm_hour = 23;
        pTm->tm_min = 59;
        pTm->tm_sec = 59;

        timePoint = chrono::system_clock::from_time_t(mktime(pTm));
        durationTime = timePoint - chrono::system_clock::now();

        //ждем конца
        this_thread::sleep_for(chrono::microseconds(chrono::duration_cast<chrono::microseconds>(durationTime)));

        auto itemEvent = listEvent.cbegin();
        for (size_t i = 0; i < listEvent.size(); ++i, ++itemEvent) {
            if (itemEvent->expires.year == pTm->tm_year + 1900 &&
                itemEvent->expires.month == pTm->tm_mon + 1 &&
                itemEvent->expires.day == pTm->tm_mday) {

                listEvent.erase(itemEvent);
            }
        }

        // если код выполнится быстрее чем за секунду и день не успеет сменится
        this_thread::sleep_for(chrono::microseconds(1001));

        //узнаем сколько осталось до дня рождения
        timeT = chrono::system_clock::to_time_t(chrono::system_clock::now());
        pTm = localtime(&timeT);
        pTm->tm_hour = 00;
        pTm->tm_min = 01;
        pTm->tm_sec = 00;

        timePoint = chrono::system_clock::from_time_t(mktime(pTm));
        durationTime = timePoint - chrono::system_clock::now();

        //ждем
        this_thread::sleep_for(chrono::microseconds(chrono::duration_cast<chrono::microseconds>(durationTime)));

        auto itemBirthday = listBirthday.begin();
        for (size_t i = 0; i < listEvent.size(); ++i, ++itemBirthday) {
            if (itemBirthday->date.month == pTm->tm_mon + 1 &&
                itemBirthday->date.day == pTm->tm_mday) {

                itemBirthday->age++;
            }
        }

        //записываем изменения
        writeFileData(listEvent, listBirthday);
    }
}

int main(void) {
    list<Event> listEvent;
    list<Birthday> listBirthday;

    readFileData(listEvent, listBirthday);

    bool status = true;
    string consRead;
    Birthday tmpCheckBirthday;

    // поток отслеживания события
    thread threadEvent(checkEvBr, ref(listEvent), ref(listBirthday));

    // работает пока пользователь не введете "0"
    while (status) {
        cout << "Commands:\n[1] - Add | [2] - Request | [3] - Save | [4] - All Delete | [0] - Exit" << endl;
        consRead.clear();
        getline(cin, consRead);

        switch (consRead[0]) {
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
                cout << "How to sort the data?\n[1] - date of occurrence | [2] - Name | [3] - date create | [4] - Today"
                     << endl;
                consRead.clear();
                getline(cin, consRead);

                switch (consRead[0]) {
                    case '1':
                    case '2':
                    case '3':
                        // сортирует списки и выводит нужные данные
                        sortAndPrint(listEvent, listBirthday, consRead[0]);
                        break;
                    case '4':
                        // выводит события которые происходят сегодня
                        outNowEvent(listEvent, listBirthday);
                        break;
                    default:
                        cout << "Enter valid value" << endl;
                }

                break;
            case '3':
                cout << "Write path:";
                consRead.clear();
                getline(cin, consRead);

                if (!saveInFile(listEvent, listBirthday, consRead)) {
                    cout << "Error open file" << endl;
                    break;
                }
                cout << "Save in file" << endl;
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
            case '4':
                cout << "You are sure?\n[1] - Yes | [2] - No" << endl;
                consRead.clear();
                getline(cin, consRead);

                if (consRead[0] == '1'){
                    clearData(listEvent, listBirthday);
                }

                break;
            default:
                cout << "Enter valid value" << endl;
        }
    }

    threadEvent.detach();
    return 0;
}
