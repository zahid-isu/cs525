#demo python

x = [5,6,7,5,9]
y=[9, 1]


print(" x:", x)
print(" y:", y)


# append()
x.append(y)
print("append y to x:", x)


#copy 
x.copy()
print("copy", x)

#count
print("count 5:", x.count(5))


# extend()
x.extend(y)
print("extend x:", x)

# index()
idx= x.index(7)
print("index of 7 in x:", idx)

# insert()
x.insert(2, 't')
print("insert 't' at 2nd position in x:", x)

# pop()
poped_itm= x.pop(3)
print("poped 9 from x: ", x)

# remove()
remove_itm= x.remove([9, 1])
remove_itm= x.remove('t')

print("removed [9,1] & t from x: ", x)


# reverse()

x.reverse()
print("reversed x: ", x)

# sort()

x.sort()
print("sorted x:", x)

#clear()
x.clear()
print("clear x: ", x)
