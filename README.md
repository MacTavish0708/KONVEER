Микроконтроллер управления конвеерной линией
============================================
Область применения
------------------

Есть конвейер, в котором задаётся количество товара, которое надо отгрузить. 
Есть датчик, который считает сколько товара уже прошло. 
Требовалось чтобы микроконтроллер имел кнопки для добавления/уменьшения количества отгружаемых штук товара; для запуска и для остановки электродвигателя; табло, которое показывает сколько осталось отгрузить. Работа алгоритма по струтурной схеме:



![Структурная схема](/strukturnaya_ishodnik.png "Структурная схема")



Схема подключения выводов к микроконтроллеру STM32F103C8T6
----------------------------------------------------------


![текст](/Schematic_konveer_2021-05-16.png "Схема")


К выводу PA0 приходит сигнал о прохождения через ИК-светодиод и ИК-фотодиод предмета который запускает счетчик количества пройденных предметов. Питание для светодида и фотодиода 3,3В. Резисторы 47 Ом и 1 МОМ согласно схеме подключанияю


К выводам PA10,PA11,PA12 подключаются выводы U3,U1,U2 соотвественно с частотного преобразователя Toshiba VF-AS3. По схеме:



![Схема подключения к частотнику](/strukturnaya_ishodnik.png "Схема подключения к частотнику")



![Сигнал для частотника](/signal_chastotnik.png "Сигнал для частотника")



Семисегментные индикаторы подключаются ко всем остальным свободеым выходам и и настравиваются в коде инициализации GPIO в пункте обозначинном комментарием led.


Кнопки настройки количества предметов на конвеерной линии(больше/меньше), запуска ковеерной линии, остановки конвеерной линии подключаются к выводам PA8,PA9,PC13CPC14,PC15 соотвественно.


Алгоритм работы кода
====================
из чего состоит код
1. иницилизация тактирования
2. инициализация используемых портов (инициализация портов под кнопки, инициализация портов под светодиоы, настройка АЦП, инициализация портов для управления двигателем) 
3. подключение необходимых библиотек
4. прописание функций 
5. пропись основного тела программы 
6. пропись основного цикла

основной алгоритм
1. начало -> 2 пункт
2. проверка состояний кнопок "+" и "-" -> 3 пункт
3. вводим число в счетчик отгружаемого груза  -> 4 пункт
4. отображение на индикаторе количества введенноного отгружаемого груза -> 5 пункт
5. если нажата кнопка "Установка" -> 6 пункт
/ если нет -> 2 пункт
6. индикатор мигает 3 раза, сигнализируя о переходе в режим отгрузки груза -> 7 пункт  
7. проверка состояния кнопок "пуск" и "останов" -> 8 пункт
8. нажимаем кнопку "пуск" -> 9 пункт
9. на частотный преобразователь подается сигнал о запуске асинхронного двигателя -> 10 пункт
10. асинхронный двигатель двигает конвеерную ленту -> 11 пункт
11. груз проходит через фотодатчик -> 12 пункт
12. уменьшение числа в счетчике отгруженного груза -> 13 пункт
13. отображаение на индикторе сколько осталось отгрузить груза -> 14 пункт
14. проверка отгрузился ли весь груз, если да -> 15 пункт
/ если нет -> 10 пункт
15. была нажата кнопка "останов" -> 16 пункт
16. на частотный преобразователь подается сигнал об остановке двигателя -> 17 пункт
17. МК переходит в исхоное состояние -> 2 пункт
18. конец


Источники для большего понимания
================================

[про частотника к асинхронному двигаетлю](http://engio.ru/index/vstraivaemyie-sistemyi/upravlyaem-asinxronnyim-dvigatelem-s-pomoshhyu-mikrokontrollera-stm32-i-preobrazovatelya-chastotyi.html)



[про подключение семисегментника](https://diodov.net/semisegmentnyj-indikator-programmirovanie-mikrokontrollerov/#:~:text=%D0%9F%D1%80%D0%B8%D0%BD%D1%86%D0%B8%D0%BF%20%D1%80%D0%B0%D0%B1%D0%BE%D1%82%D1%8B%20%D1%81%D0%B5%D0%BC%D0%B8%D1%81%D0%B5%D0%B3%D0%BC%D0%B5%D0%BD%D1%82%D0%BD%D0%BE%D0%B3%D0%BE%20%D0%B8%D0%BD%D0%B4%D0%B8%D0%BA%D0%B0%D1%82%D0%BE%D1%80%D0%B0,%D0%9E%D1%82%D1%81%D1%8E%D0%B4%D0%B0%20%D0%B8%20%D0%BF%D1%80%D0%BE%D0%B8%D1%81%D1%85%D0%BE%D0%B4%D0%B8%D1%82%20%D0%B5%D0%B3%D0%BE%20%D0%BD%D0%B0%D0%B7%D0%B2%D0%B0%D0%BD%D0%B8%D0%B5.&text=%D0%92%D0%BD%D0%B5%20%D0%B7%D0%B0%D0%B2%D0%B8%D1%81%D0%B8%D0%BC%D0%BE%D1%81%D1%82%D0%B8%20%D0%BE%D1%82%20%D0%BA%D0%BE%D0%BB%D0%B8%D1%87%D0%B5%D1%81%D1%82%D0%B2%D0%B0%20%D1%80%D0%B0%D0%B7%D1%80%D1%8F%D0%B4%D0%BE%D0%B2,%2C%20e%2C%20f%2C%20g)



[про подключение фотодиода](http://electrik.info/main/praktika/1347-kak-primenyat-fotorezistory-fotodiody-i-fototranzistory.html#i2)
