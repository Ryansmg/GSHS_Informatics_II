n = int(input())
p = input()

rail = [['\0' for _ in range(len(p))] for _ in range(n)]
di = False
row, col = 0, 0

for i in p:
    if row == 0 or row == n-1:
        di = not di
    rail[row][col] = i
    col += 1
    if di:
        row += 1
    else:
        row -= 1

e = []
for i in range(n):
    for j in range(len(p)):
        if rail[i][j] != '\0':
            e.append(rail[i][j])

e = ''.join(e)
print(e)