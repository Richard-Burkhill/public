import BurkhillMaths as stat
import statistics

dl = [5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10]

mode2 = [1,1,1,2,2,2,3,3,3,3]
mode3=[1,1,1,1,2,2,2,3,3,3]
mode4=[1,1,1,1,2,2,2,2,3,3]
emptyList = []

print(stat.calcMean (dl))

print(stat.calcMedian(dl))

print(stat.modesIfAny(dl))
print(stat.modesIfAny(mode2))
print(stat.modesIfAny(mode3))
print(stat.modesIfAny(mode4))
print(stat.modesIfAny(emptyList))

print("\nUsing Python3 statistics library")

print(statistics.mean (dl))

print(statistics.median(dl))

print(statistics.mode(dl))
print(statistics.mode(mode2))
print(statistics.mode(mode3))
print(statistics.mode(mode4))
print("statistics.mode() can't handle empty lists")
