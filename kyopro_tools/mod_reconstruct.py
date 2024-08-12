# p/q mod P が与えられたとき、p, q を復元する

def reconstruct(n, mod):
    v = [mod, 0]
    w = [n, 1]
    while w[0] * w[0] * 2 > mod:
        q = v[0] // w[0]
        z = [v[0] - q * w[0], v[1] - q * w[1]]
        v = w
        w = z
        print(w)
    
    if w[1] < 0:
        w[0] *= -1
        w[1] *= -1
    
    return w

def add_rational_expression(original, mod):
    original += '*'
    buffer = ""
    res = ""
    tag_parsing = False

    for c in original:
        if c == '<':
            tag_parsing = True
            res += buffer
            buffer = ""
        elif c == '>':
            tag_parsing = False
        
        if not tag_parsing:
            if '0' <= c <= '9':
                buffer += c
            else:
                if buffer:
                    num = int(buffer)
                    if num < mod and num * num * 2 > mod:
                        w = reconstruct(num, mod)
                        buffer += f' ({w[0]}/{w[1]}) '
                    res += buffer
                    buffer = ""
                res += c
        else:
            res += c

    return res[:-1]

def main():
    mod = 998244353
    original = input("Enter the expression: ")
    
    if mod:
        result = add_rational_expression(original, mod)
        print("Result:", result)
    else:
        print("No recognized mod value found in the input.")

if __name__ == "__main__":
    main()