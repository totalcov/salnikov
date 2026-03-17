countries_temperature = [
    ['Таиланд', [75.2, 77, 78.8, 73.4, 68, 75.2, 77]],
    ['Германия', [57.2, 55.4, 59, 59, 53.6]],
    ['Россия', [35.6, 37.4, 39.2, 41, 42.8, 39.2, 35.6]],
    ['Польша', [50, 50, 53.6, 57.2, 55.4, 55.4]]
]

print("Средняя температура в странах:")
for country in countries_temperature:
    name = country[0]
    temps_f = country[1]
    
    temps_c = [(f - 32) * 5/9 for f in temps_f]
    avg_temp = sum(temps_c) / len(temps_c)
    
    print(f"{name} - {avg_temp:.1f} C")