from math import sqrt

primes = [2]
maximum = 100000000

for num in range(3, maximum, 2):
    is_prime = True
    square_root = sqrt(num)
    for prime in primes:
        if num % prime == 0:
            is_prime = False
            break
        if prime > square_root:
            break
    if is_prime:
        print(num)
        primes.append(num)