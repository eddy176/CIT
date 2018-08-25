def test_prime(n):
    if (n==1):
        return False
    elif (n==2):
        return True
    else:
        count = 0
        for x in range(2,n):
            if(n % x==0):
                count +=1
                if count != 0:
                    return False
            else:
                return True
