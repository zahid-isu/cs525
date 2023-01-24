import myfunc as my

import numpy as np
x=2
smine = my.expo(x,100)
snum = np.exp(2)
serr1= smine - snum
print("Error between my exp(%f) and numpy exp(%f) is %.5E" % (x,x,abs(serr1)))


smine = my.natlog(x,100)
snum = np.log(2)
serr2 = smine - snum
print("Error between my ln(%f) and numpy ln(%f) is %.5E" % (x,x,abs(serr2)))