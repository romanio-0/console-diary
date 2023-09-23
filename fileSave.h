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
void readFileData(std::list<Event> &listEvent, std::list<Birthday> &listBirthday);

#endif //_FILESAVE_H_
