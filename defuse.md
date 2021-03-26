# Defuse Bomb

From the README file we learn that we need to defuse the bomb.
For this we need to go through 6 stages and we have several hints:   

```
Diffuse this bomb!
When you have all the password use it as "thor" user with ssh.

HINT:
P
 2
 b

o
4

```

The answers to the questions at each stage are impossible to guess, so we need to decompile the file.

Download the file via ssh via command:

[comment]: <> (paste command)

Now let's use the decompiler from https://retdec.com/

    python $RETDEC_INSTALL_DIR/bin/retdec-decompiler.py bomb

We get several files. We are interested in `bomb.c` which is added to utils folder.  
Now let's take a look at individual sections of the code.   
// We delete decompiler comments, but you can always read them in `bomb.c` file

### Phase 1

```c
int32_t phase_1(int32_t a1) {
    if (strings_not_equal(a1, "Public speaking is very easy.") == 0) {
        return 0;
    }
    explode_bomb();
}
```

We see a check for string matching, so the answer to the first phase is:

    Public speaking is very easy.

Here we see that the hint for the first phase is the answer symbol!

### Phase 2

```c
int32_t phase_2(int32_t a1) {
    int32_t v1;
    read_six_numbers(a1, &v1);
    if (v1 != 1) {
        explode_bomb();
    }
    int32_t v2 = 1;
    int32_t v3 = v2 + 1;
    int32_t v4 = 4 * v2 + (int32_t)&v1;
    int32_t result = v3 * *(int32_t *)(v4 - 4);
    while (*(int32_t *)v4 == result) {
        if (v3 >= 6) {
            return result;
        }
        v2 = v3;
        v3 = v2 + 1;
        v4 = 4 * v2 + (int32_t)&v1;
        result = v3 * *(int32_t *)(v4 - 4);
    }
    explode_bomb();
}
```

We see that you need to enter 6 numbers.
Here you need to understand that int32_t is actually can be a pointer... or not

### Phase 3

```c
int32_t phase_3(int32_t str) {
    int32_t result;
    int32_t v1;
    char v2;
    uint32_t items_assigned = sscanf((char *)str, "%d %c %d", &result, &v2, &v1); // 0x8048bb7
    if (items_assigned <= 2) {
        explode_bomb();
    }
    g9 = result;
    char v3;
    switch (result) {
        case 0: {
            v3 = 113;
            if (v1 != 777) {
                explode_bomb();
            }
            break;
        }
        case 1: {
            v3 = 98;
            if (v1 != 214) {
                explode_bomb();
            }
            break;
        }
        case 2: {
            v3 = 98;
            if (v1 != 755) {
                explode_bomb();
            }
            break;
        }
        case 3: {
            v3 = 107;
            if (v1 != 251) {
                explode_bomb();
            }
            break;
        }
        case 4: {
            v3 = 111;
            if (v1 != 160) {
                explode_bomb();
            }
            break;
        }
        case 5: {
            v3 = 116;
            if (v1 != 458) {
                explode_bomb();
            }
            break;
        }
        case 6: {
            v3 = 118;
            if (v1 != 780) {
                explode_bomb();
            }
            break;
        }
        case 7: {
            v3 = 98;
            if (v1 != 524) {
                explode_bomb();
            }
            break;
        }
        default: {
            explode_bomb();
        }
    }
    if (v2 == v3) {
        return result;
    }
    explode_bomb();
}
```

We see that in this case program wants from us `("%d %c %d", &result, &v2, &v1)` number, char and number.   
And have a hint for this: second must be char 'b' witch ascii number is 98, and v2 must be 98.   
See thant char v2 must be equal char v3 for get result, that means v3 must be 98.
Next we have 2 cases, than v3 == 98:
    result: 1, v2: 'b', v1: 214
    result: 2, v2: 'b', v1: 755
    result: 7, v2: 'b', v1: 524

ok, we have 2 answers:

    1 b 214
    2 b 755

### Phase 4

```c
int32_t func4(uint32_t a1) {
    int32_t result = 1;
    if (a1 >= 2) {
        int32_t v1 = func4(a1 - 1);
        result = func4(a1 - 2) + v1;
    }
    return result;
}

int32_t phase_4(int32_t str) {
    int32_t v1;
    if (sscanf((char *)str, "%d", &v1) != 1) {
        explode_bomb();
    }
    int32_t v2 = v1;
    if (v2 >= 0 != v2 != 0) {
        explode_bomb();
    }
    if (func4(v2) == 55) {
        return 55;
    }
    explode_bomb();
}
```

A number is required here and there is no hint.  
We see that 0 and 1 cannot be used. And the result of recursive operation of func4 the value 55 should be obtained.

Because in too hard to count the number manually, we make a program `phase4.c` for it:

```c
int main(void) {
    uint32_t i = 2;
    while (func4(i) != 55) {
        i++;
    }
    printf("%d\n", i);
    return 0;
}
```

And now we se that the answer is `9`
### Phase 5

```c
int32_t phase_5(int32_t a1) {
    if (string_length(a1) != 6) {
        explode_bomb();
    }
    
    int32_t v1;
    int32_t v2 = &v1;
    for (int32_t i = 0; i < 6; i++) {
        unsigned char v3 = *(char *)(i + a1);
        char v4 = *(char *)((int32_t)(v3 % 16) + (int32_t)&g1);
        *(char *)(i + v2) = v4;
    }
    if (strings_not_equal(v2, "giants") == 0) {
        return 0;
    }
    explode_bomb();
}
```

We see that g1 a global variable not setted in bomb.c and another decompiled files,
but we must know what contains address 0x804b220
```c
int32_t g1 = 0x76727369; // 0x804b220
```

For that we use another decompiler: https://www.hopperapp.com  
And found this:

```asm
             array.123:
0804b220         db  0x69 ; 'i' ; DATA XREF=phase_5+38
0804b221         db  0x73 ; 's'
0804b222         db  0x72 ; 'r'
0804b223         db  0x76 ; 'v'
0804b224         db  0x65 ; 'e'
0804b225         db  0x61 ; 'a'
0804b226         db  0x77 ; 'w'
0804b227         db  0x68 ; 'h'
0804b228         db  0x6f ; 'o'
0804b229         db  0x62 ; 'b'
0804b22a         db  0x70 ; 'p'
0804b22b         db  0x6e ; 'n'
0804b22c         db  0x75 ; 'u'
0804b22d         db  0x74 ; 't'
0804b22e         db  0x66 ; 'f'
0804b22f         db  0x67 ; 'g'
```

Ok, we see that we have hint that first letter must be 'o', 
and after this transforms it should become letter 'g' from check word `giants`.  
Let's check this:

g == 0х0804b22f == (v3 % 16) + 0x804b220  
then  
v3 % 16 = 0х0804b22f - 0x804b220 == 15

### Phase 6
