import base64
a = "R9Ly6NoJvsIPnWhETYtHe4Sdl+MbGujaZpk102wKCr7/ODg5zXAFqQfxBicV3m8U"
b = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
base_fix = "+wXp+xDkldnFdFNFdxnzdFWpGx2m"
table = ''.maketrans(a, b)
print(base64.b64decode(base_fix.translate(table)))