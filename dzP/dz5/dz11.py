import re

def domain_distribution(emails):
    # создаем словарь для подсчета доменных зон
    dic = {}
    
    # проходим по каждому email
    for email in emails:
        domain = email.split('@')[1]  # извлекаем доменную зону
        if domain not in dic:
            dic[domain] = 1  # если домен не найден, добавляем его с счетчиком 1
        else:
            dic[domain] += 1  # если домен уже есть, увеличиваем счетчик
    
    # выводим результат
    for k, v in dic.items():
        print(f'{k} {v}')

# Пример использования
emails = ['test@gmail.com', 'xyz@test.in', 'test@mail.ru', 'xyz@ya.ru', 'xyz@gmail.com']
domain_distribution(emails)