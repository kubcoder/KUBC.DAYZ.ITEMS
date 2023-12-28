# KUBC.DAYZ.ITEMS
Серверный мод для игры [DAYZ SA](https://dayz.com/) для работы с игровыми предметами. Для работы мода необходимо подключить серверный мод [KUBC.DAYZ.CONSOLE](https://github.com/kubcoder/KUBC.DAYZ.CONSOLE)

**[Подробное описание на сайте разработчика](https://kubcoder.ru/dayz/items)**


# Инструменты
Для разработки мода используется редактор [VS Code](https://code.visualstudio.com/). Для тестов используется не упакованый мод со стороны сервера.
В рабочем пространстве проекта добавлены инструменты для сборки мода, и запуска сервера с подключенным модом:
- **Clear Server Logs** Выполнить очистку логов сервера
- **Start Server** Запустить сервер DAYZ с собранным модом
- **Start Test Server** Запустить тестовый сервер с очисткой логов
Для выполнения данных команд, в VS Code нажимаем `Shift+Ctrl+P`, далее вводим `Tasks: Run Task` и выбираем из списка одну из команд рабочего пространства.

Для того что бы сервер работал с модом, необходимо в папке сервера создать связь с папкой где находятся исходники мода. Создать связь можно с помощью команды [mklink](https://learn.microsoft.com/ru-ru/windows-server/administration/windows-commands/mklink)

# Журнал версий

## 2.0 (28.12.2023)
Работает [справочник игровых предметов](https://kubcoder.ru/dayz/items/dictionary)

Добавлены [команды](https://kubcoder.ru/dayz/items/cmd/index):
- [spawn](https://kubcoder.ru/dayz/items/cmd/spawn) создать игровой предмет
- [box](https://kubcoder.ru/dayz/items/cmd/box) создать ящик игровых предметов
- [del](https://kubcoder.ru/dayz/items/cmd/del)  удалить игровой предмет
- [save](https://kubcoder.ru/dayz/items/cmd/save) сохранить набор игровых предметов
- [get](https://kubcoder.ru/dayz/items/cmd/get) выдать набор игровых предметов
- [car](https://kubcoder.ru/dayz/items/cmd/car) команда сохранения/создания и обслуживания транспортных средств
- [equip](https://kubcoder.ru/dayz/items/cmd/equip) команда сохранения/создания экипировки игрока
- [repair](https://kubcoder.ru/dayz/items/cmd/repair) команда "ремонта" игровых предметов
