queries = [
    'смотреть сериалы онлайн',
    'новости спорта',
    'афиша кино',
    'курс доллара',
    'сериалы этим летом',
    'курс по питону',
    'сериалы про спорт'
]


count_words = {}

for query in queries:

    words_count = len(query.split())

    count_words[words_count] = count_words.get(words_count, 0) + 1

total_queries = len(queries)

for words in sorted(count_words.keys()):
    percentage = (count_words[words] / total_queries) * 100
    print(f"Поисковых запросов, содержащих {words} слова: {percentage:.2f}%")