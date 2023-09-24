#ifndef _STRUCTURES_H_
#define _STRUCTURES_H_

#include <iostream>
#include <cstdint>
#include <list>
#include <ctime>
#include <chrono>
#include <limits>
#include <thread>
#include <mutex>

struct FIO {
    std::string surname;
    std::string name;
    std::string patronymic;
};

struct Date {
    uint16_t day;
    uint16_t month;
    uint16_t year;
};

struct DateTime {
    Date date;
    uint8_t hour;
    uint8_t minutes;
};

struct Event {
    DateTime created; // Дата создания: ДД.ММ.ГГГГ + часы и минуты в числовом формате в структуре
    Date expires; // Дата окончания: ДД.ММ.ГГГГ в числовом формате в структуре
    std::string description; // Описание
};

struct Birthday {
    int age;
    Date date; // Дата окончания: ДД.ММ.ГГГГ в числовом формате в структуре
    FIO full_name; // Структура с тремя строками: ФИО
};

/**
 * функция запрацивающая у пользователя данные об Событии
 * @return Возвращает заполненную структуру Event
 */
Event addEvent();

/**
 * функция запрацивающая у пользователя данные об Дне рождении
 * @return Возвращает заполненную структуру Birthday
 */
Birthday addBirthday();

/**
 * функция проверяет существует уже такой день рождения или нет
 */
bool checkRepeatBirthday(std::list<Birthday> const &listBirthday, Birthday const &birthday);

/**
 * выводит на консоль список Дней рождения, так же присутсвует фильтр вывода
 */
void outBirthday(std::list<Birthday> const &listBirthday, bool (*filter)(Birthday) = nullptr);

/**
 * выводит на консоль список Событий, так же присутсвует фильтр вывода
 */
void outEvent(std::list<Event> const &listEvent, bool (*filter)(Event) = nullptr);

/**
 * выводит События которые наступают сегодня
 */
void outNowEvent(std::list<Event> const &listEvent, std::list<Birthday> const &listBirthday);


#endif //_STRUCTURES_H_