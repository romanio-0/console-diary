#ifndef _FILESAVE_H_
#define _FILESAVE_H_

#include "sup.h"
#include <fstream>

#define NAME_FILE_DATA "data.bin"

#define EVENT_FILE -2
#define BIRTHDAY_FILE -3

/**
 * функция для записи в файл структуры Event в существующий поток
 */
void writeEvent(Event const& event, std::fstream &file);
/**
 * функция для записи в файл структуры Event
 */
bool writeEvent(Event const& event);

/**
 * функция для записи в файл структуры Birthday в существующий поток
 */
void writeBirthday(Birthday const& birthday, std::fstream &file);
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
 * функция для считывания структур Event и Birthday из файла
 */
void readFileData(std::list<Event> &listEvent, std::list<Birthday> &listBirthday);

#endif //_FILESAVE_H_
