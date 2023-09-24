#ifndef _FILESAVE_H_
#define _FILESAVE_H_

#include "sup.h"
#include <fstream>
#include <string.h>

#define NAME_FILE_DATA "data.bin"

#define EVENT_FILE -2
#define BIRTHDAY_FILE -3

//для более безопасной передачи списков (можно было бы и не использовать)
struct GetListEvBr{
    std::list<Event> listEvent;
    std::list<Birthday> listBirthday;
};

/**
 * записывает данные в текстовый файл
 */
bool saveInFile(std::list<Event> const &listEvent, std::list<Birthday> const &listBirthday, std::string path);

/**
 * функция для записи в файл структуры Event в существующий поток
 */
void writeEvent(Event const& event, std::ofstream &file);
/**
 * функция для записи в файл структуры Event
 */
bool writeEvent(Event const& event);

/**
 * функция для записи в файл структуры Birthday в существующий поток
 */
void writeBirthday(Birthday const& birthday, std::ofstream &file);
/**
 * функция для записи в файл структуры Birthday
 */
bool writeBirthday(Birthday const& birthday);

/**
 * функция для записи в файл структур Event и Birthday
 * (файл перезаписывается)
 */
bool writeFileData(std::list<Event> const &listEvent, std::list<Birthday> const &listBirthday);

/**
 * функция для чтения структуры Event из файла, из существующего потока
 */
void readEvent(Event & event, std::ifstream &file);

/**
 * функция для чтения структуры Birthday из файла, из существующего потока
 */
void readBirthday(Birthday & birthday, std::ifstream &file);

/**
 * функция для считывания структур Event и Birthday из файла
 */
GetListEvBr readFileData();

#endif //_FILESAVE_H_
