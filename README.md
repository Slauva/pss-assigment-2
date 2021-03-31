# Hacker Attack System

> A simple console application designed to demonstrate the operation of standard systems in a university environment for both students and professors.

[![Status](https://img.shields.io/badge/status-active-success.svg)]()
[![Build Status][travis-image]][travis-url]
[![Downloads Stats][npm-downloads]][npm-url]
[![GitHub Pull Requests](https://img.shields.io/github/issues-pr/kylelobo/The-Documentation-Compendium.svg)](https://github.com/Slauva/pss-assigment-2/pulls)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](/LICENSE)

![](header.jpg)

## 📝 Table of Contents

-   [About](#about)
-   [Dependence & System](#dep)
-   [Development setup](#dev)
-   [Classes](#class)
    -   [Calendar](#calendar)
    -   [Asset](#asset)
    -   [Environment](#env)
-   [Custom users](#users)
-   [Meta](#meta)
-   [Contributing](#contr)

## 🎈 About <a name="about"></a>

A simple console application designed to demonstrate the operation of standard systems in a university environment for both students and professors. It implements such systems as: database, calendar, user editor, access system. Also, a hacker has crept into the projects with whom you will have to play games your system is at stake, but if you win it, you may find out what's new for yourself.

## 🚀 Development setup <a name="dev"></a>

The MakeFile collector is installed in the project. In order to build the file, you need to write in the console

```cmd
make
start output/main.exe
```

## ⛏️ Dependence & System <a name="dep"></a>

-   [Cpp](https://github.com/nlohmann/json) - c++17
-   [Json](https://github.com/nlohmann/json) - Json for modern C++

## ✍️ Classes <a name="class"></a>

Description of classes and their methods

### **class** Calendar <a name="calendar"></a>

This object is responsible for recording events, comparing them by date and rooms where they will be held.

```cpp
class Calendar {
    public:
    Calendar(std::string);
    bool reservation(std::string, int, std::string, std::string, std::string);
    bool remove(std::string, int, std::string);
    void print();
    void save();
    void load();
    ~Calendar();
};
```

### Function **Calendar::Reservation()**

**Responsible for writing data to an array.**
**It accepts 5 values ​​as input:**

```cpp
    string label   // Name of event
    int room       // Room number
    string date    // Date in format(dd/mm/yyyy)
    string from    // Time from in format(hh:mm)
    string to      // Time to in format(hh:mm)
    return bool    // If it turned out to be written, the function will return true, otherwise false
```

### Function **Calendar::Remove()**

**Responsible for removing data from an array.**
**It accepts 3 values ​​as input:**

```cpp
    string label   // Name of event
    int room       // Room number
    string date    // Date in format(dd/mm/yyyy)
    return bool    // If it succeeded to delete, then the function will return true, otherwise false
```

### Functions **Calendar::save()** & **Calendar::load()**

**Write and read data from a json file.**

```json
{
    "12/08/1980" : {
        "Room Number" : [
            {"Label1" : ["Time from", "Time to"]},
        ],
        "110" : [
            {"Math exam" : ["12:00", "14:00"]},
            {"Poker club" : ["15:00", "16:00"]},
            {"Dance" : ["17:00", "18:00"]}
        ],
        ...
    },
    ...
}
```

### **class** Asset <a name="asset"></a>

This object is engaged in storing data about the user, access level.

```cpp
class Asset {
   public:
    User data;
    Info::Post post;
    Info::Access_Level level;
    std::string email;

    Asset(User data, Info::Post post, Info::Access_Level level, std::string email, std::string password);
    Asset(Info::Post, Info::Access_Level);
    ~Asset() { save(); };

    int getId() { return this->id; };
    void save();
    static Asset* load(std::string email, std::string password);

   private:
    int password;
    int id;
};
```

### Function **Asset::load()**

**Loads user data from json file into class object.**
**It accepts 2 values ​​as input:**

```cpp
    string email       // User email
    string password    // User password
```

### Function **Asset::save()**

**Saves user data to json file from class object.**

```json
{
    "Access": {
        "Access Level": 0,
        "Post": 0
    },
    "Auth": {
        "Email": "n.smith@innopolis.univesrity",
        "Id": 123456789,
        "Password": 123456789 // Hashcode of password
    },
    "User": {
        "Age": 18,
        "Appartment": "1-203",
        "Name": "Nikolas",
        "Sex": "Male",
        "Surname": "Smith",
        "Type": "Cute"
    }
}
```

### **class** Environment <a name="env"></a>

The main class is where all the manipulation of objects takes place.

```cpp
class Environment {
   public:
    Environment(std::string);
    void auth(int);
    void create();
    static std::string info(std::string);
    static std::string error(std::string);
    static std::string debug(std::string);
    static std::string custom(std::string, std::string);

    Asset* system_user;
    std::string name;

    int* class_room;
    int* labs;
    int* lecture_room;
    int* conference_room;
    int* profesor_cabinet;
    int director_cabinet;

    void print_rooms();
    void print_users();
    void red_button();
    void terminated();
    void move_out(std::string);
    void drop(std::string);
    void create_exam();
    void new_lessen();
    void open(int);

    bool access_check(int, int);
};
```

### Function **Environment::auth()**

**User authentication in the system.**

### Function **Environment::create()**

**Create user in the system.**

### Function **Environment::info()**, **Environment::debug()**, **Environment::error()**, **Environment::custom()**

**Functions that return the edited line for output to the terminal, with flags as in the logs, are intended to inform the user in various situations. There is also a custom function to which a decorative flag can be passed.**

```cmd
[INFO]      Main information
[DEBUG]     Debug information
[ERROR]     Error information
[CUSTOM]    Custom information
```

### Function **Environment::print_rooms()**

**Display of all cabinets and their types.**

### Function **Environment::print_users()**

**Display of all users and their information in table.**

### Function **Environment::drop()**

**Removing users from the database.**

### Function **Environment::move_out()**

**Eviction of the user from his apartment.**

### Function **Environment::create_exam()**, **Environment::new_lessen()**

**Responsible for writing data to an array.**
**It accepts 5 values ​​as input:**

```cpp
    string label   // Name of Exam or Lessen
    int room       // Room number
    string date    // Date in format(dd/mm/yyyy)
    string from    // Time from in format(hh:mm)
    string to      // Time to in format(hh:mm)
    return bool    // If it turned out to be written, the function will return true, otherwise false
```

### Function **Environment::open()**

**Open audience.**

### Function **Environment::red_button()**

**The red button makes you a god in the system, it removes all users except you. So let's say - a change of government.**

### Function **Environment::terminated()**

**Deleting the entire project with one button, just don't delete the whole game on the first day.**

## Custom Users <a name="users"></a>

### Admin account

```txt
> login: k.pavlov@innopolis.university
> Password: 12345
```

### Student account

```txt
> Login: a.dermov@innopolis.university
> Password: 12345
```

## Meta <a name="meta"></a>

Slava Koshman – [@jack_koshman](https://www.instagram.com/jack_koshman/) – main-app@yandex.ru

[https://github.com/Slauva](https://github.com/Slauva/)

## Contributing <a name="contr"></a>

1. Fork it (<https://github.com/Slauva/pss-assigment-2/fork>)
2. Create your feature branch (`git checkout -b feature/fooBar`)
3. Commit your changes (`git commit -am 'Add some fooBar'`)
4. Push to the branch (`git push origin feature/fooBar`)
5. Create a new Pull Request

<!-- Markdown link & img dfn's -->

[npm-image]: https://img.shields.io/npm/v/datadog-metrics.svg?style=flat-square
[npm-url]: https://npmjs.org/package/datadog-metrics
[npm-downloads]: https://img.shields.io/npm/dm/datadog-metrics.svg?style=flat-square
[travis-image]: https://img.shields.io/travis/dbader/node-datadog-metrics/master.svg?style=flat-square
[travis-url]: https://travis-ci.org/dbader/node-datadog-metrics
[wiki]: https://github.com/Slauva/pss-assigment-2/wiki
