import sys

xs = [int(x) for x in sys.stdin]
cnt = 0
for i in range(len(xs) - 3):
  cnt += xs[i] < xs[i + 3]
print(cnt)

