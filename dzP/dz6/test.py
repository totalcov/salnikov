import json

# 1. Создыю словарь для хранения покупок {user_id: category}
purchases = {}

# Читаю файл с покупками и наполняем словарь
with open('dzP\dz6\purchase_log.txt', 'r', encoding='utf-8') as f:
    for line in f:
        # Превращаем строку JSON в обычный словарь Python
        dict_row = json.loads(line)
        # Сохраняем: ключ — id пользователя, значение — категория
        purchases[dict_row['user_id']] = dict_row['category']


with open('dzP\dz6\visit_log.csv', 'r', encoding='utf-8') as f_visits:
    with open('dzP\dz6\funnel.csv', 'w', encoding='utf-8') as f_out:
        for line in f_visits:
            # Убираем лишние  и разбиваем строку по запятой
            row = line.strip().split(',')
            user_id = row[0]
            source = row[1]
            
            # Проверяе сть ли этот пользователь среди покупателей
            if user_id in purchases:
                category = purchases[user_id]
                # строку для записи: id, источник, категория
                new_line = f'{user_id},{source},{category}\n'
                f_out.write(new_line)

print("Файл funnel.csv успешно создан!")