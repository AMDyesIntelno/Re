difference=[0, 9, -9, -1, 13, -13, -4, -11, -9, -1, -7, 6, -13, 13, 3, 9, -13, -11, 6, -7]
for first_letter in range(97,123):
    user_string=""
    for i in range(20):
        user_string+=chr(first_letter+difference[i])
    print(user_string)
#lucky_hacker_you_are