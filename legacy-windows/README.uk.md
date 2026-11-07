# Старі проєкти лише для Windows

[English](README.md) | **Українська**

Ці проєкти використовують Windows API або Windows Forms (C++/CLI), тому збираються лише у **Visual Studio на Windows**.
Вони *не* входять у збірку CMake і перевірку GitHub Actions.

| Папка | Що це | Як зібрати |
|---|---|---|
| [winapi-conchoid](winapi-conchoid) | Вікно Win32, що малює криву конхоїду (консоль + вікно GDI) | відкрийте `ConchoidWindow.sln` |
| [winapi-two-windows](winapi-two-windows) | Розширена версія: два вікна з різними графіками | відкрийте `TwoWindows.sln` |
| [futkeeper-winforms](futkeeper-winforms) | Застосунок Windows Forms «Futkeeper»: меню (створити / відкрити користувача, налаштування, про програму), таблиця й список користувачів | відкрийте `Futkeeper.sln` |
| [sort-prog-winforms](sort-prog-winforms) | Інтерфейс Windows Forms для алгоритмів сортування (самі алгоритми - у [projects/sorting-algorithms](../projects/sorting-algorithms)) | відкрийте `SortProg.sln` |

## Вимоги
- Visual Studio 2019 або новіша, робоче навантаження **Desktop development with C++**.
- Обидва проєкти WinForms також потребують компонента **C++/CLI support** (вкладка Individual components).
- Visual Studio запропонує *Retarget* рішення на встановлений набір інструментів - натисніть OK.

## Примітки
- Вихідні файли в UTF-8 з BOM (раніше були у Windows-1251), тому Visual Studio правильно показує кириличні коментарі.
- Проєкти `winapi-*` перейменовано з `ConsoleApplication2` / `Lb2_11_1`.
