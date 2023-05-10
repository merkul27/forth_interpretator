'''
Описание:
Проверка корректности введенного потока с помощью метода синтаксически управляемого перевода для языка Forth
На вход программа получает от лексического анализатора входную строку в формате потока интов (input.txt) и таблицу имен(name_table.txt). А также берет из файла заданную грамматику(gram.txt).
Программа полексемно считывает входной поток и работает со стеком, проверяя применимость правил грамматики. Если входной поток корректный в терминах нашей грамматики, то стек сворачивается в #PROGR и выдает SUCCESS, иначе выдает ошибку ERROR.
То есть программа проверяет корректность написания условий, циклов и ввода нового имени.

Грамматика из файла gram.txt
PROGR->MOP
MOP->MOP OP
MOP->OP
OP->WORD
OP->begin MOP until
OP->do MOP loop
OP->if MOP then
OP->: WORD MOP ;
OP->if MOP else MOP then
WORD-><keyword>
WORD-><num>
WORD-><name>
'''


class Nable:            #хранятся элементы таблицы имен
    def __init__(self, num, name, tp):
        self.num = num  #int лексемы
        self.name = name    #имя лексемы
        self.tp = tp    #тип лексемы

class Rule:             #хранятся правила грамматики
    def __init__(self, n, left, right):
        self.n = n
        self.left = left
        self.right = right
        #self.cond = cond
    
def procedures(rule, r): #процедуры соответствующие применяемому правилу грамматики
    if (rule.n == 1):
        if r == '#':
            stek[-1] = rule.left
            print('done rule {}'.format(rule.n))
            return 1
        else: 
            return 0
    if (rule.n == 2):
        #for i in range(k):
        stek.pop()
        stek[-1] = rule.left
        print('done rule {}'.format(rule.n))
        return 1
    if (rule.n == 3):
        stek[-1] = rule.left
        #output.append(r)
        print('done rule {}'.format(rule.n))
        return 1
    if (rule.n == 4):
        if stek[-2] != ':':
            #print('rule 4')
            stek[-1] = rule.left
            output.append(r)
            print('done rule {}'.format(rule.n))
            return 1
        else:
            return 0
    if (rule.n == 5):
        for i in range(3):
            stek.pop()
        stek.append(rule.left)
        print('done rule {}'.format(rule.n))
        return 1
    if (rule.n == 6):   
        for i in range(3):
            stek.pop()
        stek.append(rule.left)
        print('done rule {}'.format(rule.n))
        return 1
    if (rule.n == 7): 
        for i in range(3):
            stek.pop()
        stek.append(rule.left)
        print('done rule {}'.format(rule.n))
        return 1
    if (rule.n == 8):   
        for i in range(4):
            stek.pop()
        stek.append(rule.left)
        print('done rule {}'.format(rule.n))
        return 1
    if (rule.n == 9):   
        for i in range(5):
            stek.pop()
        stek.append(rule.left)
        print('done rule {}'.format(rule.n))
        return 1
    if (rule.n == 10):
        stek[-1] = rule.left
        #output.append(r)
        print('done rule {}'.format(rule.n))
        return 1
    if (rule.n == 11):
        stek[-1] = rule.left
        #output.append(r)
        print('done rule {}'.format(rule.n))
        return 1
    if (rule.n == 12):
        stek[-1] = rule.left
        #output.append(r)
        print('done rule {}'.format(rule.n))
        return 1
            
key_words = ["+", "-", "*", "/", ".", "dup", "drop", "mod",             #массив ключевых слов
            "over", "rot", "swap", "roll", "abs", "negate", "1+",
            "1-", "pick", ".", "@", "!", "and", "or", "xor", "not", ">", "<",
            "=", "0<", "0=", "0>"]

NTERM = ["PROGR","MOP", "OP", "MWORD", "WORD"]

stek = ['#'] #стек

output = [] 

def rules_check(stek, r):    #функция проверки стека на приминяемость правил
    prim = 0
    #print('rule check')
    for rule in rules:  
        j = 1
        if prim == 1:
            #print('правило применено')
            break
        stekslovo = stek[-1]
        while(j < len(stek)):
            
            if stekslovo == rule.right:
                prim = procedures(rule, r)  #выполнение процедуры соответствующей правилу
                print(stek)
                if (r == '#' and rule.n == 1):
                    if len(stek) == 2:
                        print('SUCCESS')
                    else:
                        print('ERROR')
                    return 0
                return prim
            else:
                j += 1
                stekslovo = stek[-j]+ ' ' + stekslovo
    return prim

if __name__ == "__main__":
    
    rules = []
    n = 0
    file1 = open("gram.txt","r")  #считывание правил грамматики из файла
    while True:
        n += 1
        line = file1.readline()
        if not line:
            break
        data = line.split("->")
        data[-1] = data[-1].strip('\n')
        #print(data)
        rules.append(Rule(n, data[0], data[1]))
    file1.close
    
    name_table = []
    file2 = open("name_table.txt","r")  #считывание таблицы имен из файла
    while True:
        line = file2.readline()
        if not line:
            break
        data = line.split()
        
        name_table.append(Nable(int(data[0]), data[1], int(data[2])))
    file2.close
    
    inline = []
    file3 = open("input.txt","r")   #считывание входной строки
    while True:
        line = file3.readline()
        if not line:
            break
        data = line.split()
        data[-1] = data[-1].strip('\n')
        for i in range(len(data)):
            inline.append(int(data[i]))
    file3.close
    
    inline.append('#')      #добавления конечного символа во входной поток
    print(inline)
    r = ''
    i = 0
    while (i < len(inline)):    #обработка входной строки полексемно (строка представлена интами)
        
        if (r != ''):
            p = rules_check(stek, r)       #проверка на применения правил к стеку
            #print(stek, r)
            while (p == 1):
                #print('rule')
                p = rules_check(stek, r)
            if p == 0:
                if (r == '#'):
                    break
                print('нет правила')
                stek.append(r)
                r = ''
                i += 1
                #print('i++2 {}'.format(i))
                print(stek)

        f = 0
        index = inline[i]
        #print(index, i)
        if index == '#':
            f = 1
            r = index
        
        
        for t in name_table:        #проверка наличия лексемы в таблице имен
            #print(t.num)
            if index == t.num:
                #print('find')
                f = 1
                if t.num >= 0:
                    if t.tp == 1:
                        r = '<num>'
                    if t.tp == 0:
                        r = '<name>'
                if t.num < 0:
                    for k in key_words:
                        #print(k)
                        if t.name == k:
                            r = '<keyword>'
                            break
                        else:
                            r = t.name
        if f == 0:
            print("UNKNOWN LEXEM")
            exit = 1
            break
        else:
            if(stek == ['#']):
                stek.append(r)      #добавление в стек первого считанного символа
                r = ''
                i += 1
                #print('i++1 {}'.format(i))
             
    print(stek)     #вывод содержимого стека для проверки
    
    
