# 1. Функция сложения
def add_numbers(a, b):
    return a + b


# 2. Функция нахождения большего числа
def get_max(a, b):
    return max(a, b)


# 3. Функция проверки на четность
def is_even(number):
    return number % 2 == 0


# 4. Функция возведения в квадрат
def square_number(number):
    return number ** 2


# 5. Функция, которая вызывает другие функции
def number_info(number1, number2):
    total = add_numbers(number1, number2)     # вызов 1 функции
    bigger = get_max(number1, number2)        # вызов 2 функции
    square = square_number(bigger)            # вызов 3 функции
    even_check = is_even(total)               # вызов 4 функции

    return total, bigger, square, even_check


# Проверка работы программы
print("Сумма:", add_numbers(4, 6))
print("Большее число:", get_max(4, 6))
print("Четное ли число 10:", is_even(10))
print("Квадрат числа 5:", square_number(5))

result = number_info(4, 6)
print("Результат функции number_info:", result)