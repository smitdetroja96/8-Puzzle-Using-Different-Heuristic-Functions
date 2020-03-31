import os

out_file = "output.txt"
in_file = "input.txt"

os.system("./createBoard >>"+out_file)
print "Board Created"
os.system("./euclidean >>"+out_file+" <"+in_file)
print "Euclidean Created"
os.system("./manhattan >>"+out_file+" <"+in_file)
print "Manhattan Created"
os.system("./hamming >>"+out_file+" <"+in_file)
print "Hamming Created"
os.system("./inversion >>"+out_file+" <"+in_file)
print "Inversion Created"