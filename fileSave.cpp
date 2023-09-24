#include "fileSave.h"

using namespace std;

bool saveInFile(std::list<Event> const &listEvent, std::list<Birthday> const &listBirthday, std::string path) {
    ofstream file(path, ios::out);
    if (!file.is_open()) {
        return false;
    }

    file << "----------\nDate\t\tAge\tFIO\n";

    for (Birthday const &it: listBirthday) {
        file << it.date.day << '.' << it.date.month << '.' << it.date.year << '\t' << it.age << '\t'
             << it.full_name.surname << " " << it.full_name.name << " " << it.full_name.patronymic << '\n';
    }

    file << "----------\n";
    file << "----------\nExpires\t\tCreate\t\t Description\n";

    for (Event const &it: listEvent) {
        file << it.expires.day << '.' << it.expires.month << '.' << it.expires.year << '\t'
             << it.created.date.day << '.' << it.created.date.month << '.' << it.created.date.year << " "
             << (int) it.created.hour << ':' << (int) it.created.minutes << "\t "
             << it.description << '\n';

    }

    file << "----------\n";

    file.close();
    return true;
}

void writeEvent(Event const &event, std::ofstream &file) {
    char tmp;

    tmp = EVENT_FILE;
    file.write(&tmp, 1);

    file.write((char *) (&event.created), sizeof(event.created));
    file.write((char *) (&event.expires), sizeof(event.expires));
    file.write(event.description.c_str(), event.description.size() + 1);
}

bool writeEvent(Event const &event) {
    ofstream file(NAME_FILE_DATA, ios::binary | ios::out | ios::app);
    if (!file.is_open()) {
        return false;
    }

    writeEvent(event, file);

    file.close();
    return true;
}

void writeBirthday(Birthday const &birthday, std::ofstream &file) {
    char tmp;

    tmp = BIRTHDAY_FILE;
    file.write(&tmp, 1);

    file.write((char *) (&birthday.age), sizeof(birthday.age));
    file.write((char *) (&birthday.date), sizeof(birthday.date));
    file.write(birthday.full_name.surname.c_str(), birthday.full_name.surname.size() + 1);
    file.write(birthday.full_name.name.c_str(), birthday.full_name.name.size() + 1);
    file.write(birthday.full_name.patronymic.c_str(), birthday.full_name.patronymic.size() + 1);
}

bool writeBirthday(Birthday const &birthday) {
    ofstream file(NAME_FILE_DATA, ios::binary | ios::out | ios::app);
    if (!file.is_open()) {
        return false;
    }

    writeBirthday(birthday, file);

    file.close();
    return true;
}

bool writeFileData(list<Event> const &listEvent, list<Birthday> const &listBirthday) {
    ofstream file(NAME_FILE_DATA, ios::binary | ios::out);
    if (!file.is_open()) {
        return false;
    }

    for (Event const &it: listEvent) {
        writeEvent(it, file);
    }


    for (Birthday const &it: listBirthday) {
        writeBirthday(it, file);
    }

    file.close();
    return true;
}


void readEvent(Event &event, std::ifstream &file) {
    char tmp;

    file.read((char *) (&event.created), sizeof(event.created));
    file.read((char *) (&event.expires), sizeof(event.expires));
    while (true) {
        file.get(tmp);
        if (tmp == '\0')
            break;

        event.description.push_back(tmp);
    }
}

void readBirthday(Birthday &birthday, std::ifstream &file) {
    char tmp;

    file.read((char *) (&birthday.age), sizeof(birthday.age));
    file.read((char *) (&birthday.date), sizeof(birthday.date));

    while (true) {
        file.get(tmp);
        if (tmp == '\0')
            break;

        birthday.full_name.surname.push_back(tmp);
    }

    while (true) {
        file.get(tmp);
        if (tmp == '\0')
            break;

        birthday.full_name.name.push_back(tmp);
    }

    while (true) {
        file.get(tmp);
        if (tmp == '\0')
            break;

        birthday.full_name.patronymic.push_back(tmp);
    }
}

void readFileData(list<Event> &listEvent, list<Birthday> &listBirthday) {
    ifstream file(NAME_FILE_DATA, ios::binary | ios::in);
    if (!file.is_open()) {
        return;
    }

    Event *tmpEvent = new Event;
    Birthday *tmpBirthday = new Birthday;
    char tmp;

    while (file.get(tmp)) {
        if (tmp == EVENT_FILE) {
            memset((void*)tmpEvent, 0, sizeof(Event));

            readEvent(*tmpEvent, file);
            listEvent.push_back(*tmpEvent);


        } else if (tmp == BIRTHDAY_FILE) {
            memset((void*)tmpBirthday, 0, sizeof(Birthday));

            readBirthday(*tmpBirthday, file);
            listBirthday.push_back(*tmpBirthday);
        }
    }

    delete tmpEvent;
    delete tmpBirthday;

    file.close();
}
