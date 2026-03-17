results = {
    'vk': {'revenue': 103, 'cost': 98},
    'yandex': {'revenue': 179, 'cost': 153},
    'facebook': {'revenue': 103, 'cost': 110},
    'adwords': {'revenue': 35, 'cost': 34},
    'twitter': {'revenue': 11, 'cost': 24}
}


for campaign_data in results.values():
    revenue = campaign_data['revenue']
    cost = campaign_data['cost']

    roi = ((revenue / cost) - 1) * 100
    campaign_data['ROI'] = round(roi, 2)

print("Все кампании:")

sorted_results = dict(sorted(results.items()))
print(sorted_results)

print("\nПрибыльные кампании (ROI > 0):")

profitable = {name: data for name, data in results.items() if data['ROI'] > 0}

sorted_profitable = dict(sorted(profitable.items()))
print(sorted_profitable)