#include "fileSave.h"

using namespace std;


void writeEvent(Event const &event, std::ofstream &file){
    char tmp;

    tmp = EVENT_FILE;
    file.write(&tmp, 1);

    file.write((char *) (&event.created), sizeof(event.created));
    file.write((char *) (&event.expires), sizeof(event.expires));
    file.write(event.description.c_str(), event.description.size() + 1);
}

bool writeEvent(Event const& event){
    ofstream file(NAME_FILE_DATA, ios::binary | ios::out | ios::app);
    if (!file.is_open()) {
        return false;
    }

    char tmp;

    tmp = EVENT_FILE;
    file.write(&tmp, 1);

    file.write((char *) (&event.created), sizeof(event.created));
    file.write((char *) (&event.expires), sizeof(event.expires));
    file.write(event.description.c_str(), event.description.size() + 1);

    file.close();
    return true;
}

void writeBirthday(Birthday const& birthday, std::ofstream &file){
    char tmp;

    tmp = BIRTHDAY_FILE;
    file.write(&tmp, 1);

    file.write((char *) (&birthday.date), sizeof(birthday.date));
    file.write(birthday.full_name.surname.c_str(), birthday.full_name.surname.size() + 1);
    file.write(birthday.full_name.name.c_str(), birthday.full_name.name.size() + 1);
    file.write(birthday.full_name.patronymic.c_str(), birthday.full_name.patronymic.size() + 1);
}

bool writeBirthday(Birthday const& birthday){
    ofstream file(NAME_FILE_DATA, ios::binary | ios::out | ios::app);
    if (!file.is_open()) {
        return false;
    }

    char tmp;

    tmp = BIRTHDAY_FILE;
    file.write(&tmp, 1);

    file.write((char *) (&birthday.date), sizeof(birthday.date));
    file.write(birthday.full_name.surname.c_str(), birthday.full_name.surname.size() + 1);
    file.write(birthday.full_name.name.c_str(), birthday.full_name.name.size() + 1);
    file.write(birthday.full_name.patronymic.c_str(), birthday.full_name.patronymic.size() + 1);

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


    for (Birthday it: listBirthday) {
        writeBirthday(it, file);
    }

    file.close();
    return true;
}

void readFileData(list<Event> &listEvent, list<Birthday> &listBirthday) {
    ifstream file(NAME_FILE_DATA, ios::binary | ios::in);
    if (!file.is_open()) {
        return;
    }

    Event tmpEvent;
    Birthday tmpBirthday;
    char tmp;

    while (file.get(tmp)) {

        if (tmp == EVENT_FILE) {
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
