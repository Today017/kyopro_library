symbols=['!','#','$','%','&','*','+','-','/','<','=','>','?','@','^','_','~','|','\\','.',':',';','[',']','{','}','(',')','"',"'",',']

code=''

while True:
    try:
        line=input()
        code+=line+'\n'
    except:
        break

res=""

for line in code.split('\n'):
    # line=line.replace("    ","\t")
    for symbol in symbols:
        a=' '+symbol
        line=line.replace(a,symbol)
        a=symbol+' '
        line=line.replace(a,symbol)
    res+=line+'\n'

print(res)
