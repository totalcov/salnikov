def create_nested_dict(lst):
    if not lst:
        return {}
  
    result = lst[-1]
    
    for i in range(len(lst) - 2, -1, -1):
        
        result = {lst[i]: result}
    return result


my_list1 = ['2018-01-01', 'yandex', 'cpc', 100]
my_list2 = ['a', 'b', 'c', 'd', 'e', 'f']

print(create_nested_dict(my_list1))
print(create_nested_dict(my_list2))