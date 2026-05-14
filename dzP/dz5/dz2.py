# Исходные данные о документах
documents = [
    {'type': 'passport', 'number': '2207 876234', 'name': 'Василий Гупкин', 'shelf': 1},
    {'type': 'invoice', 'number': '11-2', 'name': 'Тенадий Покемонова', 'shelf': 1},
    {'type': 'insurance', 'number': '10006', 'name': 'Аристарх Павлов', 'shelf': 2}
]

# Исходный перечень полок
shelves = [1, 2, 3]

# Функция для поиска владельца по номеру документа
def find_owner(documents, doc_number):
    for doc in documents:
        if doc['number'] == doc_number:
            return doc['name']
    return "Документ не найден"

# Функция для поиска полки по номеру документа
def find_shelf(documents, doc_number):
    for doc in documents:
        if doc['number'] == doc_number:
            return doc['shelf']
    return "Документ не найден"

# Функция для добавления нового документа
def add_document(documents, doc_type, doc_number, owner, shelf):
    documents.append({'type': doc_type, 'number': doc_number, 'name': owner, 'shelf': shelf})

# Функция для вывода всей информации по документам
def print_all_documents(documents):
    if not documents:
        print("Документы не найдены.")
    else:
        for doc in documents:
            print(f"№: {doc['number']}, тип: {doc['type']}, владелец: {doc['name']}, полка хранения: {doc['shelf']}")

# Функция для добавления новой полки
def add_shelf(shelves, shelf_number):
    if shelf_number not in shelves:
        shelves.append(shelf_number)
        print(f"Полка добавлена. Текущий перечень полок: {sorted(shelves)}")
    else:
        print(f"Такая полка уже существует. Текущий перечень полок: {sorted(shelves)}")

# Функция для удаления существующей полки
def remove_shelf(shelves, shelf_number):
    if shelf_number in shelves:
        shelves.remove(shelf_number)
        print(f"Полка удалена. Текущий перечень полок: {sorted(shelves)}")
    else:
        print(f"Такой полки не существует. Текущий перечень полок: {sorted(shelves)}")

# Основной цикл программы
while True:

    command = input("Введите команду: ").lower()

    if command == 'q':  # Выход из программы
        print("Завершаем программу.")
        break
    
    elif command == 'p':  # Поиск владельца по номеру документа
        doc_number = input("Введите номер документа: ")
        print(f"Владелец документа: {find_owner(documents, doc_number)}")

    elif command == 's':  # Поиск полки по номеру документа
        doc_number = input("Введите номер документа: ")
        print(f"Документ хранится на полке: {find_shelf(documents, doc_number)}")

    elif command == 'l':  # Вывод всей информации по документам
        print_all_documents(documents)

    elif command == 'ads':  # Добавление новой полки
        shelf_number = int(input("Введите номер полки: "))
        add_shelf(shelves, shelf_number)

    elif command == 'ds':  # Удаление полки
        shelf_number = int(input("Введите номер полки: "))
        remove_shelf(shelves, shelf_number)

    else:
        print("Неверная команда. Повторите ввод.")