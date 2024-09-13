n = int(input())
e = input()

rail = [['\0' for _ in range(len(e))] for _ in range(n)]
di = False
row, col = 0, 0

for i in range(len(e)):
    if row == 0:
        di = True
    if row == n-1:
        di = False

    rail[row][col] = '0'
    col += 1

    if di:
        row += 1
    else:
        row -= 1

cnt = 0
for i in range(n):
    for j in range(len(e)):
        if rail[i][j] == '0' and cnt < len(e):
            rail[i][j] = e[cnt]
            cnt += 1

d = []
row, col = 0, 0
for i in range(len(e)):
    if row == 0:
        di = True
    if row == n-1:
        di = False

    if rail[row][col] != '0':
        d.append(rail[row][col])
        col += 1

    if di:
        row += 1
    else:
        row -= 1
d = ''.join(d)
print(d)