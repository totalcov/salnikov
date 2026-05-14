cook_book = {
    'салат': [
        {'ingredient_name': 'сыр', 'quantity': 50, 'measure': 'гр'},
        {'ingredient_name': 'томаты', 'quantity': 2, 'measure': 'шт'},
        {'ingredient_name': 'огурцы', 'quantity': 20, 'measure': 'гр'},
        {'ingredient_name': 'маслины', 'quantity': 10, 'measure': 'гр'},
        {'ingredient_name': 'оливковое масло', 'quantity': 20, 'measure': 'мл'},
        {'ingredient_name': 'салат', 'quantity': 10, 'measure': 'гр'},
        {'ingredient_name': 'перец', 'quantity': 20, 'measure': 'гр'}
    ],
    'пицца': [
        {'ingredient_name': 'сыр', 'quantity': 20, 'measure': 'гр'},
        {'ingredient_name': 'колбаса', 'quantity': 30, 'measure': 'гр'},
        {'ingredient_name': 'бекон', 'quantity': 30, 'measure': 'гр'},
        {'ingredient_name': 'оливки', 'quantity': 10, 'measure': 'гр'},
        {'ingredient_name': 'томаты', 'quantity': 20, 'measure': 'гр'},
        {'ingredient_name': 'тесто', 'quantity': 100, 'measure': 'гр'}
    ],
    'лимонад': [
        {'ingredient_name': 'лимон', 'quantity': 1, 'measure': 'шт'},
        {'ingredient_name': 'вода', 'quantity': 200, 'measure': 'мл'},
        {'ingredient_name': 'сахар', 'quantity': 10, 'measure': 'гр'},
        {'ingredient_name': 'лайм', 'quantity': 20, 'measure': 'гр'},
    ]
}


portions = int(input("Введите количество порций: "))


total_ingredients = {}


for dishes in cook_book.values():

    for ingredient in dishes:
        name = ingredient['ingredient_name']
        measure = ingredient['measure']
        quantity = ingredient['quantity'] * portions


        key = (name, measure)


        total_ingredients[key] = total_ingredients.get(key, 0) + quantity


print("Результат:")
for (name, measure), quantity in total_ingredients.items():
    print(f"{name.capitalize()}: {quantity} {measure}")
    