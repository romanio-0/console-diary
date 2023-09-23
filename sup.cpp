#include "sup.h"

bool validDay(int day, int month, int year) {
    if (month < 8) {
        if (month == 2) {
            if (year % 4 == 0 || (year % 100 == 0 && year % 400 == 0)) {
                if (day <= 29)
                    return true;
            } else {
                if (day <= 28)
                    return true;
            }
        } else if (month % 2 == 1) {
            if (day <= 31)
                return true;
        } else {
            if (day <= 30)
                return true;
        }
    } else {
        if (month % 2 == 0) {
            if (day <= 31)
                return true;
        } else {
            if (day <= 30)
                return true;
        }
    }

    return false;
}

Date readConsDate() {
    Date date;
    bool errBoll = true;
    int checkData = 0;
    std::string consRead;

    while (errBoll) {
        try {
            while (true) {
                std::cout << "Year - " << std::endl;
                std::getline(std::cin, consRead);
                checkData = std::stoi(consRead);
                consRead.clear();
                if (checkData < 2999 && checkData > 1900) {
                    date.year = checkData;
                    break;
                } else {
                    std::cout << "Not valid year!" << std::endl;
                }
            }

            while (true) {
                std::cout << "Month - " << std::endl;
                std::getline(std::cin, consRead);
                checkData = std::stoi(consRead);
                consRead.clear();
                if (checkData <= 12 && checkData > 0) {
                    date.month = checkData;
                    break;
                } else {
                    std::cout << "Not valid month!" << std::endl;
                }
            }

            while (true) {
                std::cout << "Day - " << std::endl;
                std::getline(std::cin, consRead);
                checkData = std::stoi(consRead);
                consRead.clear();
                if (validDay(checkData, date.month, date.year)) {
                    date.day = checkData;
                    break;
                } else {
                    std::cout << "Not valid day!" << std::endl;
                }
            }

            errBoll = false;
        } catch (std::invalid_argument &ex) {
            std::cout << "Еnter correct data!" << std::endl;
        }
    }
    return date;
}

Event addEvent() {
    Event event;

    std::cout << "Enter the end date of the event" << std::endl;

    event.expires = readConsDate();

    std::cout << "Write a description: ";
    std::getline(std::cin, event.description);

    std::time_t t = std::time(nullptr);
    std::tm *now = std::localtime(&t);

    event.created.day = now->tm_mday;
    event.created.month = now->tm_mon + 1;
    event.created.year = now->tm_year + 1900;
    event.created.hour = now->tm_hour;
    event.created.minutes = now->tm_min;

    return event;
}

Birthday addBirthday() {
    Birthday birthday;

    std::cout << "Enter date of birth" << std::endl;

    birthday.date = readConsDate();

    std::cout << "Write Surname Name Patronymic: ";

    std::cin >> birthday.full_name.surname;
    std::cin >> birthday.full_name.name;
    std::cin >> birthday.full_name.patronymic;
    // на всякий отчищаем буффер
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return birthday;
}

bool checkRepeatBirthday(std::list<Birthday> const &listBirthday, Birthday const &birthday) {
    for (Birthday const &it: listBirthday) {
        if (it.date.day == birthday.date.day &&
            it.date.month == birthday.date.month &&
            it.date.year == birthday.date.year) {
            if (it.full_name.name == birthday.full_name.name &&
                it.full_name.surname == birthday.full_name.surname &&
                it.full_name.patronymic == birthday.full_name.patronymic) {
                return true;
            }
        }
    }
    return false;
}

void outBirthday(std::list<Birthday> const &listBirthday) {
    std::cout << "----------\nDate\t\tFIO" << std::endl;

    for (Birthday const &it: listBirthday) {
        std::cout << it.date.day << '.' << it.date.month << '.' << it.date.year << '\t'
                  << it.full_name.surname << ' ' << it.full_name.name << ' ' << it.full_name.patronymic
                  << std::endl;
    }

    std::cout << "----------" <<std::endl;
}

void outEvent(std::list<Event> const &listEvent) {
    std::cout << "----------\nExpires\t\tCreate\t\t Description" << std::endl;

    for (Event const &it: listEvent) {
        std::cout << it.expires.day << '.' << it.expires.month << '.' << it.expires.year << '\t'
                  << it.created.day << '.' << it.created.month << '.' << it.created.year << ' '
                  << (int)it.created.hour << ':' << (int)it.created.minutes << "\t "
                  << it.description << std::endl;
    }
    std::cout << "----------" <<std::endl;
    std::cout << std::endl;
}