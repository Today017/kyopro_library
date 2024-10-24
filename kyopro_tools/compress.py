symbols=['!','#','$','%','&','*','+','-','/','<','=','>','?','@','^','_','~','|','\\','.',':',';','[',']','{','}','(',')','"',"'",',']

code=''

while True:
    line=input()
    if line=='':
        break
    code+=line+'\n'

res=""

for line in code.split('\n'):
    line=line.replace("    ","\t")
    for symbol in symbols:
        a=' '+symbol
        line=line.replace(a,symbol)
        a=symbol+' '
        line=line.replace(a,symbol)
    res+=line+'\n'

print(res)
